/**
 ******************************************************************************
 * @file    HTS221_JS.h
 * @author  ST
 * @version V1.0.0
 * @date    9 October 2017
 * @brief   Implementation of an HTS221 Humidity and Temperature sensor for use
 *          with Javascript.
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

#ifndef __HTS221_JS_H__
#define __HTS221_JS_H__

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include "mbed.h"
#include "HTS221Sensor.h"

/* Class Declaration ---------------------------------------------------------*/

/**
 * Abstract class of an HTS221 Humidity and Temperature sensor for Javascript.
 */
class HTS221_JS {
private:
    /* Helper classes. */
    HTS221Sensor *hum_temp = NULL;

public:
    /* Constructors */
    HTS221_JS(){}
    
    HTS221_JS(DevI2C &devI2c);
    void init(DevI2C &devI2c);
    HTS221_JS(DevI2C &devI2c, uint8_t address, PinName drdy_pin);
    void init(DevI2C &devI2c, uint8_t address, PinName drdy_pin);
    
    HTS221_JS(SPI &spi);
    void init(SPI &spi);
    HTS221_JS(SPI &spi, PinName cs_pin, PinName drdy_pin);
    void init(SPI &spi, PinName cs_pin, PinName drdy_pin);
    
    /* Destructor */
    ~HTS221_JS();
    
    /* Declarations */
    uint8_t readID();
    float get_temperature();
    char *get_temperature_string(char *);
    float get_humidity();
    char *get_humidity_string(char *);
    void led_on(DigitalOut &led) {
        //printf("led status: %d\n", led);
        led = 1;
        //led = !led;
    }
};

#endif