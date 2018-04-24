/**
 ******************************************************************************
 * @file    NetworkInterface_JS-js.cpp
 * @author  ST
 * @version V1.0.0
 * @date    25 October 2017
 * @brief   Implementation of NetworkInterface for Javascript.
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

#include "jerryscript-mbed-library-registry/wrap_tools.h"
#include "jerryscript-mbed-event-loop/EventLoop.h"

#include "NetworkInterface_JS.h"

/* Class Implementation ------------------------------------------------------*/

/**
 * NetworkInterface_JS#destructor
 *
 * Called if/when the NetworkInterface_JS object is GC'ed.
 */
void NAME_FOR_CLASS_NATIVE_DESTRUCTOR(NetworkInterface_JS) (void *void_ptr) {
    delete static_cast<NetworkInterface_JS*>(void_ptr);
}

/**
 * Type infomation of the native NetworkInterface_JS pointer
 *
 * Set NetworkInterface_JS#destructor as the free callback.
 */
static const jerry_object_native_info_t native_obj_type_info = {
    .free_cb = NAME_FOR_CLASS_NATIVE_DESTRUCTOR(NetworkInterface_JS)
};

/**
 * NetworkInterface_JS#connect (native JavaScript method)
 *
 * Connects to the MQTT Broker.
 */

DECLARE_CLASS_FUNCTION(NetworkInterface_JS, connect) {
    CHECK_ARGUMENT_COUNT(NetworkInterface_JS, connect, (args_count == 0));
    
    // Unwrap native NetworkInterface_JS object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native NetworkInterface_JS pointer");
    }

    NetworkInterface_JS *native_ptr = static_cast<NetworkInterface_JS*>(void_ptr);

    //int ret = 0; //native_ptr->connect();
    //NetworkInterface_JS::getInstance()->connect();
  
    native_ptr->connect();

    return jerry_create_number(0);
}

/**
 * NetworkInterface_JS (native JavaScript constructor)
 *
 * @returns a JavaScript object representing the NetworkInterface_JS.
 */
DECLARE_CLASS_CONSTRUCTOR(NetworkInterface_JS) {
    CHECK_ARGUMENT_COUNT(NetworkInterface_JS, __constructor, (args_count == 0));
    
    NetworkInterface_JS *native_ptr = NetworkInterface_JS::getInstance(); //->getNetworkInterface_JS();

    jerry_value_t js_object = jerry_create_object();
    jerry_set_object_native_pointer(js_object, native_ptr, &native_obj_type_info);
    
    ATTACH_CLASS_FUNCTION(js_object, NetworkInterface_JS, connect);
    
    return js_object;
}
