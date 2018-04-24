#ifndef _JS_MANAGER_H
#define _JS_MANAGER_H

#include <string>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/time.h>

#include "mbed.h"
#include "jerry-core/include/jerryscript.h"

#include "jerryscript-mbed-event-loop/EventLoop.h"
#include "events/EventQueue.h"

#include "NetworkInterface_JS.h"
#include "http_request.h"

#include "string.h"
#include "Flasher.h"

using namespace std;

class JSManager {

public:
    JSManager();

    int connect_to_network();

    NetworkInterface* getNetworkInterface();

    void reboot();

    /**
     * run_js_flash
     *
     * Parse and run a dynamically loaded javascript file
     */
    int run_js_flash();

    int write_to_flash(char *data);

    int erase_flash();
    
    void cleanup();


    /**
     * load_http_program
     *
     * Prints the response of the HTTP request.
     */
    
    void print_response(HttpResponse* res);

    /**
     * load_http_program
     *
     * loads the program from http server.
     * returns code
     * 0 for success
     * 1 for no network available
     * 2 for request status not ok
     * 3 for error in parsin code 
     */
    int load_http_program(char *url);

    void jsmbed_js_exit();

};

#endif // _JS_MANAGER_H
