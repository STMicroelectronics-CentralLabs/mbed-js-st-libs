/**
 ******************************************************************************
 * @file    NFC02A1-js.cpp
 * @author  ST
 * @version V1.0.0
 * @date    9 October 2017
 * @brief   Implementation of an NFC02A1 Dynamic NFC Tag for
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
#include "NFC02A1.h"

#include "mbed.h"

#ifdef TARGET_SENSOR_TILE
mbed::Serial pc3((PinName)0x2C, (PinName)0x32);
#define printf(...) pc3.printf(__VA_ARGS__)
#endif


/* Class Implementation ------------------------------------------------------*/

/**
 * NFC02A1#destructor
 *
 * Called if/when the NFC02A1 is GC'ed.
 */
void NAME_FOR_CLASS_NATIVE_DESTRUCTOR(NFC02A1)(void *void_ptr) {
    delete static_cast<NFC02A1*>(void_ptr);
}


/**
 * Type infomation of the native NFC02A1 pointer
 *
 * Set NFC02A1#destructor as the free callback.
 */
static const jerry_object_native_info_t native_obj_type_info = {
    .free_cb = NAME_FOR_CLASS_NATIVE_DESTRUCTOR(NFC02A1)
};

/**
 * NFC02A1#init (native JavaScript method)
 * @brief   Initializes the component using I2C interface
 * @param   DevI2c object of helper class which handles the DevI2C peripheral
 */
DECLARE_CLASS_FUNCTION(NFC02A1, init) {
    CHECK_ARGUMENT_COUNT(NFC02A1, init, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(NFC02A1, init, 0, object);
    
    
    // Unwrap native NFC02A1 object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native NFC02A1 pointer");
    }

    NFC02A1 *native_ptr = static_cast<NFC02A1*>(void_ptr);
 
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
    native_ptr->init(*i2c);
    
    return jerry_create_number(0);
}


/**
 * NFC02A1#read_tag (native JavaScript method)
 * @brief   Read the tag
 */
DECLARE_CLASS_FUNCTION(NFC02A1, read_tag) {
    CHECK_ARGUMENT_COUNT(NFC02A1, read_tag, (args_count == 0));
    
    
    // Unwrap native NFC02A1 object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native NFC02A1 pointer");
    }

    NFC02A1 *native_ptr = static_cast<NFC02A1*>(void_ptr);
 
    // Call the native function
    char output[32] = {0};
    int result = native_ptr->read_tag(output);
    if(result == 0){
        return jerry_create_string((const jerry_char_t *) output);
    }
    else{
        return jerry_create_undefined();
    }
}

/**
 * NFC02A1#write_tag (native JavaScript method)
 * @brief   Write the tag
 * @param   tag string
 */
DECLARE_CLASS_FUNCTION(NFC02A1, write_tag) {
    CHECK_ARGUMENT_COUNT(NFC02A1, write_tag, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(BLEService, __constructor, 0, string);

    
    // Unwrap native NFC02A1 object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native NFC02A1 pointer");
    }

    NFC02A1 *native_ptr = static_cast<NFC02A1*>(void_ptr);
 
    // Unwrap input
    char input[32] = {0};
    jerry_string_to_char_buffer(args[0], (jerry_char_t*)input, 32);
    jerry_release_value(args[0]);

    // Call the native function
    int result = native_ptr->write_tag(input);

    return jerry_create_number(result);
}
    
/**
 * NFC02A1 (native JavaScript constructor)
 * @brief   Constructor for Javascript wrapper
 * @returns a JavaScript object representing NFC02A1.
 */
DECLARE_CLASS_CONSTRUCTOR(NFC02A1) {
    CHECK_ARGUMENT_COUNT(NFC02A1, __constructor, args_count == 0);
    
    // Extract native NFC02A1 pointer (from this object) 
    NFC02A1 *native_ptr = new NFC02A1();

    jerry_value_t js_object = jerry_create_object();
    jerry_set_object_native_pointer(js_object, native_ptr, &native_obj_type_info);

    // attach methods
    ATTACH_CLASS_FUNCTION(js_object, NFC02A1, init);
    ATTACH_CLASS_FUNCTION(js_object, NFC02A1, read_tag);
    ATTACH_CLASS_FUNCTION(js_object, NFC02A1, write_tag);
    
    
    return js_object;
}