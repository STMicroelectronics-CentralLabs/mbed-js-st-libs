/**
 ******************************************************************************
 * @file    LSM6DSL_JS.h
 * @author  ST
 * @version V1.0.0
 * @date    9 October 2017
 * @brief   Implementation of an LSM6DSL Accelerometer and gyroscope sensor for
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

#ifndef __LSM6DSL_JS_H__
#define __LSM6DSL_JS_H__

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include "mbed.h"
#include "LSM6DSLSensor.h"

/* Class Declaration ---------------------------------------------------------*/

/**
 * Abstract class of an LSM6DSL Humidity and Temperature sensor for Javascript.
 */
class LSM6DSL_JS {
private:
    /* Helper classes. */
    LSM6DSLSensor *acc_gyro = NULL;

public:
    /* Constructors */
    LSM6DSL_JS(){}
    
    LSM6DSL_JS(DevI2C &devI2c);
    void init(DevI2C &devI2c);
    LSM6DSL_JS(DevI2C &devI2c, PinName int1_pin, PinName int2_pin);
    void init(DevI2C &devI2c, PinName int1_pin, PinName int2_pin);
    LSM6DSL_JS(DevI2C &devI2c, PinName int1_pin, PinName int2_pin, uint8_t address);
    void init(DevI2C &devI2c, PinName int1_pin, PinName int2_pin, uint8_t address);
    
    LSM6DSL_JS(SPI &spi, PinName cs_pin);
    void init(SPI &spi, PinName cs_pin);
    LSM6DSL_JS(SPI &spi, PinName cs_pin, PinName int1_pin, PinName int2_pin, int spi_type);
    void init(SPI &spi, PinName cs_pin, PinName int1_pin, PinName int2_pin, int spi_type);
    
    /* Destructor */
    ~LSM6DSL_JS();
    
    /* Declarations */
    char *make_json(char* str, int32_t *data, char *axes, int data_count);
    uint8_t readID();
    int32_t *get_accelerometer_axes(int32_t *);
    char *get_accelerometer_axes_json(char *);
    int32_t *get_gyroscope_axes(int32_t *);
    char *get_gyroscope_axes_json(char *);
    
};

#endif