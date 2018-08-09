/**
  ******************************************************************************
  * @file       NdefNfcTagM24LR.cpp
  * @author     AMG Central Lab
  * @version    V2.0.0
  * @date       19 May 2017
  * @brief      Wrapper class of the NDefLib library to write/read NDEF messages.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */


#include <cmath>
#include "NDefNfcTagM24LR.h"


/* wait 1sec, driver is configured to let 200ms for command to complete */
/* which is enough for all commands except GetSession if RF session is already opened */
/* Smartphone generally releases the session within the second, anyway the user can modify this value */
#define OPENSESSION_NTRIALS 5

#define CC_FILE_LENGTH_BYTE 15


#define NFCT5_MAGICNUMBER_E1_CCFILE       0xE1
#define NFCT5_MAGICNUMBER_E2_CCFILE       0xE2
#define NFCT5_EXTENDED_CCFILE             0xFF
#define NFCT5_VERSION_V1_0                0x40
#define NFCT5_READ_ACCESS                 0x0C
#define NFCT5_WRITE_ACCESS                0x03

#define NFCT5_NDEF_MSG_TLV                0x03
#define NFCT5_PROPRIETARY_TLV             0xFD
#define NFCT5_TERMINATOR_TLV              0xFE
#define NFCT5_3_BYTES_L_TLV               0xFF
    

#define NDEF_MAX_SIZE               NFC_DEVICE_MAX_NDEFMEMORY

#define NDEF_SIZE_OFFSET            0
#define FIRST_RECORD_OFFSET         2

#ifndef MIN
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif

#define NFCTAG_4M_SIZE            0x200
#define NFCTAG_16M_SIZE           0x800
#define NFCTAG_64M_SIZE           0x2000

#define MAX_NDEF_MEM                 0x200
#define M24LR_MAX_SIZE               NFCTAG_4M_SIZE
#define M24LR_NDEF_MAX_SIZE          MIN(M24LR_MAX_SIZE,MAX_NDEF_MEM)
#define NFC_DEVICE_MAX_NDEFMEMORY    M24LR_NDEF_MAX_SIZE

/**
  * @brief  This function read the data stored in NDEF file at defined offset.
  * @param  Offset : Offset in the NDEF file.
  * @param  DataSize : Number of byte to read.
  * @param  pData : pointer on buffer to store read data.
  * @retval NDEF_ERROR_MEMORY_INTERNAL : Size not compatible with memory.
  * @retval NDEF_ERROR_NOT_FORMATED : CCFile data not supported.
  * @retval NDEF_ERROR : No NDEF in the tag.
  * @retval NDEF_OK : The operation is completed.
  */
uint16_t NDefNfcTagM24LR::ReadData( uint16_t Offset , uint16_t DataSize , uint8_t* pData )
{
  uint16_t status = NDEF_ERROR;
  uint8_t atlv_detect[4];
  uint8_t index = 0;
  
  /* If too many data to write return error */
  if ( DataSize > NDEF_MAX_SIZE ) {
    return NDEF_ERROR_MEMORY_INTERNAL;
  }
  
  /* Detect NDEF message in memory */
  status = NfcType5_NDEFDetection( );
  if ( status != NDEF_OK ) {
    return status;
  }

  /* Read TL of Type 5 */
  status = NDefReadByte(CCFileStruct.NDEF_offset, 4, atlv_detect);
  if ( status != NDEF_OK ){
    return status;
  }
  
  if ( atlv_detect[1] == NFCT5_3_BYTES_L_TLV ) {
    index = 2;
  }

  if (Offset==0 && DataSize>=2) {
    if ( atlv_detect[1] == NFCT5_3_BYTES_L_TLV ) {
      pData[0] = atlv_detect[2];
      pData[1] = atlv_detect[3];
    } else {
      pData[0] = 0x00;
      pData[1] = atlv_detect[1];
    }
    DataSize -= 2;
    pData += 2;
  }

  /* Check CC file is in the correct mode to proceed */
  if ( CCFileStruct.State ==  TT5_INITIALIZED ) {
    return NDEF_ERROR;
  }

  if (DataSize > 0) {
    /* Read NDEF */
    if ( NDefReadByte(CCFileStruct.NDEF_offset + index + Offset, DataSize, pData) != NFC_SUCCESS ) {
      return NDEF_ERROR;
    }
  }
  
  return NDEF_OK;
}

/**
  * @brief  This function writes data in NDEF file at defined offset.
  * @param  Offset : Offset in the NDEF file.
  * @param  DataSize : Number of byte to write.
  * @param  pData : pointer on buffer to copy.
  * @retval NDEF_ERROR_MEMORY_INTERNAL : Size not compatible with memory.
  * @retval NDEF_ERROR_NOT_FORMATED : CCFile data not supported.
  * @retval NDEF_ERROR : No NDEF in the tag.
  * @retval NDEF_OK : The operation is completed.
  */
uint16_t NDefNfcTagM24LR::WriteData( uint16_t Offset , uint32_t DataSize , uint8_t *pData )
{
  uint8_t atlv[4];
  uint8_t index = 0;
  uint16_t NDEF_Size = 0;
  bool status;

  /* Do not include length bytes */
  DataSize -= FIRST_RECORD_OFFSET;
  
  /* If too many data to write return error */
  if ( DataSize > NDEF_MAX_SIZE ) {
    return NDEF_ERROR_MEMORY_INTERNAL;
  }
  
  /* Detect NDEF message in memory */
  if ( NfcType5_NDEFDetection( ) != NDEF_OK ) {
    return NDEF_ERROR;
  }
 
  /* Extract NDEF Size from buffer */
  NDEF_Size = (uint16_t)(pData[0] << 8);
  NDEF_Size = NDEF_Size | (uint16_t)(pData[1] );
  
  /* If entire NDEF is written, update Length of Type 5 */
  if ( DataSize == NDEF_Size ) {
    /* Check if L is on 3 or 1 byte */
    if ( NDEF_Size >= NFCT5_3_BYTES_L_TLV ) {
      /* First init L with 0, will be updated at the end */
      atlv[1] = 0x00;
      atlv[2] = 0x00;
      atlv[3] = 0x00;
      status = NDefWriteByte( (atlv + 1), 3, (CCFileStruct.NDEF_offset + 1));
      index += 4; 
    } else {
      /* First inti L with 0, will be updated at the end */
      atlv[1] = 0x00;
      status = NDefWriteByte( (atlv + 1), 1, (CCFileStruct.NDEF_offset + 1));
      index += 2;
    }
  }
  
  /* Start write NDEF message to EEPROM */
  status = NDefWriteByte( (pData + FIRST_RECORD_OFFSET), DataSize, CCFileStruct.NDEF_offset + index + Offset);
  if ( status != NFC_SUCCESS ) {
    return NDEF_ERROR;
  }
  
  /* If entire NDEF is written, update Length of Type 5 */
  if ( DataSize == NDEF_Size ) {
    /* Check if L is on 3 or 1 byte */
    if ( NDEF_Size >= NFCT5_3_BYTES_L_TLV ) {
      /* Update Length value */
      atlv[1] = NFCT5_3_BYTES_L_TLV;
      atlv[2] = pData[0];
      atlv[3] = pData[1];
      status = NDefWriteByte( (atlv + 1), 3, (CCFileStruct.NDEF_offset + 1));
    } else {
      /* Update Length value */
      atlv[1] = pData[1];
      status = NDefWriteByte( (atlv + 1), 1, (CCFileStruct.NDEF_offset + 1));
    }

    /* Write Terminator TLV */
    atlv[0] = NFCT5_TERMINATOR_TLV;
    status = NDefWriteByte( atlv, 1, CCFileStruct.NDEF_offset + index + NDEF_Size);
  }
  
  return NDEF_OK;
}

/**
  * @brief  This functions writes CCFile in EEPROM.
  * @param  pCCBuffer : pointer on the buffer containnig CC file.
  * @retval NFCTAG status.
  */
uint16_t NDefNfcTagM24LR::NfcType5_WriteCCFile( const uint8_t * const pCCBuffer )
{
  bool ret_value;
  
  /* Write first block of CCFile */
  ret_value = NDefWriteByte( pCCBuffer, 0x4, 0x00);
 
  /* If extended memory writes the next 4 bytes */
  if ( (pCCBuffer[2] == 0x00) && (ret_value == NFC_SUCCESS) ) {
    ret_value = NDefWriteByte( pCCBuffer + 4, 4, 0x04);
  }

  if ( ret_value != NFC_SUCCESS ) {
    return NDEF_ERROR;
  }
  
  return NDEF_OK;
}

/**
  * @brief  This functions reads CCFile from EEPROM.
  * @param  pCCBuffer : pointer on the buffer containnig CC file.
  * @retval NFCTAG status.
  */
uint16_t NDefNfcTagM24LR::NfcType5_ReadCCFile( uint8_t * const pCCBuffer )
{
  bool ret_value;
  
  /* Read 4 bytes of CC File */
  ret_value = NDefReadByte(0x00, 4, pCCBuffer);

  /* If extended memory reads the next 4 bytes */
  if ( (pCCBuffer[2] == 0x00) && (ret_value == NFC_SUCCESS) ) {
    ret_value = NDefReadByte(0x04, 4, pCCBuffer + 4 );
  }
  
  if ( ret_value != NFC_SUCCESS ) {
    return NDEF_ERROR;
  }
  
  return NDEF_OK;
}

/**
  * @brief  This functions initializes Nfc Type.
  * @param  None.
  * @retval NFCTAG status.
  */
uint16_t NDefNfcTagM24LR::NfcType5_TT5Init( void )
{
  bool ret_value ;
  uint16_t status;
  uint8_t accbuffer[8];
  uint8_t cdata;

  /* Prepare buffer to update CCFile */
  accbuffer[0] = CCFileStruct.MagicNumber;
  accbuffer[1] = CCFileStruct.Version;
  accbuffer[2] = CCFileStruct.MemorySize;
  accbuffer[3] = CCFileStruct.TT5Tag;
  CCFileStruct.NDEF_offset = 0x04;
  
  /* If extended memory prepare the length bytes */
  if ( CCFileStruct.MemorySize == NFCT5_EXTENDED_CCFILE ) {
    accbuffer[6] = (uint8_t)(CCFileStruct.ExtMemorySize >> 8);
    accbuffer[7] = (uint8_t)(CCFileStruct.ExtMemorySize & 0xFF);
    CCFileStruct.NDEF_offset = 0x08;
  }
  
  /* Update CCFile */
  status = NfcType5_WriteCCFile( accbuffer );
  if ( status != NDEF_OK ) {
    return status;
  }
  
  /* Update NDEF TLV for INITIALIZED state */
  /* Update T */
  cdata = NFCT5_NDEF_MSG_TLV;
  ret_value = NDefWriteByte( &cdata, 1, CCFileStruct.NDEF_offset);
  if ( ret_value != NFC_SUCCESS ) {
    return NDEF_ERROR;
  }

  /* Update L */
  cdata = 0x00;
  ret_value = NDefWriteByte( &cdata, 1, (CCFileStruct.NDEF_offset + 1));
  if ( ret_value != NFC_SUCCESS ) {
    return NDEF_ERROR;
  }
  
  return NDEF_OK;
}

/**
  * @brief  This functions detects Nfc Tyoe.
  * @param  None.
  * @retval NDEF_ERROR_NOT_FORMATED : CCFile data not supported.
  * @retval NDEF_OK : The operation is completed.
  */
uint16_t NDefNfcTagM24LR::NfcType5_NDEFDetection( void )
{
  uint8_t acc_buffer[8];
  uint8_t atlv_detect[4];
  uint16_t status;
  uint32_t memory_size;
  
  CCFileStruct.State = TT5_NO_NDEF;
  
  /* Read CCFile */
  status = NfcType5_ReadCCFile( acc_buffer );
  if ( status != NDEF_OK ) {
    return status;
  }
  
  /* Check Byte 0 is equal to magic number */
  if ( ( acc_buffer[0] != NFCT5_MAGICNUMBER_E1_CCFILE ) && ( acc_buffer[0] != NFCT5_MAGICNUMBER_E2_CCFILE ) ) {
    return NDEF_ERROR_NOT_FORMATED;
  } else if ( ( (acc_buffer[1]&0xFC) != 0x40 ) ) { /* Check Version number */
    return NDEF_ERROR_NOT_FORMATED;
  }
  
  /* Check if CCFile is on 4 Bytes or 8 Bytes */
  if ( acc_buffer[2] == 0x00 ) {
    /* Update CCFIle structure */
    CCFileStruct.MemorySize = 0x0;
    CCFileStruct.ExtMemorySize = (uint16_t)acc_buffer[6];
    CCFileStruct.ExtMemorySize = ( CCFileStruct.ExtMemorySize << 8 ) |  acc_buffer[7];
    memory_size = CCFileStruct.ExtMemorySize;
    CCFileStruct.NDEF_offset = 8;
  } else {
    /* Update CCFIle structure */
    CCFileStruct.MemorySize = acc_buffer[2];
    CCFileStruct.ExtMemorySize = 0x0;
    memory_size = CCFileStruct.MemorySize;
    CCFileStruct.NDEF_offset = 4;
  }
  
  /* Update CCFIle structure */
  CCFileStruct.MagicNumber = acc_buffer[0];
  CCFileStruct.Version = acc_buffer[1];
  CCFileStruct.TT5Tag = acc_buffer[3];
  
  /* Search for position of NDEF TLV in memory and tag status */
  while( ( NDefReadByte(CCFileStruct.NDEF_offset, 4, atlv_detect) == NFC_SUCCESS ) && ( CCFileStruct.NDEF_offset < memory_size ) ) {
    /* Detect first NDEF Message in memory */
    if ( atlv_detect[0] == NFCT5_NDEF_MSG_TLV ) {
      if ( atlv_detect[1] == 0x00 ) {
        CCFileStruct.State = TT5_INITIALIZED;
      } else {
        if ( CCFileStruct.Version & 0x3 ) {
          CCFileStruct.State = TT5_READ;
        } else {
          CCFileStruct.State = TT5_READ_WRITE;
        }
      }
      return NDEF_OK;
    } else if ( atlv_detect[0] == NFCT5_PROPRIETARY_TLV ) { /* If Proprietary NDEF jump to end of proprietary message */
      if ( atlv_detect[1] == NFCT5_3_BYTES_L_TLV ) {
        CCFileStruct.NDEF_offset = CCFileStruct.NDEF_offset + ( (uint32_t)atlv_detect[2] << 8 ) + atlv_detect[3];
        continue;
      } else {
        CCFileStruct.NDEF_offset = CCFileStruct.NDEF_offset + atlv_detect[1];
        continue;
      }
    } else if ( atlv_detect[0] == NFCT5_TERMINATOR_TLV ) { /* if Terminator no NDEF detected */
      return NDEF_ERROR_NOT_FORMATED;
    }

    CCFileStruct.NDEF_offset++;
  }
  
  return NDEF_ERROR_NOT_FORMATED;
}

/**
  * @brief  This functions opens a session.
  * @param  force : force the opening.
  * @retval true.
  */
bool NDefNfcTagM24LR::open_session(bool force) {
  uint16_t status = NfcType5_NDEFDetection();

  if ( status != NDEF_OK ) {
    CCFileStruct.MagicNumber = NFCT5_MAGICNUMBER_E1_CCFILE;
    CCFileStruct.Version = NFCT5_VERSION_V1_0;
    CCFileStruct.MemorySize = ( M24LR_MAX_SIZE / 8 ) & 0xFF;
    CCFileStruct.TT5Tag = 0x05;
    /* Init of the Type Tag 5 component (M24LR) */
    while ( NfcType5_TT5Init( ) != NDEF_OK );
  }

  mIsSessionOpen = 1;

  return true;
}


/**
  * @brief  This functions closes a session.
  * @param  None.
  * @retval true.
  */
bool NDefNfcTagM24LR::close_session() 
{
    return true;
}

/**
  * @brief  This functions writes bytes.
  * @param  byffer : the buffer containing data.
  * @param  length: the length of the buffer in bytes.
  * @param  offset: the offset of the buffer in bytes.
  * @retval true if written, false otherwise.
  */
bool NDefNfcTagM24LR::writeByte(const uint8_t *buffer, uint16_t length, uint16_t offset,
    byteOperationCallback_t callback,CallbackStatus_t *callbackStatus)
{
  if (WriteData(offset, length, (uint8_t*)buffer)== NDEF_OK) {
    callback(callbackStatus,true,buffer,length);
    return true;
  }

  callback(callbackStatus,false,buffer,length);
  return false;
}

/**
  * @brief  This functions reads bytes.
  * @param  byteOffset : the offset of the buffer in bytes.
  * @param  length: the length of the buffer in bytes.
  * @param  buffer : the buffer containing data.
  * @param  callback : a function to call after reading data.
  * @param  callbackStatus : the status of the callback.
  * @retval true if read, false otherwise.
  */       
bool NDefNfcTagM24LR::readByte(const uint16_t byteOffset, const uint16_t length,
    uint8_t *buffer, byteOperationCallback_t callback, CallbackStatus_t *callbackStatus)
{
  
  //first it reads the 2 byte for the length then when it will have the callback it reads the real message
  if (ReadData(byteOffset, length, (uint8_t*)buffer)== NDEF_OK){
    callback(callbackStatus,true,buffer,length);
    return true;
  }

  callback(callbackStatus,false,buffer,length);
  return false;
}

/**
  * @brief  This functions writes bytes.
  * @param  byffer : the buffer containing data.
  * @param  length: the length of the buffer in bytes.
  * @param  offset: the offset of the buffer in bytes.
  * @retval NFCTAG status.
  */
uint16_t NDefNfcTagM24LR::NDefWriteByte(const uint8_t *buffer, uint16_t length, uint16_t offset)
{
    uint16_t status;
    do {
        uint8_t writeLength =(uint8_t) std::min<uint16_t>(0xFF,length);
        status = mDevice.update_binary(offset, writeLength, (uint8_t*)buffer);
        offset+=writeLength;
        buffer+=writeLength;
        length-=writeLength;
    } while (status==NDEF_OK && length!=0);

    return status;
}

/**
  * @brief  This functions reads bytes.
  * @param  byteOffset : the offset of the buffer in bytes.
  * @param  length: the length of the buffer in bytes.
  * @param  buffer : the buffer containing data.
  * @retval NFCTAG status.
  */
uint16_t NDefNfcTagM24LR::NDefReadByte(uint16_t byteOffset, uint16_t length, uint8_t *buffer)
{
    uint16_t status;
    do {
        uint8_t readBuffer = (uint8_t)std::min<uint16_t>(0xFF,length);
        status= mDevice.read_binary(byteOffset, readBuffer, (uint8_t*)buffer);
        byteOffset+=readBuffer;
        buffer+=readBuffer;
        length-=readBuffer;
    } while (status==NDEF_OK && length!=0);

  return status;
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/ 
