#include "JSManager.h"

JSManager::JSManager(){
}

int JSManager::connect_to_network(){
    if (!NetworkInterface_JS::getInstance()->getNetworkInterface()) {
        // Connect to the network (see mbed_app.json for the connectivity method used)
        NetworkInterface_JS::getInstance()->connect();
        if (!NetworkInterface_JS::getInstance()->getNetworkInterface()) {
            printf("Cannot connect to the network, see serial output");
            return 1;
        }
    }
    return 0;    
}

NetworkInterface* JSManager::getNetworkInterface(){
    return NetworkInterface_JS::getInstance()->getNetworkInterface();
}

void JSManager::reboot(){
    // To soft reset device
    NVIC_SystemReset();
}

/**
 * run_js_flash
 *
 * Parse and run a dynamically loaded javascript file
 */
int JSManager::run_js_flash(){
    char *code = Flasher::read_from_flash();
    if(code == 0){
        return 1; //Flash is empty
    }
    else{
        const size_t length = strlen(code); //strlen(main_js::get_code()); //sizeof (code) / sizeof (code[0]); //24; //code.length;
        //printf("Length of code: %i\n", (int)length);
        jerry_value_t parsed_code = jerry_parse((const jerry_char_t *)code, length, false);

        if (jerry_value_has_error_flag(parsed_code)) {
            jerry_release_value(parsed_code);
            jsmbed_js_exit();
            return 2; //jerry_parse failed
        }

        jerry_value_t returned_value = jerry_run(parsed_code);
        jerry_release_value(parsed_code);

        if (jerry_value_has_error_flag(returned_value)) {
            jerry_release_value(returned_value);
            jsmbed_js_exit();
            return 3; //jerry_run failed
        }

        jerry_release_value(returned_value);
        return 0;

    }
}

int JSManager::write_to_flash(char *data){
    //int len = strlen(data);
    //data[len] = '\0';
    return Flasher::write_to_flash(data);
}

int JSManager::erase_flash(){
    return Flasher::erase_flash();
}

void JSManager::cleanup(){
    printf("JSManager: Cleaning up...\r\n");
    
    // To soft reset device
    //NVIC_SystemReset();

    // GC and cleaup
    //jerry_gc();
    //jerry_cleanup();

    // Run JS code
    //run_js();

    // Write to Flash
    //Flasher::write_to_flash("print('Hello World!');\0");
    
}


/**
 * load_http_program
 *
 * Prints the response of the HTTP request.
 */

void JSManager::print_response(HttpResponse* res) {
    
    // Print headers
    
    printf("\n----- HTTP GET response -----\n");
    printf("Status: %d - %s\n", res->get_status_code(), res->get_status_message().c_str());
    printf("Headers:\n");
    for (size_t ix = 0; ix < res->get_headers_length(); ix++) {
        printf("\t%s: %s\n", res->get_headers_fields()[ix]->c_str(), res->get_headers_values()[ix]->c_str());
    }
    // */
    
    // Print body
    printf("code (%d bytes):\n\n%s\n\n", res->get_body_length(), res->get_body_as_string().c_str());
}

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
int JSManager::load_http_program(char *url){
    // Connect to the network (see mbed_app.json for the connectivity method used)
    if (connect_to_network()) {
        //printf("Cannot connect to the network, see serial output");
        return 4; // Network could not be located
    }

    // Do a GET request to httpbin.org
    {
        // By default the body is automatically parsed and stored in a buffer, this is memory heavy.
        // To receive chunked response, pass in a callback as last parameter to the constructor.
        //HttpRequest* get_req = new HttpRequest(network, HTTP_GET, "http://httpbin.org/status/418");
        HttpRequest* get_req = new HttpRequest(getNetworkInterface(), HTTP_GET, url);
        //HttpRequest* get_req = new HttpRequest(network, HTTP_GET, "http://os.mbed.com/cookbook/HTTP-Client#hello-world");
        
        HttpResponse* get_res = get_req->send();
        if (!get_res) {
            //printf("HttpRequest failed (error code %d)\n", get_req->get_error());
            delete get_req;
            return 1; // Request failed.
        }

        
        if(get_res->get_status_code() == 200){
            print_response(get_res);
                
            string data = get_res->get_body_as_string();

            jerry_value_t parsed_code = jerry_parse((const jerry_char_t *)data.c_str(), data.length(), false);

            if (jerry_value_has_error_flag(parsed_code)) {
                //LOG_PRINT_ALWAYS("Error parsing program. Contains error(s)");
                jerry_release_value(parsed_code);
                delete get_req;
                return 3; // Error parsing program.
            }
            else{
                
                //printf("priting: %s", data.c_str());
                Flasher::write_to_flash((char *)data.c_str());

                jerry_release_value(parsed_code);
                reboot();
            }
            
        }
        else{
            //printf("Could not get program from server!\n");
            delete get_req;
            return 2; // File not found.
        }
        
        return 0;
    }

    /*
    // POST request to httpbin.org
    {
        HttpRequest* post_req = new HttpRequest(network, HTTP_POST, "http://httpbin.org/post");
        post_req->set_header("Content-Type", "application/json");

        const char body[] = "{\"hello\":\"world\"}";

        HttpResponse* post_res = post_req->send(body, strlen(body));
        if (!post_res) {
            printf("HttpRequest failed (error code %d)\n", post_req->get_error());
            return;
        }

        printf("\n----- HTTP POST response -----\n");
        dump_response(post_res);

        delete post_req;
    }
    */
    return 0;

}

void JSManager::jsmbed_js_exit() {
    // Cleaup
    //jerry_cleanup();
}