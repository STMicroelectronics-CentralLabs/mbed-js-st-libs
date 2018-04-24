#include "jerryscript-mbed-library-registry/wrap_tools.h"
#include "jerryscript-mbed-event-loop/EventLoop.h"

#include "JSManager.h"

/* Class Implementation ------------------------------------------------------*/

/**
 * JSManager#destructor
 *
 * Called if/when the JSManager object is GC'ed.
 */
void NAME_FOR_CLASS_NATIVE_DESTRUCTOR(JSManager) (void *void_ptr) {
    delete static_cast<JSManager*>(void_ptr);
}

/**
 * Type infomation of the native JSManager pointer
 *
 * Set JSManager#destructor as the free callback.
 */
static const jerry_object_native_info_t native_obj_type_info = {
    .free_cb = NAME_FOR_CLASS_NATIVE_DESTRUCTOR(JSManager)
};


/**
 * JSManager#connect_to_network (native JavaScript method)
 *
 * connects to the network using Easy connect.
 *
 */
DECLARE_CLASS_FUNCTION(JSManager, connect_to_network) {
    CHECK_ARGUMENT_COUNT(JSManager, connect_to_network, (args_count == 0));
    
    // Unwrap native JSManager object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native JSManager pointer");
    }

    JSManager *native_ptr = static_cast<JSManager*>(void_ptr);

    int result = native_ptr->connect_to_network();

    return jerry_create_number(result);
}

/**
 * JSManager#run_js_flash (native JavaScript method)
 *
 * Set the run_js_flash of the JSManager bus.
 *
 * @param run_js_flash New JSManager run_js_flash
 */
DECLARE_CLASS_FUNCTION(JSManager, run_js_flash) {
    CHECK_ARGUMENT_COUNT(JSManager, run_js_flash, (args_count == 0));
    
    // Unwrap native JSManager object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native JSManager pointer");
    }

    JSManager *native_ptr = static_cast<JSManager*>(void_ptr);

    int result = native_ptr->run_js_flash();

    return jerry_create_number(result);
}


/**
 * JSManager#erase_flash (native JavaScript method)
 *
 * Erases the flash.
 */
DECLARE_CLASS_FUNCTION(JSManager, erase_flash) {
    CHECK_ARGUMENT_COUNT(JSManager, erase_flash, (args_count == 0));
    
    // Unwrap native JSManager object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native JSManager pointer");
    }

    JSManager *native_ptr = static_cast<JSManager*>(void_ptr);

    int ret = native_ptr->erase_flash();

    return jerry_create_number(ret);
}


/**
 * JSManager#write_to_flash (native JavaScript method)
 *
 * Set the write_to_flash of the JSManager bus.
 *
 * @param write_to_flash New JSManager write_to_flash
 */
DECLARE_CLASS_FUNCTION(JSManager, write_to_flash) {
    CHECK_ARGUMENT_COUNT(JSManager, write_to_flash, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(JSManager, write_to_flash, 0, string);
    
    size_t code_length = jerry_get_string_length(args[0]);
    
    // add an extra character to ensure there's a null character after the device name
    char* code = (char*)calloc(code_length + 1, sizeof(char));
    jerry_string_to_char_buffer(args[0], (jerry_char_t*)code, code_length);


    // Unwrap native JSManager object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native JSManager pointer");
    }

    JSManager *native_ptr = static_cast<JSManager*>(void_ptr);

    native_ptr->write_to_flash(code);

    free(code);
    return jerry_create_undefined();
}

/**
 * JSManager#load_http_program (native JavaScript method)
 *
 * Loads the program from http server.
 *
 * @param load_http_program New JSManager load_http_program
 */
DECLARE_CLASS_FUNCTION(JSManager, load_http_program) {
    CHECK_ARGUMENT_COUNT(JSManager, load_http_program, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(JSManager, load_http_program, 0, string);
    
    size_t code_length = jerry_get_string_length(args[0]);
    
    // add an extra character to ensure there's a null character after the device name
    char* code = (char*)calloc(code_length + 1, sizeof(char));
    jerry_string_to_char_buffer(args[0], (jerry_char_t*)code, code_length);


    // Unwrap native JSManager object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native JSManager pointer");
    }

    JSManager *native_ptr = static_cast<JSManager*>(void_ptr);

    int ret =  native_ptr->load_http_program(code);

    free(code);
    return jerry_create_number(ret);
}

/**
 * JSManager#reboot (native JavaScript method)
 *
 * Set the reboot of the JSManager bus.
 *
 * @param reboot New JSManager reboot
 */
DECLARE_CLASS_FUNCTION(JSManager, reboot) {
    CHECK_ARGUMENT_COUNT(JSManager, reboot, (args_count == 0));
    
    // Unwrap native JSManager object
    void *void_ptr;
    const jerry_object_native_info_t *type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native JSManager pointer");
    }

    JSManager *native_ptr = static_cast<JSManager*>(void_ptr);

    native_ptr->reboot();

    return jerry_create_undefined();
}

/**
 * JSManager (native JavaScript constructor)
 *
 * @returns a JavaScript object representing the JSManager.
 */
DECLARE_CLASS_CONSTRUCTOR(JSManager) {
    CHECK_ARGUMENT_COUNT(JSManager, __constructor, (args_count == 0));
    
    JSManager *native_ptr = new JSManager();

    jerry_value_t js_object = jerry_create_object();
    jerry_set_object_native_pointer(js_object, native_ptr, &native_obj_type_info);

    
    ATTACH_CLASS_FUNCTION(js_object, JSManager, erase_flash);
    ATTACH_CLASS_FUNCTION(js_object, JSManager, run_js_flash);
    ATTACH_CLASS_FUNCTION(js_object, JSManager, write_to_flash);
    ATTACH_CLASS_FUNCTION(js_object, JSManager, reboot);
    ATTACH_CLASS_FUNCTION(js_object, JSManager, load_http_program);
    ATTACH_CLASS_FUNCTION(js_object, JSManager, connect_to_network);
    
    return js_object;
}
