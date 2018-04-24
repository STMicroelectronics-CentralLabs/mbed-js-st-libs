/**
 ******************************************************************************
 * @file    LSM303AGR_JS.h
 * @author  ST
 * @version V1.0.0
 * @date    9 October 2017
 * @brief   Implementation of an LSM303AGR Accelerometer and Magnetometer sensor for
 *          use with Javascript.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
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


/* Prevent recursive inclusion -----------------------------------------------*/

#ifndef __LSM303AGR_JS_H__
#define __LSM303AGR_JS_H__

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include "mbed.h"
#include "LSM303AGRMagSensor.h"
#include "LSM303AGRAccSensor.h"

/* Class Declaration ---------------------------------------------------------*/

/**
 * Abstract class of an LSM303AGR Humidity and Temperature sensor for Javascript.
 */
class LSM303AGR_JS {
private:
    /* Helper classes. */
    LSM303AGRMagSensor *magnetometer = NULL;
    LSM303AGRAccSensor *accelerometer = NULL;

public:
    /* Constructors */
    LSM303AGR_JS(){}
    
    //LSM303AGRAccSensor(SPI *spi, PinName cs_pin, PinName int1_pin=NC, PinName int2_pin=NC); // SPI3W ONLY
    void init_acc(SPI &spi, PinName cs_pin);
    void init_acc(SPI &spi, PinName cs_pin, PinName int1_pin, PinName int2_pin);
    
    //LSM303AGRAccSensor(DevI2C *i2c, uint8_t address=LSM303AGR_ACC_I2C_ADDRESS, PinName int1_pin=NC, PinName int2_pin=NC);
    void init_acc(DevI2C &devI2c);
    void init_acc(DevI2C &devI2c, PinName int1_pin, PinName int2_pin);
    void init_acc(DevI2C &devI2c, PinName int1_pin, PinName int2_pin, uint8_t address);
    
    //LSM303AGRMagSensor(SPI *spi, PinName cs_pin, PinName intmag_pin=NC);  // SPI3W ONLY
    void init_mag(SPI &spi, PinName cs_pin);
    void init_mag(SPI &spi, PinName cs_pin, PinName int_pin);
    
    //LSM303AGRMagSensor(DevI2C *i2c, uint8_t address=LSM303AGR_MAG_I2C_ADDRESS, PinName int_pin=NC);
    void init_mag(DevI2C &devI2c);
    void init_mag(DevI2C &devI2c, PinName int_pin);
    void init_mag(DevI2C &devI2c, PinName int_pin, uint8_t address);
    
    
    /* Destructor */
    ~LSM303AGR_JS();
    
    /* Declarations */
    char *make_json(char* str, int32_t *data, char *axes, int data_count);
    uint8_t read_magnetometer_id();
    uint8_t read_accelerometer_id();
    int32_t *get_accelerometer_axes(int32_t *);
    char *get_accelerometer_axes_json(char *);
    int32_t *get_magnetometer_axes(int32_t *);
    char *get_magnetometer_axes_json(char *);
    
};

#endif