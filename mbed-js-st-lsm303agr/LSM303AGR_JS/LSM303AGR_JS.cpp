/**
 ******************************************************************************
 * @file    LSM303AGR_JS.cpp
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


/* Includes ------------------------------------------------------------------*/

#include "LSM303AGR_JS.h"
#include <inttypes.h>
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

/* Helper function for creating JSON for data */
char *LSM303AGR_JS::make_json(char* str, int32_t *data, char *axes, int data_count)
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

/** init_acc
 * @brief	Initializing the component.
 * @param	SPI object of an helper class which handles the SPI peripheral
 * @param	CS pin
 */
void LSM303AGR_JS::init_acc(SPI &spi, PinName cs_pin){
	accelerometer = new LSM303AGRAccSensor (&spi, cs_pin);
	accelerometer->init(NULL);
	accelerometer->enable();
}

/** init_acc
 * @brief	Initializing the component.
 * @param	SPI object of an helper class which handles the SPI peripheral
 * @param	CS pin
 * @param	INT1 pin
 * @param	INT2 pin
 */
void LSM303AGR_JS::init_acc(SPI &spi, PinName cs_pin, PinName int1_pin, PinName int2_pin){
	accelerometer = new LSM303AGRAccSensor (&spi, cs_pin, int1_pin, int2_pin);
	accelerometer->init(NULL);
	accelerometer->enable();
}

/** init_acc
 * @brief	Initializing the component.
 * @param	DevI2c object of an helper class which handles the DevI2C peripheral
 */
void LSM303AGR_JS::init_acc(DevI2C &devI2c){
	accelerometer = new LSM303AGRAccSensor (&devI2c);
	accelerometer->init(NULL);
	accelerometer->enable();
}

/** init_acc
 * @brief	Initializing the component.
 * @param	DevI2c object of an helper class which handles the DevI2C peripheral
 * @param	INT1 pin
 * @param	INT2 pin
 */
void LSM303AGR_JS::init_acc(DevI2C &devI2c, PinName int1_pin, PinName int2_pin){
	accelerometer = new LSM303AGRAccSensor (&devI2c, LSM303AGR_ACC_I2C_ADDRESS, int1_pin, int2_pin);
	accelerometer->init(NULL);
	accelerometer->enable();
}

/** init_acc
 * @brief	Initializing the component.
 * @param	DevI2c object of an helper class which handles the DevI2C peripheral
 * @param	INT1 pin
 * @param	INT2 pin
 * @param	Address
 */
void LSM303AGR_JS::init_acc(DevI2C &devI2c, PinName int1_pin, PinName int2_pin, uint8_t address){
	accelerometer = new LSM303AGRAccSensor (&devI2c, address, int1_pin, int2_pin);
	accelerometer->init(NULL);
	accelerometer->enable();
}

/** init_mag
 * @brief	Initializing the component.
 * @param	SPI object of an helper class which handles the SPI peripheral
 * @param	CS pin
 */
void LSM303AGR_JS::init_mag(SPI &spi, PinName cs_pin){
	magnetometer = new LSM303AGRMagSensor (&spi, cs_pin);
	magnetometer->init(NULL);
	magnetometer->enable();
}

/** init_mag
 * @brief	Initializing the component.
 * @param	SPI object of an helper class which handles the SPI peripheral
 * @param	CS pin
 * @param	INT pin
 */
void LSM303AGR_JS::init_mag(SPI &spi, PinName cs_pin, PinName int_pin){
	magnetometer = new LSM303AGRMagSensor (&spi, cs_pin, int_pin);
	magnetometer->init(NULL);
	magnetometer->enable();
}

/** init_mag
 * @brief	Initializing the component.
 * @param	DevI2c object of an helper class which handles the DevI2C peripheral
 */
void LSM303AGR_JS::init_mag(DevI2C &devI2c){
	magnetometer = new LSM303AGRMagSensor (&devI2c);
	magnetometer->init(NULL);
	magnetometer->enable();
}

/** init_mag
 * @brief	Initializing the component.
 * @param	DevI2c object of an helper class which handles the DevI2C peripheral
 * @param	INT pin
 */
void LSM303AGR_JS::init_mag(DevI2C &devI2c, PinName int_pin){
	magnetometer = new LSM303AGRMagSensor (&devI2c, LSM303AGR_MAG_I2C_ADDRESS, int_pin);
	magnetometer->init(NULL);
	magnetometer->enable();
}

/** init_mag
 * @brief	Initializing the component.
 * @param	DevI2c object of an helper class which handles the DevI2C peripheral
 * @param	INT pin
 * @param	Address
 */
void LSM303AGR_JS::init_mag(DevI2C &devI2c, PinName int_pin, uint8_t address){
	magnetometer = new LSM303AGRMagSensor (&devI2c, address, int_pin);
	magnetometer->init(NULL);
	magnetometer->enable();
}

/** Destructor
 * @brief     Recycle the component.
 *  Deletes the Sensor Object
 */
LSM303AGR_JS::~LSM303AGR_JS(){
	if(magnetometer != NULL){
		delete magnetometer;
	}
	if(accelerometer != NULL){
		delete accelerometer;
	}
}

/**
 * @brief  Read ID address of LSM303AGR Magnetometer
 * @retval The ID of the Sensor
 */
uint8_t LSM303AGR_JS::read_magnetometer_id(){
	uint8_t result;
	magnetometer->read_id(&result);
	return result;
}

/**
 * @brief  Read ID address of LSM303AGR Accelerometer
 * @retval The ID of the Sensor
 */
uint8_t LSM303AGR_JS::read_accelerometer_id(){
	uint8_t result;
	accelerometer->read_id(&result);
	return result;
}

/**
 * @brief  Get the accleremeter reading from LSM303AGR
 * @retval Accleremeter value
 */
int32_t *LSM303AGR_JS::get_accelerometer_axes(int32_t *axes){
	accelerometer->get_x_axes(axes);
    printf("LSM303AGR [acc/mg]:        %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);
	return axes;
}

/**
 * @brief  Get the accleremeter reading from LSM303AGR
 * @retval Accleremeter value in JSON string form
 */

char *LSM303AGR_JS::get_accelerometer_axes_json(char *data){
	int32_t axes[3];
  	accelerometer->get_x_axes(axes);
    //printf("LSM303AGR [acc/mg]:        %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);
	
	char axes_labels[3] = {'x', 'y', 'z'};
	make_json(data, axes, axes_labels, 3);
	
	return data;
}


/**
 * @brief  Get the Magnetometer reading from LSM303AGR
 * @retval Magnetometer value
 */
int32_t *LSM303AGR_JS::get_magnetometer_axes(int32_t *axes){
	magnetometer->get_m_axes(axes);
    printf("LSM303AGR [mag/mgauss]:     %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);
    return axes;
}

/**
 * @brief  Get the Magnetometer reading from LSM303AGR
 * @retval Magnetometer value
 */
char *LSM303AGR_JS::get_magnetometer_axes_json(char * data){
	int32_t axes[3];
    magnetometer->get_m_axes(axes);
    //printf("LSM303AGR [mag/mgauss]:     %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);
    
	char axes_labels[3] = {'x', 'y', 'z'};
	make_json(data, axes, axes_labels, 3);
	
	return data;
}
