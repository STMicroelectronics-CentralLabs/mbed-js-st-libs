/**
 ******************************************************************************
 * @file    LSM6DSL_JS-js.cpp
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

#include "jerryscript-mbed-util/logging.h"
#include "jerryscript-mbed-library-registry/wrap_tools.h"

// Load the library that we'll wrap
#include "LSM6DSL_JS.h"

#include "mbed.h"

#ifdef TARGET_SENSOR_TILE
mbed::Serial pc1((PinName)0x2C, (PinName)0x32);
#define printf(...) pc1.printf(__VA_ARGS__)
#endif

/* Class Implementation ------------------------------------------------------*/

/**
 * LSM6DSL_JS#destructor
 * Called if/when the LSM6DSL_JS is GC'ed.
 */
void NAME_FOR_CLASS_NATIVE_DESTRUCTOR(LSM6DSL_JS)(void *void_ptr) {
    delete static_cast<LSM6DSL_JS*>(void_ptr);
}


/**
 * Type infomation of the native LSM6DSL_JS pointer
 * Set LSM6DSL_JS#destructor as the free callback.
 */
static const jerry_object_native_info_t native_obj_type_info = {
    .free_cb = NAME_FOR_CLASS_NATIVE_DESTRUCTOR(LSM6DSL_JS)
};


/**
 * LSM6DSL_JS#init_spi (native JavaScript method)
 * @brief Initializes the sensor using SPI interface
 * @param SPI object of helper class which handles the SPI peripheral
 * @param CS pin
 * @param INT1 pin
 * @param INT2 pin
 * @param SPI type
 */
DECLARE_CLASS_FUNCTION(LSM6DSL_JS, init_spi) {
    CHECK_ARGUMENT_COUNT(LSM6DSL_JS, init_spi, (args_count == 2 || args_count == 5));
    CHECK_ARGUMENT_TYPE_ALWAYS(LSM6DSL_JS, init_spi, 0, object);
    CHECK_ARGUMENT_TYPE_ALWAYS(LSM6DSL_JS, init_spi, 1, number);
    CHECK_ARGUMENT_TYPE_ON_CONDITION(LSM6DSL_JS, init_spi, 2, number, args_count == 5);
    CHECK_ARGUMENT_TYPE_ON_CONDITION(LSM6DSL_JS, init_spi, 3, number, args_count == 5);
    CHECK_ARGUMENT_TYPE_ON_CONDITION(LSM6DSL_JS, init_spi, 4, number, args_count == 5);

    // Unwrap native LSM6DSL_JS object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native LSM6DSL_JS pointer");
    }

    LSM6DSL_JS *native_ptr = static_cast<LSM6DSL_JS*>(void_ptr);
 
    // Unwrap arguments
    void *spi_ptr;
    const jerry_object_native_info_t *spi_type_ptr;
    bool spi_has_ptr = jerry_get_object_native_pointer(args[0], &spi_ptr, &spi_type_ptr);

    // Check if we have the spi pointer
    if (!spi_has_ptr) {
        printf("Not a SPI input!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native DigitalOut pointer");
    }

    // Cast the argument to C++
    SPI* spi = reinterpret_cast<SPI*>(spi_ptr);

    int cs_pin = jerry_get_number_value(args[1]);

    // Call the native function
    if(args_count == 2){
        native_ptr->init(*spi, (PinName)cs_pin);
    }
    else if(args_count == 5){
        int int1_pin = jerry_get_number_value(args[2]);
        int int2_pin = jerry_get_number_value(args[3]);
        int spi_type = jerry_get_number_value(args[4]);

        native_ptr->init(*spi, (PinName)cs_pin, (PinName)int1_pin, (PinName)int2_pin, spi_type);
    }
    
    return jerry_create_number(0);
}

/**
 * LSM6DSL_JS#init_i2c (native JavaScript method)
 * @brief   Initializes the sensor using I2C interface
 * @param   DevI2c object of helper class which handles the DevI2C peripheral
 * @param   INT1 pin
 * @param   INT2 pin
 * @param   Address
 */
DECLARE_CLASS_FUNCTION(LSM6DSL_JS, init_i2c) {
    CHECK_ARGUMENT_COUNT(LSM6DSL_JS, init_i2c, (args_count == 1 || args_count == 3 || args_count == 4));
    CHECK_ARGUMENT_TYPE_ALWAYS(LSM6DSL_JS, init_i2c, 0, object);
    CHECK_ARGUMENT_TYPE_ON_CONDITION(LSM6DSL_JS, init_i2c, 1, number, args_count == 3);
    CHECK_ARGUMENT_TYPE_ON_CONDITION(LSM6DSL_JS, init_i2c, 2, number, args_count == 3);
    CHECK_ARGUMENT_TYPE_ON_CONDITION(LSM6DSL_JS, init_i2c, 3, number, args_count == 4);
    
    // Unwrap native LSM6DSL_JS object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native LSM6DSL_JS pointer");
    }

    LSM6DSL_JS *native_ptr = static_cast<LSM6DSL_JS*>(void_ptr);
 
    // Unwrap arguments
    void *i2c_ptr;
    const jerry_object_native_info_t *i2c_type_ptr;
    bool i2c_has_ptr = jerry_get_object_native_pointer(args[0], &i2c_ptr, &i2c_type_ptr);

    // Check if we have the i2c pointer
    if (!i2c_has_ptr) {
        printf("Not a I2C input!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native DigitalOut pointer");
    }

    // Cast the argument to C++
    DevI2C* i2c = reinterpret_cast<DevI2C*>(i2c_ptr);
    
    // Call the native function
    if(args_count == 1){
        native_ptr->init(*i2c);
    }
    else if(args_count == 3){
        int int1_pin = jerry_get_number_value(args[1]);
        int int2_pin = jerry_get_number_value(args[2]);
        native_ptr->init(*i2c, (PinName) int1_pin, (PinName) int2_pin);
    }
    else if(args_count == 4){
        int int1_pin = jerry_get_number_value(args[1]);
        int int2_pin = jerry_get_number_value(args[2]);
        int address = jerry_get_number_value(args[3]);
        native_ptr->init(*i2c, (PinName) int1_pin, (PinName) int2_pin, (uint8_t) address);
    }
    
    return jerry_create_number(0);
}

/**
 * LSM6DSL_JS#get_accelerometer_axes (native JavaScript method)
 * @brief   Gets the accelerometer axes information
 * @returns Accelerometer axes
 */
DECLARE_CLASS_FUNCTION(LSM6DSL_JS, get_accelerometer_axes) {
    CHECK_ARGUMENT_COUNT(LSM6DSL_JS, get_accelerometer_axes, (args_count == 0));
 
    
    // Unwrap native LSM6DSL_JS object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native LSM6DSL_JS pointer");
    }

    LSM6DSL_JS *native_ptr = static_cast<LSM6DSL_JS*>(void_ptr);
 
    // Get the result from the C++ API
    char *result = new char[128];
    native_ptr->get_accelerometer_axes_json(result);
    
    // Cast it back to JavaScript
    jerry_value_t out = jerry_create_string((unsigned char *)result);
    
    //mbed::Serial pc((PinName)0x2C, (PinName)0x32);
    //printf("accele: %s\n", result);
   
    // Recycle the result from function
    delete result;

    // Return the output
    return out;
}


/**
 * LSM6DSL_JS#get_gyroscope_axes (native JavaScript method)
 * @brief   Gets the gyroscope axes information
 * @returns Gyroscope axes
 */
DECLARE_CLASS_FUNCTION(LSM6DSL_JS, get_gyroscope_axes) {
    CHECK_ARGUMENT_COUNT(LSM6DSL_JS, get_gyroscope_axes, (args_count == 0));
 
    // Unwrap native LSM6DSL_JS object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native LSM6DSL_JS pointer");
    }

    LSM6DSL_JS *native_ptr = static_cast<LSM6DSL_JS*>(void_ptr);
 
    // Get the result from the C++ API
    char *result = new char[128];
    native_ptr->get_gyroscope_axes_json(result);
    
    // Cast it back to JavaScript
    jerry_value_t out = jerry_create_string((unsigned char *)result);
    
    // Recycle the result from function
    delete result;

    // Return the output
    return out;
}


/**
 * LSM6DSL_JS (native JavaScript constructor)
 * @brief   Constructor for Javascript wrapper
 * @returns A JavaScript object representing LSM6DSL_JS.
 */
DECLARE_CLASS_CONSTRUCTOR(LSM6DSL_JS) {
    CHECK_ARGUMENT_COUNT(LSM6DSL_JS, __constructor, args_count == 0);
    
    // Extract native LSM6DSL_JS pointer (from this object) 
    LSM6DSL_JS *native_ptr = new LSM6DSL_JS();

    jerry_value_t js_object = jerry_create_object();
    jerry_set_object_native_pointer(js_object, native_ptr, &native_obj_type_info);

    // attach methods
    ATTACH_CLASS_FUNCTION(js_object, LSM6DSL_JS, init_spi);
    ATTACH_CLASS_FUNCTION(js_object, LSM6DSL_JS, init_i2c);
    ATTACH_CLASS_FUNCTION(js_object, LSM6DSL_JS, get_accelerometer_axes);
    ATTACH_CLASS_FUNCTION(js_object, LSM6DSL_JS, get_gyroscope_axes);
    
    return js_object;
}
