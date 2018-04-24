/**
 ******************************************************************************
 * @file    HTS221_JS.cpp
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


/* Includes ------------------------------------------------------------------*/

#include "HTS221_JS.h"

#include <stdlib.h>     /* atoi */
#include "mbed.h"

/* Helper function for printing floats & doubles */
static char *print_double(char* str, double v, int decimalDigits=2)
{
	int i = 1;
	int intPart, fractPart;
	int len;
	char *ptr;

	/* prepare decimal digits multiplicator */
	for (;decimalDigits!=0; i*=10, decimalDigits--);

	/* calculate integer & fractinal parts */
	intPart = (int)v;
	fractPart = (int)((v-(double)(int)v)*i);

	/* fill in integer part */
	sprintf(str, "%i.", intPart);

	/* prepare fill in of fractional part */
	len = strlen(str);
	ptr = &str[len];

	/* fill in leading fractional zeros */
	for (i/=10;i>1; i/=10, ptr++) {
		if (fractPart >= i) {
			break;
		}
		*ptr = '0';
	}

	/* fill in (rest of) fractional part */
	sprintf(ptr, "%i", fractPart);

	return str;
}

/* Class Implementation ------------------------------------------------------*/

/** Constructor
 * @brief	Initializing the component.
 * @param	devI2c object of an helper class which handles the DevI2C peripheral
 */
HTS221_JS::HTS221_JS(DevI2C &devI2c){
	init(devI2c);
}

/** init
 * @brief	Initializing the component.
 * @param	devI2c object of an helper class which handles the DevI2C peripheral
 */
void HTS221_JS::init(DevI2C &devI2c){
	hum_temp = new HTS221Sensor(&devI2c);
	hum_temp->init(NULL);
	hum_temp->enable();
}

/** Constructor
 * @brief	Initializing the component.
 * @param	devI2c object of an helper class which handles the DevI2C peripheral
 * @param	address
 * @param	drdy pin
 */
HTS221_JS::HTS221_JS(DevI2C &devI2c, uint8_t address, PinName drdy_pin){
	init(devI2c, address, drdy_pin);
}

/** init
 * @brief	Initializing the component.
 * @param	devI2c object of an helper class which handles the DevI2C peripheral
 * @param	address
 * @param	drdy pin
 */
void HTS221_JS::init(DevI2C &devI2c, uint8_t address, PinName drdy_pin){
	hum_temp = new HTS221Sensor(&devI2c, address, drdy_pin);
	hum_temp->init(NULL);
	hum_temp->enable();
}

/** Constructor
 * @brief	Initializing the component.
 * @param	spi object of an helper class which handles the SPI peripheral
 */
HTS221_JS::HTS221_JS(SPI &spi){
	init(spi);
}

/** init
 * @brief	Initializing the component.
 * @param	spi object of an helper class which handles the SPI peripheral
 */
void HTS221_JS::init(SPI &spi){
	hum_temp = new HTS221Sensor(&spi);
	hum_temp->init(NULL);
	hum_temp->enable();
}

/** Constructor
 * @brief	Initializing the component.
 * @param	spi object of an helper class which handles the SPI peripheral
 * @param	cs pin
 * @param	drdy pin
 */
HTS221_JS::HTS221_JS(SPI &spi, PinName cs_pin, PinName drdy_pin){
	init(spi, cs_pin, drdy_pin);
}

/** init
 * @brief	Initializing the component.
 * @param	spi object of an helper class which handles the SPI peripheral
 * @param	cs pin
 * @param	drdy pin
 */
void HTS221_JS::init(SPI &spi, PinName cs_pin, PinName drdy_pin){
	hum_temp = new HTS221Sensor(&spi, cs_pin, drdy_pin);
	hum_temp->init(NULL);
	hum_temp->enable();
}

/** Destructor
 * @brief	Recycle the component.
 *  Deletes	the Sensor Object
 */
HTS221_JS::~HTS221_JS(){
	if(hum_temp != NULL){
		delete hum_temp;
	}
}

/**
 * @brief	Read ID address of HTS221
 * @retval	The ID of the Sensor
 */
uint8_t HTS221_JS::readID(){
	uint8_t result;
	hum_temp->read_id(&result);
	return result;
}

/**
 * @brief	Get the temperature reading from HTS221
 * @retval	Temperature value
 */
float HTS221_JS::get_temperature(){
	float value;
	hum_temp->get_temperature(&value);
    return value;
}

/**
 * @brief	Get the temperature reading from HTS221
 * @retval	Temperature value in string
 */
char *HTS221_JS::get_temperature_string(char *buffer){
	float value;
	hum_temp->get_temperature(&value);
    print_double(buffer, value);
	return buffer;
}

/**
 * @brief	Get the humidity reading from HTS221
 * @retval	Humidity value
 */
float HTS221_JS::get_humidity(){
	float value;
	hum_temp->get_humidity(&value);
    return value;
}

/**
 * @brief	Get the humidity reading from HTS221
 * @retval	Humidity value in string
 */
char *HTS221_JS::get_humidity_string(char *buffer){
	float value;
	hum_temp->get_humidity(&value);
    print_double(buffer, value);
	return buffer;
}