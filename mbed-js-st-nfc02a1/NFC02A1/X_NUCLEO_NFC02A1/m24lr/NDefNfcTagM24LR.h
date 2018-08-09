/**
  ******************************************************************************
  * @file       NdefNfcTagM24LR.h
  * @author     AMG Central Lab
  * @version    V2.0.0
  * @date       19 May 2017
  * @brief      M24LR specific NDefLib derived class
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
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

#ifndef X_NUCLEO_NFC02A1_M24LR_NDEFNFCTAGM24LR_H_
#define X_NUCLEO_NFC02A1_M24LR_NDEFNFCTAGM24LR_H_

#include <cstdlib>
#include <stdint.h>

#include "NDefNfcTag.h"
#include "Nfc.h"


#define NDEF_OK                     0
#define NDEF_ERROR                  1
#define NDEF_ERROR_MEMORY_TAG       2
#define NDEF_ERROR_MEMORY_INTERNAL  3
#define NDEF_ERROR_LOCKED           4
#define NDEF_ERROR_NOT_FORMATED     5

/**
 * Helper class to use the NDefLib
 */


class NDefNfcTagM24LR: public NDefLib::NDefNfcTag {

public:

    /**
     *
     * @param device device to use
     */
    NDefNfcTagM24LR(Nfc &device) :
        NDefLib::NDefNfcTag(),
        mDevice(device),mIsSessionOpen(false),
        mMaxReadBytes(0xFF), mMaxWriteBytes(0xFF){}

    virtual bool open_session(bool force = false);

    virtual bool close_session();

    virtual bool is_session_open(){
        return mIsSessionOpen;
    }
        
    /**
    * Close the open session.
    */
    virtual ~NDefNfcTagM24LR() {
        if(is_session_open())
            close_session();
    }//~NDefNfcTagM24SR

    protected:
        virtual bool writeByte(const uint8_t *buffer, uint16_t length,uint16_t offset,
            byteOperationCallback_t callback,CallbackStatus_t *callbackStatus);

        virtual bool readByte(const uint16_t byteOffset, const uint16_t byteLength,
            uint8_t *buffer, byteOperationCallback_t callback,CallbackStatus_t *callbackStatus);

    private:
        uint16_t NDefWriteByte(const uint8_t *buffer, uint16_t length,uint16_t offset);
        uint16_t NDefReadByte(uint16_t byteOffset, uint16_t length, uint8_t *buffer);

        uint16_t ReadData( uint16_t Offset , uint16_t DataSize , uint8_t* pData );
        uint16_t WriteData( uint16_t Offset , uint32_t DataSize , uint8_t *pData );
        uint16_t NfcType5_WriteCCFile( const uint8_t * const pCCBuffer );
        uint16_t NfcType5_ReadCCFile( uint8_t * const pCCBuffer );
        uint16_t NfcType5_TT5Init( void );
        uint16_t NfcType5_NDEFDetection( void );
        Nfc &mDevice;

        /**
         * true if the session is open
         */
        bool mIsSessionOpen;

        /**
        * Max length for a read operation
        */
        uint16_t mMaxReadBytes;

        /**
        * Max length for a write operation
        */
        uint16_t mMaxWriteBytes;
        typedef enum
        {
          TT5_NO_NDEF = 0,
          TT5_INITIALIZED,
          TT5_READ_WRITE,
          TT5_READ
        } TT5_State;
        
        /**
          * @brief  CCfile structure
          */
        typedef struct
        {
          uint8_t MagicNumber;  /* Magic Number should be E1h or E2h */
          uint8_t Version;
          uint8_t MemorySize;
          uint8_t TT5Tag;
          uint8_t rsved1;
          uint8_t rsved2;
          uint16_t ExtMemorySize;
          TT5_State State;
          uint32_t NDEF_offset;
        } sCCFileInfo;
                
        sCCFileInfo CCFileStruct;
    };

#endif /* X_NUCLEO_NFC02A1_M24LR_NDEFNFCTAGM24LR_H_ */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/ 
