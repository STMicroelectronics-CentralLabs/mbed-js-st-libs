/**
 ******************************************************************************
 * @file    LPS22HB_JS.cpp
 * @author  ST
 * @version V1.0.0
 * @date    9 October 2017
 * @brief   Implementation of an LPS22HB Pressure and Temperature sensor for use
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

#include "LPS22HB_JS.h"

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
 * @param	DevI2c object of helper class which handles the DevI2C peripheral
 */
LPS22HB_JS::LPS22HB_JS(DevI2C &devI2c){
	init(devI2c);
}

/** init
 * @brief	Initializing the component.
 * @param	DevI2c object of helper class which handles the DevI2C peripheral
 */
void LPS22HB_JS::init(DevI2C &devI2c){
	press_temp = new LPS22HBSensor(&devI2c);
	press_temp->init(NULL);
	press_temp->enable();
}

/** Constructor
 * @brief	Initializing the component.
 * @param	DevI2c object of helper class which handles the DevI2C peripheral
 * @param	Address
 * @param	INT pin
 */
LPS22HB_JS::LPS22HB_JS(DevI2C &devI2c, uint8_t address, PinName int_pin){
	init(devI2c, address, int_pin);
}

/** init
 * @brief	Initializing the component.
 * @param	DevI2c object of helper class which handles the DevI2C peripheral
 * @param	Address
 * @param	INT pin
 */
void LPS22HB_JS::init(DevI2C &devI2c, uint8_t address, PinName int_pin){
	press_temp = new LPS22HBSensor(&devI2c, address, int_pin);
	press_temp->init(NULL);
	press_temp->enable();
}

/** Constructor
 * @brief	Initializing the component.
 * @param	SPI object of helper class which handles the SPI peripheral
 * @param	CS pin
 */
LPS22HB_JS::LPS22HB_JS(SPI &spi, PinName cs_pin){
	init(spi, cs_pin);
}

/** init
 * @brief	Initializing the component.
 * @param	SPI object of helper class which handles the SPI peripheral
 * @param	CS pin
 */
void LPS22HB_JS::init(SPI &spi, PinName cs_pin){
	press_temp = new LPS22HBSensor(&spi, cs_pin);
	press_temp->init(NULL);
	press_temp->enable();
}

/** Constructor
 * @brief	Initializing the component.
 * @param	SPI object of helper class which handles the SPI peripheral
 * @param	CS pin
 * @param	INT pin
 * @param	SPI type
 */
LPS22HB_JS::LPS22HB_JS(SPI &spi, PinName cs_pin, PinName int_pin, int spi_type){
	init(spi, cs_pin, int_pin, spi_type);
}

/** init
 * @brief	Initializing the component.
 * @param	SPI object of helper class which handles the SPI peripheral
 * @param	CS pin
 * @param	INT pin
 * @param	SPI type
 */
void LPS22HB_JS::init(SPI &spi, PinName cs_pin, PinName int_pin, int spi_type){
	press_temp = new LPS22HBSensor(&spi, cs_pin, int_pin, spi_type == 3? LPS22HBSensor::SPI3W: LPS22HBSensor::SPI4W);
	press_temp->init(NULL);
	press_temp->enable();
}

/** Destructor
 * @brief	Recycling the component. Deletes the Sensor Object
 */
LPS22HB_JS::~LPS22HB_JS(){
	if(press_temp != NULL){
		delete press_temp;
	}
}

/** readID
 * @brief	Read ID address of LPS22HB
 * @retval	The ID of the Sensor
 */
uint8_t LPS22HB_JS::readID(){
	uint8_t result;
	press_temp->read_id(&result);
	return result;
}

/** get_temperature
 * @brief	Gets the temperature reading from LPS22HB
 * @retval	Temperature value
 */
float LPS22HB_JS::get_temperature(){
	float value;
	press_temp->get_temperature(&value);
	return value;
}

/** get_temperature_string
 * @brief	Gets the temperature reading from LPS22HB
 * @retval	Temperature value in string form
 */
char *LPS22HB_JS::get_temperature_string(char *buffer){
	float value;
	press_temp->get_temperature(&value);
    print_double(buffer, value);
	return buffer;
}

/** get_pressure
 * @brief	Gets the pressure reading from LPS22HB
 * @retval	Pressure value
 */
float LPS22HB_JS::get_pressure(){
	float value;
	press_temp->get_pressure(&value);
	return value;
}

/** get_pressure_string
 * @brief	Gets the pressure reading from LPS22HB
 * @retval	pressure value in string form
 */
char *LPS22HB_JS::get_pressure_string(char *buffer){
	float value;
	press_temp->get_pressure(&value);
    print_double(buffer, value);
	return buffer;
}