/**
 ******************************************************************************
 * @file    LPS22HB_JS-js.cpp
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

#include "jerryscript-mbed-util/logging.h"
#include "jerryscript-mbed-library-registry/wrap_tools.h"

// Load the library that we'll wrap
#include "LPS22HB_JS.h"

#include "mbed.h"

#ifdef TARGET_SENSOR_TILE
mbed::Serial pc2((PinName)0x2C, (PinName)0x32);
#define printf(...) pc2.printf(__VA_ARGS__)
#endif

/* Class Implementation ------------------------------------------------------*/

/**
 * LPS22HB_JS#destructor
 * Called if/when the LPS22HB_JS is GC'ed.
 */
void NAME_FOR_CLASS_NATIVE_DESTRUCTOR(LPS22HB_JS)(void *void_ptr) {
    delete static_cast<LPS22HB_JS*>(void_ptr);
}

 
/**
 * Type infomation of the native LPS22HB_JS pointer
 * Sets LPS22HB_JS#destructor as the free callback.
 */
static const jerry_object_native_info_t native_obj_type_info = {
    .free_cb = NAME_FOR_CLASS_NATIVE_DESTRUCTOR(LPS22HB_JS)
};

/**
 * LPS22HB_JS#init_spi (native JavaScript method)
 * @brief Initializes the sensor using SPI interface
 * @param SPI object of helper class which handles the SPI peripheral
 * @param CS pin
 * @param INT pin
 * @param SPI type
 */
DECLARE_CLASS_FUNCTION(LPS22HB_JS, init_spi) {
    CHECK_ARGUMENT_COUNT(LPS22HB_JS, init_spi, (args_count == 2 || args_count == 4));
    CHECK_ARGUMENT_TYPE_ALWAYS(LPS22HB_JS, init_spi, 0, object);
    CHECK_ARGUMENT_TYPE_ALWAYS(LPS22HB_JS, init_spi, 1, number);
    CHECK_ARGUMENT_TYPE_ON_CONDITION(LPS22HB_JS, init_spi, 2, number, args_count == 4);
    CHECK_ARGUMENT_TYPE_ON_CONDITION(LPS22HB_JS, init_spi, 3, number, args_count == 4);

    // Unwrap native LPS22HB_JS object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native LPS22HB_JS pointer");
    }

    LPS22HB_JS *native_ptr = static_cast<LPS22HB_JS*>(void_ptr);
 
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
    else if(args_count == 4){
        int int_pin = jerry_get_number_value(args[2]);
        int spi_type = jerry_get_number_value(args[3]);
        
        /* To read string
        jerry_size_t req_sz = jerry_get_string_size(args[3]);
        jerry_char_t spi_type[req_sz];
        jerry_string_to_char_buffer(args[3], spi_type, req_sz);
        */
        native_ptr->init(*spi, (PinName)cs_pin, (PinName)int_pin, spi_type);
    }

    return jerry_create_number(0);
}


/**
 * LPS22HB_JS#init_i2c (native JavaScript method)
 * @brief   Initializes the sensor using I2C interface
 * @param   DevI2c object of helper class which handles the DevI2C peripheral
 * @param   Address
 * @param   INT pin
 */
DECLARE_CLASS_FUNCTION(LPS22HB_JS, init_i2c) {
    CHECK_ARGUMENT_COUNT(LPS22HB_JS, init_i2c, (args_count == 1 || args_count == 3));
    CHECK_ARGUMENT_TYPE_ALWAYS(LPS22HB_JS, init_i2c, 0, object);
    CHECK_ARGUMENT_TYPE_ON_CONDITION(LPS22HB_JS, init_i2c, 1, number, args_count == 3);
    CHECK_ARGUMENT_TYPE_ON_CONDITION(LPS22HB_JS, init_i2c, 2, number, args_count == 3);
    
    // Unwrap native LPS22HB_JS object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native LPS22HB_JS pointer");
    }

    LPS22HB_JS *native_ptr = static_cast<LPS22HB_JS*>(void_ptr);
 
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
        int address = jerry_get_number_value(args[1]);
        int int_pin = jerry_get_number_value(args[2]);
        native_ptr->init(*i2c, (uint8_t) address, (PinName) int_pin);
    }
    
    return jerry_create_number(0);
}

/**
 * LPS22HB_JS#get_temperature (native JavaScript method)
 * @brief   Gets the temperature reading
 * @returns Temperature
 */
DECLARE_CLASS_FUNCTION(LPS22HB_JS, get_temperature) {
    CHECK_ARGUMENT_COUNT(LPS22HB_JS, get_temperature, (args_count == 0));
 
    
    // Unwrap native LPS22HB_JS object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native LPS22HB_JS pointer");
    }

    LPS22HB_JS *native_ptr = static_cast<LPS22HB_JS*>(void_ptr);
 
    // Get the result from the C++ API
    //float result = native_ptr->get_temperature();
    
    char * result = new char[128];
    result = native_ptr->get_temperature_string(result);
    
    //pc.printf("Temperature: %s", result);

    // Cast it back to JavaScript
    jerry_value_t out = jerry_create_string((unsigned char *)result);
    
    //printf("temp: %s\n", result);
   
    // Recycle the result from function
    delete result;

    // Return the output
    return out;
}


/**
 * LPS22HB_JS#get_temperature_string (native JavaScript method)
 * @brief   Gets temperature reading in string form
 * @returns Temperature in string
 */
DECLARE_CLASS_FUNCTION(LPS22HB_JS, get_temperature_string) {
    CHECK_ARGUMENT_COUNT(LPS22HB_JS, get_temperature_string, (args_count == 0));
 
    
    // Unwrap native LPS22HB_JS object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native LPS22HB_JS pointer");
    }

    LPS22HB_JS *native_ptr = static_cast<LPS22HB_JS*>(void_ptr);
 
    // Get the result from the C++ API
    char * result = new char[128];
    result = native_ptr->get_temperature_string(result);
    
    //pc.printf("Temperature: %s", result);

    // Cast it back to JavaScript
    jerry_value_t out = jerry_create_string((unsigned char *)result);
    
    //printf("temp: %s\n", result);
   
    // Recycle the result from function
    delete result;

    // Return the output
    return out;
}

/**
 * LPS22HB_JS#get_pressure (native JavaScript method)
 * @brief   Gets the pressure reading
 * @returns Pressure
 */
DECLARE_CLASS_FUNCTION(LPS22HB_JS, get_pressure) {
    CHECK_ARGUMENT_COUNT(LPS22HB_JS, get_pressure, (args_count == 0));
 
    // Unwrap native LPS22HB_JS object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native LPS22HB_JS pointer");
    }

    LPS22HB_JS *native_ptr = static_cast<LPS22HB_JS*>(void_ptr);
 
    // Get the result from the C++ API
    float result = native_ptr->get_pressure();
    
    //printf("pressure: %f\n", result);
   
    // Cast it back to JavaScript and return
    return jerry_create_number(result);
}


/**
 * LPS22HB_JS#get_pressure_string (native JavaScript method)
 * @brief   Gets the pressure reading in string form
 * @returns Pressure
 */
DECLARE_CLASS_FUNCTION(LPS22HB_JS, get_pressure_string) {
    CHECK_ARGUMENT_COUNT(LPS22HB_JS, get_pressure_string, (args_count == 0));
 
    
    // Unwrap native LPS22HB_JS object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native LPS22HB_JS pointer");
    }

    LPS22HB_JS *native_ptr = static_cast<LPS22HB_JS*>(void_ptr);
 
    char * result = new char[128];
    result = native_ptr->get_pressure_string(result);
    
    // Cast it back to JavaScript
    jerry_value_t out = jerry_create_string((unsigned char *)result);
    
    //printf("pressure: %s\n", result);
   
    // Recycle the result from function
    delete result;

    // Return the output
    return out;
}

/**
 * LPS22HB_JS (native JavaScript constructor)
 * @brief   Constructor for Javascript wrapper
 * @returns a JavaScript object representing LPS22HB_JS.
 */
DECLARE_CLASS_CONSTRUCTOR(LPS22HB_JS) {
    CHECK_ARGUMENT_COUNT(LPS22HB_JS, __constructor, args_count == 0);
    //pc.printf("constructor called!\n");
    
    // Extract native LPS22HB_JS pointer (from this object) 
    LPS22HB_JS *native_ptr = new LPS22HB_JS();

    jerry_value_t js_object = jerry_create_object();
    jerry_set_object_native_pointer(js_object, native_ptr, &native_obj_type_info);

    // attach methods
    ATTACH_CLASS_FUNCTION(js_object, LPS22HB_JS, init_spi);
    ATTACH_CLASS_FUNCTION(js_object, LPS22HB_JS, init_i2c);
    ATTACH_CLASS_FUNCTION(js_object, LPS22HB_JS, get_temperature);
    ATTACH_CLASS_FUNCTION(js_object, LPS22HB_JS, get_temperature_string);
    ATTACH_CLASS_FUNCTION(js_object, LPS22HB_JS, get_pressure);
    ATTACH_CLASS_FUNCTION(js_object, LPS22HB_JS, get_pressure_string);
    
    return js_object;
}
