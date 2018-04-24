/*
 * @file    MQTT_JS-js.cpp
 * @author  ST
 * @version V1.0.0
 * @date    9 October 2017
 * @brief   Implementation of MQTT for Javascript.
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

#include "jerryscript-mbed-library-registry/wrap_tools.h"
#include "jerryscript-mbed-event-loop/EventLoop.h"

#include "MQTT_JS.h"

/* Class Implementation ------------------------------------------------------*/

/**
 * MQTT_JS#destructor
 *
 * Called if/when the MQTT_JS object is GC'ed.
 */
void NAME_FOR_CLASS_NATIVE_DESTRUCTOR(MQTT_JS) (void *void_ptr) {
    delete static_cast<MQTT_JS*>(void_ptr);
}

/**
 * Type infomation of the native MQTT_JS pointer
 *
 * Set MQTT_JS#destructor as the free callback.
 */
static const jerry_object_native_info_t native_obj_type_info = {
    .free_cb = NAME_FOR_CLASS_NATIVE_DESTRUCTOR(MQTT_JS)
};


/**
 * MQTT_JS#init (native JavaScript method)
 *
 * Initializes the MQTT service.
 */
DECLARE_CLASS_FUNCTION(MQTT_JS, init) {
    CHECK_ARGUMENT_COUNT(MQTT_JS, init, (args_count == 4));
    CHECK_ARGUMENT_TYPE_ALWAYS(MQTT_JS, init, 0, string);
    CHECK_ARGUMENT_TYPE_ALWAYS(MQTT_JS, init, 1, string);
    CHECK_ARGUMENT_TYPE_ALWAYS(MQTT_JS, init, 2, string);
    CHECK_ARGUMENT_TYPE_ALWAYS(MQTT_JS, init, 3, string);
    
    size_t id_length = jerry_get_string_length(args[0]);
    size_t token_length = jerry_get_string_length(args[1]);
    size_t url_length = jerry_get_string_length(args[2]);
    size_t port_length = jerry_get_string_length(args[3]);
    
    if(id_length > 32){
        return jerry_create_number(1);
    }
    if(token_length > 32){
        return jerry_create_number(2);
    }
    if(url_length > 128){
        return jerry_create_number(3);
    }
    if(port_length > 16){
        return jerry_create_number(4);
    }
    
    // add an extra character to ensure there's a null character after the device name
    char* id = (char*)calloc(id_length + 1, sizeof(char));
    jerry_string_to_char_buffer(args[0], (jerry_char_t*)id, id_length);
    char* token = (char*)calloc(token_length + 1, sizeof(char));
    jerry_string_to_char_buffer(args[1], (jerry_char_t*)token, token_length);
    char* url = (char*)calloc(url_length + 1, sizeof(char));
    jerry_string_to_char_buffer(args[2], (jerry_char_t*)url, url_length);
    char* port = (char*)calloc(port_length + 1, sizeof(char));
    jerry_string_to_char_buffer(args[3], (jerry_char_t*)port, port_length);

    // Unwrap native MQTT_JS object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native MQTT_JS pointer");
    }

    MQTT_JS *native_ptr = static_cast<MQTT_JS*>(void_ptr);

    //int ret = 0; //native_ptr->init();
    NetworkInterface_JS::getInstance()->connect();
  
    int res = native_ptr->init(NetworkInterface_JS::getInstance()->getNetworkInterface(),
    id, token, url, port);

    free(id);
    free(token);
    free(url);
    free(port);
    
    return jerry_create_number(res);
}


/**
 * MQTT_JS#yield (native JavaScript method)
 *
 * Waits to receive from the MQTT Broker.
 */
DECLARE_CLASS_FUNCTION(MQTT_JS, yield) {
    CHECK_ARGUMENT_COUNT(MQTT_JS, yield, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(MQTT_JS, init, 0, number);
    
    int time = jerry_get_number_value(args[0]);

    printf("Yielding for %d ms.\n", time);
    // Unwrap native MQTT_JS object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native MQTT_JS pointer");
    }

    MQTT_JS *native_ptr = static_cast<MQTT_JS*>(void_ptr);

    //int ret = 0; //native_ptr->yield();
    //NetworkInterface_JS::getInstance()->yield();
  
    int result = native_ptr->yield(time);

    return jerry_create_number(result);
}


/**
 * MQTT_JS#connect (native JavaScript method)
 *
 * Connects to the MQTT Broker.
 */
DECLARE_CLASS_FUNCTION(MQTT_JS, connect) {
    CHECK_ARGUMENT_COUNT(MQTT_JS, connect, (args_count == 0));
    
    // Unwrap native MQTT_JS object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native MQTT_JS pointer");
    }

    MQTT_JS *native_ptr = static_cast<MQTT_JS*>(void_ptr);

    //int ret = 0; //native_ptr->connect();
    //NetworkInterface_JS::getInstance()->connect();
  
    int result = native_ptr->connect(NetworkInterface_JS::getInstance()->getNetworkInterface());

    return jerry_create_number(result);
}


/**
 * MQTT_JS#publish (native JavaScript method)
 *
 * Publishes to the MQTT.
 */
DECLARE_CLASS_FUNCTION(MQTT_JS, publish) {
    CHECK_ARGUMENT_COUNT(MQTT_JS, subscribe, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(MQTT_JS, subscribe, 0, string);
    
    size_t buf_length = jerry_get_string_length(args[0]);
    
    // add an extra character to ensure there's a null character after the device name
    char* buf = (char*)calloc(buf_length + 1, sizeof(char));
    jerry_string_to_char_buffer(args[0], (jerry_char_t*)buf, buf_length);

    // Unwrap native MQTT_JS object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native MQTT_JS pointer");
    }

    MQTT_JS *native_ptr = static_cast<MQTT_JS*>(void_ptr);

    int result = native_ptr->publish(buf);

    free(buf);
    return jerry_create_number(result);

}

/**
 * MQTT_JS#run (native JavaScript method)
 *
 * Runs the MQTT demo.
 */
DECLARE_CLASS_FUNCTION(MQTT_JS, run) {
    CHECK_ARGUMENT_COUNT(MQTT_JS, run, (args_count == 0));
    
    // Unwrap native MQTT_JS object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native MQTT_JS pointer");
    }

    MQTT_JS *native_ptr = static_cast<MQTT_JS*>(void_ptr);

    //int ret = 0; //native_ptr->run();
    NetworkInterface_JS::getInstance()->connect();
  
    //MQTT_JS *mqtt = new MQTT_JS();
    native_ptr->start_mqtt(NetworkInterface_JS::getInstance()->getNetworkInterface());
  
    //native_ptr->run();

    return jerry_create_undefined();
}

DECLARE_CLASS_FUNCTION(MQTT_JS, onSubscribe) {
    CHECK_ARGUMENT_COUNT(MQTT_JS, onUpdate, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(MQTT_JS, onUpdate, 0, function);

    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native MQTT_JS pointer");
    }

    MQTT_JS *native_ptr = static_cast<MQTT_JS*>(void_ptr);

    jerry_value_t fn = args[0];
    jerry_acquire_value(fn);


    //BLEJS* this_ble = &BLEJS::Instance();
    //this_ble->setWriteCallback(native_ptr, f);
    int result = native_ptr->onSubscribe(fn);

    return jerry_create_number(result);
}

/**
 * MQTT_JS#subscribe (native JavaScript method)
 *
 * Subscribes to MQTT
 *
 * @param topic
 */
DECLARE_CLASS_FUNCTION(MQTT_JS, subscribe) {
    CHECK_ARGUMENT_COUNT(MQTT_JS, subscribe, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(MQTT_JS, subscribe, 0, string);
    
    size_t topic_length = jerry_get_string_length(args[0]);
    
    // add an extra character to ensure there's a null character after the device name
    char* topic = (char*)calloc(topic_length + 1, sizeof(char));
    jerry_string_to_char_buffer(args[0], (jerry_char_t*)topic, topic_length);

    // Unwrap native MQTT_JS object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native MQTT_JS pointer");
    }

    MQTT_JS *native_ptr = static_cast<MQTT_JS*>(void_ptr);

    int result = native_ptr->subscribe(topic);

    free(topic);
    return jerry_create_number(result);
}


/**
 * MQTT_JS (native JavaScript constructor)
 *
 * @returns a JavaScript object representing the MQTT_JS.
 */
DECLARE_CLASS_CONSTRUCTOR(MQTT_JS) {
    CHECK_ARGUMENT_COUNT(MQTT_JS, __constructor, (args_count == 0));
    
    MQTT_JS *native_ptr = new MQTT_JS();

    jerry_value_t js_object = jerry_create_object();
    jerry_set_object_native_pointer(js_object, native_ptr, &native_obj_type_info);

    
    ATTACH_CLASS_FUNCTION(js_object, MQTT_JS, run);
    ATTACH_CLASS_FUNCTION(js_object, MQTT_JS, onSubscribe);
    ATTACH_CLASS_FUNCTION(js_object, MQTT_JS, init);
    ATTACH_CLASS_FUNCTION(js_object, MQTT_JS, connect);
    ATTACH_CLASS_FUNCTION(js_object, MQTT_JS, subscribe);
    ATTACH_CLASS_FUNCTION(js_object, MQTT_JS, publish);
    ATTACH_CLASS_FUNCTION(js_object, MQTT_JS, yield);
    
    return js_object;
}
