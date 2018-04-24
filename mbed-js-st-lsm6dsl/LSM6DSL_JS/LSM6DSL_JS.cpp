/**
 ******************************************************************************
 * @file    LSM6DSL_JS.cpp
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


/* Includes ------------------------------------------------------------------*/

#include "LSM6DSL_JS.h"

#include <stdlib.h>     /* atof */
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

/* Helper function for creating JSON for data */
char *LSM6DSL_JS::make_json(char* str, int32_t *data, char *axes, int data_count)
{
	char *ptr;
	ptr = str;
	str[0] = 0;

	for(int i = 0; i < data_count; i++){
		//printf("len: %i\n", strlen(str));
		if(i == 0){
			sprintf(ptr, "{");
			ptr = &str[strlen(str)];
		}
		else{
			sprintf(ptr, ",");
			ptr = &str[strlen(str)];
		}
		sprintf(ptr, "\"%c\":%i", axes[i], static_cast<int>(data[i]));
		ptr = &str[strlen(str)];
		
	}
	sprintf(ptr, "}");
	return str;
}

/* Class Implementation ------------------------------------------------------*/

/** Constructor
 * @brief	Initializing the component.
 * @param	DevI2c object of helper class which handles the DevI2C peripheral
 */
LSM6DSL_JS::LSM6DSL_JS(DevI2C &devI2c){
	init(devI2c);
}

/** init
 * @brief	Initializing the component.
 * @param	DevI2c object of helper class which handles the DevI2C peripheral
 */
void LSM6DSL_JS::init(DevI2C &devI2c){
	acc_gyro = new LSM6DSLSensor(&devI2c, LSM6DSL_ACC_GYRO_I2C_ADDRESS_HIGH, D4, D5);
	acc_gyro->init(NULL);
	acc_gyro->enable_x();
	acc_gyro->enable_g();
}

/** Constructor
 * @brief	Initializing the component.
 * @param	DevI2c object of helper class which handles the DevI2C peripheral
 * @param	INT1 pin
 * @param	INT2 pin
 */
LSM6DSL_JS::LSM6DSL_JS(DevI2C &devI2c, PinName int1_pin, PinName int2_pin){
	init(devI2c, int1_pin, int2_pin);
}

/** init
 * @brief	Initializing the component.
 * @param	DevI2c object of helper class which handles the DevI2C peripheral
 * @param	INT1 pin
 * @param	INT2 pin
 */
void LSM6DSL_JS::init(DevI2C &devI2c, PinName int1_pin, PinName int2_pin){
	acc_gyro = new LSM6DSLSensor(&devI2c, LSM6DSL_ACC_GYRO_I2C_ADDRESS_HIGH, int1_pin, int2_pin);
	acc_gyro->init(NULL);
	acc_gyro->enable_x();
	acc_gyro->enable_g();
}

/** Constructor
 * @brief	Initializing the component.
 * @param	DevI2c object of helper class which handles the DevI2C peripheral
 * @param	INT1 pin
 * @param	INT2 pin
 * @param	Address
 */
LSM6DSL_JS::LSM6DSL_JS(DevI2C &devI2c, PinName int1_pin, PinName int2_pin, uint8_t address){
	init(devI2c, int1_pin, int2_pin, address);
}

/** init
 * @brief	Initializing the component.
 * @param	DevI2c object of helper class which handles the DevI2C peripheral
 * @param	INT1 pin
 * @param	INT2 pin
 * @param	Address
 */
void LSM6DSL_JS::init(DevI2C &devI2c, PinName int1_pin, PinName int2_pin, uint8_t address){
	acc_gyro = new LSM6DSLSensor(&devI2c, address, int1_pin, int2_pin);
	acc_gyro->init(NULL);
	acc_gyro->enable_x();
	acc_gyro->enable_g();
}

/** Constructor
 * @brief	Initializing the component.
 * @param	SPI object of helper class which handles the SPI peripheral
 * @param	CS pin
 */
LSM6DSL_JS::LSM6DSL_JS(SPI &spi, PinName cs_pin){
	init(spi, cs_pin);
}

/** init
 * @brief	Initializing the component.
 * @param	SPI object of helper class which handles the SPI peripheral
 * @param	CS pin
 */
void LSM6DSL_JS::init(SPI &spi, PinName cs_pin){
	//acc_gyro = new LSM6DSLSensor(&spi, PB_12, NC, PA_2, LSM6DSLSensor::SPI3W);
	acc_gyro = new LSM6DSLSensor(&spi, cs_pin);
	acc_gyro->init(NULL);
	acc_gyro->enable_x();
	acc_gyro->enable_g();
}

/** Constructor
 * @brief	Initializing the component.
 * @param	SPI object of helper class which handles the SPI peripheral
 * @param	CS pin
 * @param	INT1 pin
 * @param	INT2 pin
 * @param	SPI Type
 */
LSM6DSL_JS::LSM6DSL_JS(SPI &spi, PinName cs_pin, PinName int1_pin, PinName int2_pin, int spi_type){
	init(spi, cs_pin, int1_pin, int2_pin, spi_type);
}

/** init
 * @brief	Initializing the component.
 * @param	SPI object of helper class which handles the SPI peripheral
 * @param	CS pin
 * @param	INT1 pin
 * @param	INT2 pin
 * @param	SPI Type
 */
void LSM6DSL_JS::init(SPI &spi, PinName cs_pin, PinName int1_pin, PinName int2_pin, int spi_type){
	//acc_gyro = new LSM6DSLSensor(&spi, PB_12, NC, PA_2, LSM6DSLSensor::SPI3W);
	acc_gyro = new LSM6DSLSensor(&spi, cs_pin, int1_pin, int2_pin, spi_type == 3? LSM6DSLSensor::SPI3W: LSM6DSLSensor::SPI4W);
	acc_gyro->init(NULL);
	acc_gyro->enable_x();
	acc_gyro->enable_g();
}

/** Destructor
 * @brief     Recycle the component.
 *  Deletes the Sensor Object
 */
LSM6DSL_JS::~LSM6DSL_JS(){
	if(acc_gyro != NULL){
		delete acc_gyro;
	}
}

/**
 * @brief  Read ID address of LSM6DSL
 * @retval The ID of the Sensor
 */
uint8_t LSM6DSL_JS::readID(){
	uint8_t result;
	acc_gyro->read_id(&result);
	return result;
}

/**
 * @brief  Get the accleremeter reading from LSM6DSL
 * @retval Accleremeter value
 */
int32_t *LSM6DSL_JS::get_accelerometer_axes(int32_t *axes){
	acc_gyro->get_x_axes(axes);
    printf("LSM6DSL [acc/mg]:        %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);
	return axes;
}

/**
 * @brief  Get the accleremeter reading from LSM6DSL
 * @retval Accleremeter value in JSON string form
 */

char *LSM6DSL_JS::get_accelerometer_axes_json(char *data){
	int32_t axes[3];
  	acc_gyro->get_x_axes(axes);
    //printf("LSM6DSL [acc/mg]:        %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);
	
	char axes_labels[3] = {'x', 'y', 'z'};
	make_json(data, axes, axes_labels, 3);
	
	return data;
}


/**
 * @brief  Get the gyroscope reading from LSM6DSL
 * @retval Gyroscope value
 */
int32_t *LSM6DSL_JS::get_gyroscope_axes(int32_t * axes){
	acc_gyro->get_g_axes(axes);
    printf("LSM6DSL [gyro/mdps]:     %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);
    return axes;
}

/**
 * @brief  Get the gyroscope reading from LSM6DSL
 * @retval Gyroscope value
 */
char *LSM6DSL_JS::get_gyroscope_axes_json(char * data){
	int32_t axes[3];
    acc_gyro->get_g_axes(axes);
    //printf("LSM6DSL [gyro/mdps]:     %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);
    
	char axes_labels[3] = {'x', 'y', 'z'};
	make_json(data, axes, axes_labels, 3);
	
	return data;
}
