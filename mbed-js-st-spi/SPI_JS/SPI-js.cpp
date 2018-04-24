/**
 ******************************************************************************
 * @file    SPI-js.cpp
 * @author  ST
 * @version V1.0.0
 * @date    25 October 2017
 * @brief   Implementation of SPI for Javascript.
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
#include "SPI.h"
    
#include "mbed.h"

/* Class Implementation ------------------------------------------------------*/

/**
 * SPI#destructor
 *
 * Called if/when the SPI object is GC'ed.
 */
void NAME_FOR_CLASS_NATIVE_DESTRUCTOR(SPI) (void *void_ptr) {
    delete static_cast<SPI*>(void_ptr);
}

/**
 * Type infomation of the native SPI pointer
 *
 * Set SPI#destructor as the free callback.
 */
static const jerry_object_native_info_t native_obj_type_info = {
    .free_cb = NAME_FOR_CLASS_NATIVE_DESTRUCTOR(SPI)
};

/**
 * SPI (native JavaScript constructor)
 *
 * @param sda mbed pin for SPI data
 * @param scl mbed pin for SPI clock
 * @returns a JavaScript object representing the SPI bus.
 */
DECLARE_CLASS_CONSTRUCTOR(SPI) {
    CHECK_ARGUMENT_COUNT(SPI, __constructor, (args_count == 3));
    CHECK_ARGUMENT_TYPE_ALWAYS(SPI, __constructor, 0, number);
    CHECK_ARGUMENT_TYPE_ALWAYS(SPI, __constructor, 1, number);
    CHECK_ARGUMENT_TYPE_ALWAYS(SPI, __constructor, 2, number);

    int mosi = jerry_get_number_value(args[0]);
    int miso = jerry_get_number_value(args[1]);
    int sclk = jerry_get_number_value(args[2]);

    SPI *native_ptr = new SPI((PinName)mosi, (PinName)miso, (PinName)sclk);
    
    jerry_value_t js_object = jerry_create_object();
    jerry_set_object_native_pointer(js_object, native_ptr, &native_obj_type_info);
    
    /*
    //Future upgrades
    ATTACH_CLASS_FUNCTION(js_object, SPI, frequency);
    ATTACH_CLASS_FUNCTION(js_object, SPI, read);
    ATTACH_CLASS_FUNCTION(js_object, SPI, write);
    ATTACH_CLASS_FUNCTION(js_object, SPI, start);
    ATTACH_CLASS_FUNCTION(js_object, SPI, stop);
    */
    
    return js_object;

}
