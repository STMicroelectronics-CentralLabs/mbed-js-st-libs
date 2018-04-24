/**
 ******************************************************************************
 * @file    DevI2C-js.cpp
 * @author  ST
 * @version V1.0.0
 * @date    25 October 2017
 * @brief   Implementation of DevI2C for Javascript.
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
#include "DevI2C.h"

#include "mbed.h"

/* Class Implementation ------------------------------------------------------*/

/**
 * DevI2C#destructor
 * @brief	Called if/when the DevI2C object is GC'ed.
 */
void NAME_FOR_CLASS_NATIVE_DESTRUCTOR(DevI2C) (void *void_ptr) {
    delete static_cast<DevI2C*>(void_ptr);
}

/**
 * Type infomation of the native DevI2C pointer
 * @brief	Set DevI2C#destructor as the free callback.
 */
static const jerry_object_native_info_t native_obj_type_info = {
    .free_cb = NAME_FOR_CLASS_NATIVE_DESTRUCTOR(DevI2C)
};

/**
 * DevI2C#frequency (native JavaScript method)
 * @brief	Set the frequency of the DevI2C bus.
 *
 * @param frequency New DevI2C Frequency
 */
DECLARE_CLASS_FUNCTION(DevI2C, frequency) {
    CHECK_ARGUMENT_COUNT(DevI2C, frequency, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(DevI2C, frequency, 0, number);

    // Unwrap native DevI2C object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native DevI2C pointer");
    }

    I2C *native_ptr = static_cast<I2C*>(void_ptr);

    int hz = jerry_get_number_value(args[0]);
    native_ptr->frequency(hz);

    return jerry_create_undefined();
}

/**
 * DevI2C#read (native JavaScript method)
 * @brief	Read data from the DevI2C bus.
 *
 * @overload DevI2C#read(int)
 * Read a single byte from the DevI2C bus
 *
 * @param ack indicates if the byte is to be acknowledged (1 => acknowledge)
 *
 * @returns array: Data read from the DevI2C bus
 *
 * @overload DevI2C#read(int, array, int)
 * Read a series of bytes from the DevI2C bus
 *
 * @param address DevI2C address to read from
 * @param data Array to read into
 * @param length Length of data to read
 *
 * @returns array: Data read from the DevI2C bus
 */
DECLARE_CLASS_FUNCTION(DevI2C, read) {
    CHECK_ARGUMENT_COUNT(DevI2C, read, (args_count == 1 || args_count == 3 || args_count == 4));

    if (args_count == 1) {
        CHECK_ARGUMENT_TYPE_ALWAYS(DevI2C, read, 0, number);
        void *void_ptr;
        const jerry_object_native_info_t *type_ptr;
        bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

        if (!has_ptr || type_ptr != &native_obj_type_info) {
            return jerry_create_error(JERRY_ERROR_TYPE,
                                      (const jerry_char_t *) "Failed to get native DevI2C pointer");
        }

        I2C *native_ptr = static_cast<I2C*>(void_ptr);

        int data = jerry_get_number_value(args[0]);
        int result = native_ptr->read(data);

        return jerry_create_number(result);
    } else {
        CHECK_ARGUMENT_TYPE_ALWAYS(DevI2C, read, 0, number);
        CHECK_ARGUMENT_TYPE_ALWAYS(DevI2C, read, 1, array);
        CHECK_ARGUMENT_TYPE_ALWAYS(DevI2C, read, 2, number);

        CHECK_ARGUMENT_TYPE_ON_CONDITION(DevI2C, read, 3, boolean, (args_count == 4));

        void *void_ptr;
        const jerry_object_native_info_t *type_ptr;
        bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

        if (!has_ptr || type_ptr != &native_obj_type_info) {
            return jerry_create_error(JERRY_ERROR_TYPE,
                                      (const jerry_char_t *) "Failed to get native DevI2C pointer");
        }

        I2C *native_ptr = static_cast<I2C*>(void_ptr);

        const uint32_t data_len = jerry_get_array_length(args[1]);

        int address = jerry_get_number_value(args[0]);
        int length = jerry_get_number_value(args[2]);

        char *data = new char[data_len];

        bool repeated = false;
        if (args_count == 4) {
            repeated = jerry_get_boolean_value(args[3]);
        }

        int result = native_ptr->read(address, data, length, repeated);

        jerry_value_t out_array = jerry_create_array(data_len);

        for (uint32_t i = 0; i < data_len; i++) {
            jerry_value_t val = jerry_create_number(double(data[i]));
            jerry_set_property_by_index(out_array, i, val);
            jerry_release_value(val);
        }

        delete[] data;

        if (result == 0) {
            // ACK
            return out_array;
        } else {
            // NACK
            const char *error_msg = "NACK received from DevI2C bus";

            jerry_release_value(out_array);
            return jerry_create_error(JERRY_ERROR_COMMON, reinterpret_cast<const jerry_char_t *>(error_msg));
        }
    }
}

/**
 * DevI2C#write (native JavaScript method)
 * @brief	Writes to DevI2C bus
 * 
 * @overload DevI2C#write(int)
 * Write a single byte to the DevI2C bus
 *
 * @param data Data byte to write to the DevI2C bus
 *
 * @returns 1 on success, 0 on failure
 *
 * @overload DevI2C#write(int, array, int, bool)
 * Write an array of data to a certain address on the DevI2C bus
 *
 * @param address 8-bit DevI2C slave address
 * @param data Array of bytes to send
 * @param length Length of data to write
 * @param repeated (optional) If true, do not send stop at end.
 *
 * @returns 0 on success, non-0 on failure
 */
DECLARE_CLASS_FUNCTION(DevI2C, write) {
    CHECK_ARGUMENT_COUNT(DevI2C, write, (args_count == 1 || args_count == 3 || args_count == 4));

    if (args_count == 1) {
        CHECK_ARGUMENT_TYPE_ALWAYS(DevI2C, write, 0, number);

        // Extract native DevI2C object
        void *void_ptr;
        const jerry_object_native_info_t *type_ptr;
        bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

        if (!has_ptr || type_ptr != &native_obj_type_info) {
            return jerry_create_error(JERRY_ERROR_TYPE,
                                      (const jerry_char_t *) "Failed to get native DevI2C pointer");
        }

        I2C *native_ptr = static_cast<I2C*>(void_ptr);

        // Unwrap arguments
        int data = jerry_get_number_value(args[0]);

        int result = native_ptr->write(data);
        return jerry_create_number(result);
    } else {
        // 3 or 4
        CHECK_ARGUMENT_TYPE_ALWAYS(DevI2C, write, 0, number);
        CHECK_ARGUMENT_TYPE_ALWAYS(DevI2C, write, 1, array);
        CHECK_ARGUMENT_TYPE_ALWAYS(DevI2C, write, 2, number);
        CHECK_ARGUMENT_TYPE_ON_CONDITION(DevI2C, write, 3, boolean, (args_count == 4));

        // Extract native DevI2C object
        void *void_ptr;
        const jerry_object_native_info_t *type_ptr;
        bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

        if (!has_ptr || type_ptr != &native_obj_type_info) {
            return jerry_create_error(JERRY_ERROR_TYPE,
                                      (const jerry_char_t *) "Failed to get native DevI2C pointer");
        }

        I2C *native_ptr = static_cast<I2C*>(void_ptr);

        // Unwrap arguments
        int address = jerry_get_number_value(args[0]);
        const uint32_t data_len = jerry_get_array_length(args[1]);
        int length = jerry_get_number_value(args[2]);
        bool repeated = args_count == 4 && jerry_get_boolean_value(args[3]);

        // Construct data byte array
        char *data = new char[data_len];
        for (uint32_t i = 0; i < data_len; i++) {
            data[i] = jerry_get_number_value(jerry_get_property_by_index(args[1], i));
        }

        int result = native_ptr->write(address, data, length, repeated);

        // free dynamically allocated resources
        delete[] data;

        return jerry_create_number(result);
    }
}

/**
 * DevI2C#start (native JavaScript method)
 * @brief	Creates a start condition on the DevI2C bus.
 */
DECLARE_CLASS_FUNCTION(DevI2C, start) {
    CHECK_ARGUMENT_COUNT(DevI2C, start, (args_count == 0));

    // Extract native DevI2C object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native DevI2C pointer");
    }

    I2C *native_ptr = static_cast<I2C*>(void_ptr);

    native_ptr->start();
    return jerry_create_undefined();
}

/**
 * DevI2C#stop (native JavaScript method)
 * @brief	Creates a stop condition on the DevI2C bus.
 */
DECLARE_CLASS_FUNCTION(DevI2C, stop) {
    CHECK_ARGUMENT_COUNT(DevI2C, stop, (args_count == 0));

    // Extract native DevI2C object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native DevI2C pointer");
    }

    I2C *native_ptr = static_cast<I2C*>(void_ptr);

    native_ptr->stop();
    return jerry_create_undefined();
}

/**
 * DevI2C (native JavaScript constructor)
 * @brief	Constructor
 * @param sda mbed pin for DevI2C data
 * @param scl mbed pin for DevI2C clock
 * @returns a JavaScript object representing the DevI2C bus.
 */
DECLARE_CLASS_CONSTRUCTOR(DevI2C) {
    CHECK_ARGUMENT_COUNT(DevI2C, __constructor, (args_count == 2));
    CHECK_ARGUMENT_TYPE_ALWAYS(DevI2C, __constructor, 0, number);
    CHECK_ARGUMENT_TYPE_ALWAYS(DevI2C, __constructor, 1, number);

    int sda = jerry_get_number_value(args[0]);
    int scl = jerry_get_number_value(args[1]);

    DevI2C *native_ptr = new DevI2C((PinName)sda, (PinName)scl);

    jerry_value_t js_object = jerry_create_object();
    jerry_set_object_native_pointer(js_object, native_ptr, &native_obj_type_info);

    ATTACH_CLASS_FUNCTION(js_object, DevI2C, frequency);
    ATTACH_CLASS_FUNCTION(js_object, DevI2C, read);
    ATTACH_CLASS_FUNCTION(js_object, DevI2C, write);
    ATTACH_CLASS_FUNCTION(js_object, DevI2C, start);
    ATTACH_CLASS_FUNCTION(js_object, DevI2C, stop);

    return js_object;
}
