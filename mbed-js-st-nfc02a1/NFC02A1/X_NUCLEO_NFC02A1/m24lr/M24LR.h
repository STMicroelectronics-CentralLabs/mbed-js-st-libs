/**
  ******************************************************************************
  * @file       m24lr.h
  * @author     AMG Central Lab
  * @version    V2.0.0
  * @date       19 May 2017
  * @brief      header file for M24LR driver .
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


#ifndef __M24LR_H
#define __M24LR_H

#include "DevI2C.h"
#include "Nfc.h"
#include "NDefNfcTag.h"
#include "NDefNfcTagM24LR.h"

//#include "lib_NDEF_URI.h"
  /* Exported constants --------------------------------------------------------*/
/** @defgroup M24LR_Exported_Constants
  * @{
  */
#define I_AM_M24LR04            0x5A
#define I_AM_M24LR16            0x4E
#define I_AM_M24LR64            0x5E

#ifndef NULL
#define NULL      (void *) 0
#endif

#define M24LR_PAGEWRITE_NBBYTE  4

#define M24LR_ADDR_DATA_I2C     0xA6
#define M24LR_ADDR_SYST_I2C     0xAE
#define M24LR_I2C_TIMEOUT       200 /* I2C Time out (ms), this is the maximum time needed by M24LR to complete any command */

#define M24LR_IT_BUSY_MASK      0x01
#define M24LR_IT_WIP_MASK       0x02

/* Registers address */
#define M24LR_SSS_REG           0x0000
#define M24LR_LOCK_REG          0x0800
#define M24LR_I2C_PWD_REG       0x0900
#define M24LR_CFG_REG           0x0910
#define M24LR_AFI_REG           0x0912
#define M24LR_DSFID_REG         0x0913
#define M24LR_UID_REG           0x0914
#define M24LR_ICREF_REG         0x091C
#define M24LR_MEMSIZE_REG       0x091D
#define M24LR_CTRL_REG          0x0920

/* Registers mask */
#define M24LR_SSS_LOCK_MASK     0x01
#define M24LR_SSS_RW_MASK       0x06
#define M24LR_SSS_PASSCTRL_MASK 0x18
#define M24LR_LOCK_MASK         0x0F

#define M24LR_CFG_EHCFG0_MASK   0x01
#define M24LR_CFG_EHCFG1_MASK   0x02
#define M24LR_CFG_EHMODE_MASK   0x04
#define M24LR_CFG_WIPBUSY_MASK  0x08

#define M24LR_CTRL_EHEN_MASK    0x01
#define M24LR_CTRL_FIELD_MASK   0x02
#define M24LR_CTRL_TPROG_MASK   0x80


/**
 * @brief  NFCTAG status enumerator definition
 */
typedef enum
{
  NFCTAG_OK      = 0,
  NFCTAG_ERROR   = 1,
  NFCTAG_BUSY    = 2,
  NFCTAG_TIMEOUT = 3
} NFCTAG_StatusTypeDef;
 
/**
 * @brief  M24LR VOUT Configuration enumerator definition
 */
typedef enum
{
  M24LR_EH_Cfg_6MA = 0,
  M24LR_EH_Cfg_3MA,
  M24LR_EH_Cfg_1MA,
  M24LR_EH_Cfg_300UA
} M24LR_EH_CFG_VOUT;

/**
 * @brief  M24LR FIELD status enumerator definition
 */
typedef enum
{
  M24LR_FIELD_OFF = 0,
  M24LR_FIELD_ON
} M24LR_FIELD_STATUS;

/**
 * @brief  M24LR TT-PROG status enumerator definition
 */
typedef enum
{
  M24LR_T_PROG_NO = 0,
  M24LR_T_PROG_OK
} M24LR_T_PROG_STATUS;

/**
 * @brief  M24LR Energy Harvesting status enumerator definition
 */
typedef enum
{
  M24LR_EH_DISABLE = 0,
  M24LR_EH_ENABLE
} M24LR_EH_STATUS;

/**
 * @brief  M24LR Energy Harvesting mode enumerator definition
 */
typedef enum
{
  M24LR_EH_MODE_ENABLE = 0,
  M24LR_EH_MODE_DISABLE
} M24LR_EH_MODE_STATUS;

/**
 * @brief  M24LR GPO status enumerator definition
 */
typedef enum
{
  M24LR_GPO_BUSY = 0,
  M24LR_GPO_WIP
} M24LR_GPO_STATUS;

/**
 * @brief  M24LR Memory information structure definition
 */
typedef struct
{
  uint8_t BlockSize;
  uint16_t Mem_Size;
} M24LR_Mem_Size;

/**
 * @brief  M24LR I2C Write Lock register structure definition
 */
typedef struct
{
  uint8_t sectors_7_0;
  uint8_t sectors_15_8;
  uint8_t sectors_23_16;
  uint8_t sectors_31_24;
  uint8_t sectors_39_32;
  uint8_t sectors_47_40;
  uint8_t sectors_55_48;
  uint8_t sectors_63_56;
} M24LR_Lock_Sectors;

/**
 * @brief  M24LR UID information structure definition
 */
typedef struct
{
  uint32_t MSB_UID;
  uint32_t LSB_UID;
} M24LR_UID;

/**
 * @brief  M24LR Sector Security register structure definition
 */
typedef struct
{
  uint8_t SectorLock;
  uint8_t RW_Protection;
  uint8_t PassCtrl;
} M24LR_SECTOR_SEC;

/**
 * @brief  M24LR class.
 */
class M24LR : public Nfc {
public:
    NFCTAG_StatusTypeDef i2c_init( void );
    NFCTAG_StatusTypeDef i2c_read_id( uint8_t * const pICRef );
    NFCTAG_StatusTypeDef i2c_is_device_ready( const uint32_t Trials );
    NFCTAG_StatusTypeDef i2c_configure_GPO( const uint16_t ITConf );
    NFCTAG_StatusTypeDef i2c_get_GPO_status( uint16_t * const pGPOStatus );
    NFCTAG_StatusTypeDef i2c_read_data( uint8_t * const pData, const uint16_t TarAddr, const uint16_t NbByte );
    NFCTAG_StatusTypeDef i2c_write_data( const uint8_t * const pData, const uint16_t TarAddr, const uint16_t NbByte );
    NFCTAG_StatusTypeDef i2c_read_register( uint8_t * const pData, const uint16_t TarAddr, const uint16_t NbByte );
    NFCTAG_StatusTypeDef i2c_write_register( const uint8_t * const pData, const uint16_t TarAddr, const uint16_t NbByte );

    /* Extended Functions */
    NFCTAG_StatusTypeDef i2c_read_UID( M24LR_UID * const pUid );
    NFCTAG_StatusTypeDef i2c_read_DSFID( uint8_t * const pDsfid );
    NFCTAG_StatusTypeDef i2c_read_AFI( uint8_t * const pAfi );
    NFCTAG_StatusTypeDef i2c_read_I2C_lock_sector( M24LR_Lock_Sectors * const pLock_sector );
    NFCTAG_StatusTypeDef i2c_I2C_lock_sector( const uint8_t Sector );
    NFCTAG_StatusTypeDef i2c_I2C_unlock_sector( const uint8_t Sector );
    NFCTAG_StatusTypeDef i2c_present_I2C_password( const uint32_t PassWord );
    NFCTAG_StatusTypeDef i2c_write_I2C_password( const uint32_t PassWord );
    NFCTAG_StatusTypeDef i2c_read_SSSx( const uint8_t SectorNb, M24LR_SECTOR_SEC * const pData );
    NFCTAG_StatusTypeDef i2c_write_SSSx( const uint8_t SectorNb, const M24LR_SECTOR_SEC * const pData );
    NFCTAG_StatusTypeDef i2c_read_mem_size( M24LR_Mem_Size * const pSizeInfo );
    NFCTAG_StatusTypeDef i2c_get_RF_WIP_busy( M24LR_GPO_STATUS * const pRf_Wip_Busy );
    NFCTAG_StatusTypeDef i2c_setRF_Busy( void );
    NFCTAG_StatusTypeDef i2c_set_RF_WIP( void );
    NFCTAG_StatusTypeDef i2c_read_EH_mode( M24LR_EH_MODE_STATUS * const pEH_mode );
    NFCTAG_StatusTypeDef i2c_enable_EH_mode( void );
    NFCTAG_StatusTypeDef i2c_disable_EH_mode( void );
    NFCTAG_StatusTypeDef i2c_read_EH_cfg( M24LR_EH_CFG_VOUT * const pEH_Cfg );
    NFCTAG_StatusTypeDef i2c_write_EH_cfg( const M24LR_EH_CFG_VOUT EH_Cfg );
    NFCTAG_StatusTypeDef i2c_get_EH( M24LR_EH_STATUS * const pEH_Val );
    NFCTAG_StatusTypeDef i2c_set_EH( void );
    NFCTAG_StatusTypeDef i2c_reset_EH( void );
    NFCTAG_StatusTypeDef i2c_get_RF_field( M24LR_FIELD_STATUS * const pRF_Field );
    NFCTAG_StatusTypeDef i2c_get_TProg( M24LR_T_PROG_STATUS * const pT_Prog );
    
    void enable_energy_harvesting( void );
    NFCTAG_StatusTypeDef initialization( void );
    
    virtual int read_binary(uint16_t Offset, uint8_t NbByteToRead, uint8_t *pBufferRead) {
        return  i2c_read_data( pBufferRead, Offset, NbByteToRead );
        
    }
    
    virtual int update_binary(uint16_t Offset, uint8_t NbByteToWrite,uint8_t *pDataToWrite) {
        return i2c_write_data( pDataToWrite, Offset, NbByteToWrite );
    }
    
    M24LR(uint8_t const address, uint8_t const addressData, DevI2C &devI2C ):
      NDefTagUtil(*this), i2c_address_syst(address), i2c_address_data(addressData), dev_I2C(devI2C) {}

    NDefLib::NDefNfcTag& get_NDef_tag(){
      return NDefTagUtil;
    }

    virtual int init(void *ptr) {
        (void)ptr;
        return i2c_init();
    }

    virtual int read_id(uint8_t *id) {
        return i2c_read_id(id);
    }

private:
    static uint8_t NfctagInitialized;
    /* Object implementing the interface to use the NDefLib. */
    NDefNfcTagM24LR NDefTagUtil;
    
    uint8_t i2c_address_syst;
    uint8_t i2c_address_data;
    DevI2C &dev_I2C;
};

#endif /* __M24LR_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
