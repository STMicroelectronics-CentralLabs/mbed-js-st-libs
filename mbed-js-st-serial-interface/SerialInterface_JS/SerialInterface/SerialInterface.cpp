
/**
 ******************************************************************************
 * @file    SerialInterface.cpp
 * @author  ST
 * @version V1.0.0
 * @date    25 October 2017
 * @brief   Implementation of SerialInterface.
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

#include "SerialInterface.h"

/* Class Implementation ------------------------------------------------------*/

ISerialInterface* SerialInterface::serialInterface = NULL;

/** Constructor
 * @brief	constructor.
 */
SerialInterface::SerialInterface() : historyPosition(0) {
    
    //pc.printf("\r\nJavaScript REPL running...\r\n> ");
    
    serialInterface = this;

    pc.attach(Callback<void()>(this, &SerialInterface::callback));

    jerry_port_console_printing = false;
}

/** printJustHappened
 * @brief	Prints the character entered.
 */
void SerialInterface::printJustHappened() {
    string s(buffer.begin(), buffer.end());
    pc.printf("> %s", s.c_str());
}

/** callback
 * @brief	Callback when a key is entered in terminal.
 */
void SerialInterface::callback() {
    while (pc.readable()) {
        char c = pc.getc();

        // control characters start with 0x1b and end with a-zA-Z
        if (inControlChar) {

            controlSequence.push_back(c);

            // if a-zA-Z then it's the last one in the control char...
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                inControlChar = false;

                // up
                if (controlSequence.size() == 2 && controlSequence.at(0) == 0x5b && controlSequence.at(1) == 0x41) {
                    pc.printf("\033[u"); // restore current position

                    if (historyPosition == 0) {
                        // cannot do...
                    }
                    else {
                        historyPosition--;
                        // reset cursor to 0, do \r, then write the new command...
                        pc.printf("\33[2K\r> %s", history[historyPosition].c_str());

                        buffer.clear();
                        buffer.add(history[historyPosition]);
                    }
                }
                // down
                else if (controlSequence.size() == 2 && controlSequence.at(0) == 0x5b && controlSequence.at(1) == 0x42) {
                    pc.printf("\033[u"); // restore current position

                    if (historyPosition == history.size()) {
                        // no-op
                    }
                    else if (historyPosition == history.size() - 1) {
                        historyPosition++;

                        // put empty
                        // reset cursor to 0, do \r, then write the new command...
                        pc.printf("\33[2K\r> ");

                        buffer.clear();
                    }
                    else {
                        historyPosition++;
                        // reset cursor to 0, do \r, then write the new command...
                        pc.printf("\33[2K\r> %s", history[historyPosition].c_str());

                        buffer.clear();
                        buffer.add(history[historyPosition]);
                    }
                }
                // left
                else if (controlSequence.size() == 2 && controlSequence.at(0) == 0x5b && controlSequence.at(1) == 0x44) {
                    size_t curr = buffer.getPosition();

                    // at pos0? prevent moving to the left
                    if (curr == 0) {
                        pc.printf("\033[u"); // restore current position
                    }
                    // otherwise it's OK, move the cursor back
                    else {
                        buffer.setPosition(curr - 1);

                        pc.putc('\033');
                        for (size_t ix = 0; ix < controlSequence.size(); ix++) {
                            pc.putc(controlSequence[ix]);
                        }
                    }
                }
                // right
                else if (controlSequence.size() == 2 && controlSequence.at(0) == 0x5b && controlSequence.at(1) == 0x43) {
                    size_t curr = buffer.getPosition();
                    size_t size = buffer.size();

                    // already at the end?
                    if (curr == size) {
                        pc.printf("\033[u"); // restore current position
                    }
                    else {
                        buffer.setPosition(curr + 1);

                        pc.putc('\033');
                        for (size_t ix = 0; ix < controlSequence.size(); ix++) {
                            pc.putc(controlSequence[ix]);
                        }
                    }
                }
                else {
                    // not up/down? Execute original control sequence
                    pc.putc('\033');
                    for (size_t ix = 0; ix < controlSequence.size(); ix++) {
                        pc.putc(controlSequence[ix]);
                    }
                }

                controlSequence.clear();
            }

            continue;
        }

        switch (c) {
            case 0x06: // '^F': /* Flash the program */
                pc.printf("\r\n");
                addCharacter('\0');
                js::EventLoop::getInstance().nativeCallback(Callback<void()>(this, &SerialInterface::flashBuffer));
                break;
            
            case 0x12: // '\r': /* want to run the buffer */
                pc.printf("\r\n");
                js::EventLoop::getInstance().nativeCallback(Callback<void()>(this, &SerialInterface::runBuffer));
                break;
            case '\r': /* want to run the buffer */
                addSpecialCharacter('\n');
                pc.printf("\r\n");
                break;
            case 0x09: /* Horizontal Tab */
                //pc.printf("\t");
                addCharacter('\t');
                break;
            case 0x08: /* backspace */
            case 0x7f: /* also backspace on some terminals */
                js::EventLoop::getInstance().nativeCallback(Callback<void()>(this, &SerialInterface::handleBackspace));
                break;
            // Not using ESC key at the moment
            case 0x1b: // control character 
                // wait until next a-zA-Z
                inControlChar = true;

                pc.printf("\033[s"); // save current position

                break; // break out of the callback (ignore all other characters)
            
            default:
                if( c < 0x20){
                    //pc.printf("Skipping character: %c ASCII: ", c, (int)c);
                    break;
                }
                addCharacter(c);
                break;
        }
    }
}

/** addToBuffer
 * @brief	Add character to Buffer.
 * @param	Character
 */
void SerialInterface::addToBuffer(char c){
    size_t curr_pos = buffer.getPosition();
    size_t buffer_size = buffer.size();

    if (curr_pos == buffer_size) {
        buffer.add(c);
    }
    else {
        // super inefficient...
        string v(buffer.begin(), buffer.end());
        v.insert(curr_pos, 1, c);

        buffer.clear();
        buffer.add(v);

        buffer.setPosition(curr_pos + 1);

        pc.printf("\r> %s\033[%dG", v.c_str(), int(curr_pos) + 4);
    }           
}

/** addCharacter
 * @brief	Add Character to buffer.
 * @param	Character
 */
void SerialInterface::addCharacter(char c){
    addToBuffer(c);
    pc.putc(c);          
}

/** addSpecialCharacter
 * @brief	Adds special character to buffer.
 * @param	Character
 */
void SerialInterface::addSpecialCharacter(char c){
    addToBuffer(c);
}

/** handleBackspace
 * @brief	Handle the Backspace key.
 */
void SerialInterface::handleBackspace() {
    size_t curr_pos = buffer.getPosition();

    string v(buffer.begin(), buffer.end());

    if (v.size() == 0 || curr_pos == 0) return;

    bool endOfLine = curr_pos == v.size();

    v.erase(curr_pos - 1, 1);

    buffer.clear();
    buffer.add(v);

    buffer.setPosition(curr_pos - 1);

    if (endOfLine) {
        pc.printf("\b \b");
    }
    else {
        // carriage return, new text, set cursor, empty until end of line
        pc.printf("\r\033[K> %s\033[%dG", v.c_str(), curr_pos + 2);
    }
}

/** runBuffer
 * @brief	Runs the JS code from buffer.
 */
void SerialInterface::runBuffer() {
    string rawCode(buffer.begin(), buffer.end());

    // pc.printf("Running: %s\r\n", rawCode.c_str());

    history.push_back(rawCode);
    historyPosition = history.size();

    // pc.printf("Executing (%s): ", rawCode.c_str());
    // for (size_t ix = 0; ix < rawCode.size(); ix++) {
    //     pc.printf(" %02x ", rawCode.at(ix));
    // }
    // pc.printf("\r\n");

    const jerry_char_t* code = reinterpret_cast<const jerry_char_t*>(rawCode.c_str());
    const size_t length = rawCode.length();

    jerry_value_t parsed_code = jerry_parse(code, length, false);

    // @todo, how do we get the error message? :-o

    if (jerry_value_has_error_flag(parsed_code)) {
        LOG_PRINT_ALWAYS("Syntax error while parsing code... (%s)\r\n", rawCode.c_str());
    }
    else {
        jerry_value_t returned_value = jerry_run(parsed_code);

        if (jerry_value_has_error_flag(returned_value)) {
            LOG_PRINT_ALWAYS("Running failed...\r\n");
        }
        else {
            jerry_value_t str_value = jerry_value_to_string(returned_value);

            jerry_size_t size = jerry_get_string_size(str_value);
            jerry_char_t ret_buffer[size + 1] = { 0 };

            jerry_string_to_char_buffer(str_value, ret_buffer, size);

            // jerry_string_to_char_buffer is not guaranteed to end with \0
            ret_buffer[size] = '\0';

            // reset terminal position to column 0...
            pc.printf("\33[2K\r");
            pc.printf("\33[36m"); // color to cyan

            if (jerry_value_is_string(returned_value)) {
                pc.printf("\"%s\"", ret_buffer);
            }
            else if (jerry_value_is_array(returned_value)) {
                pc.printf("[%s]", ret_buffer);
            }
            else {
                pc.printf("%s", ret_buffer);
            }

            // pc.printf("\r\n");
            pc.printf("\33[0m"); // color back to normal
            pc.printf("\r\n");

            jerry_release_value(str_value);
        }

        jerry_release_value(returned_value);
    }

    jerry_release_value(parsed_code);

    buffer.clear();

    pc.printf(">\r\n");
}

/** flashBuffer
 * @brief	Write the data in buffer to flash.
 */
void SerialInterface::flashBuffer() {
    addCharacter('\0');
    string rawCode(buffer.begin(), buffer.end());

    char *data = (char *)rawCode.c_str();
    //data[buffer.size()] = '\0';
    
    pc.printf("Requesting to flash: %s\r\nwith length: %i\r\n", data, strlen(data));
    Flasher::write_to_flash(data);
    
    //buffer.clear();

    pc.printf("Rebooting...\r\n");

    // To soft reset device
    NVIC_SystemReset();  
        
}

/** jerry_port_console
 * @brief	Prints to the console.
 * @param	Format
 * @param	Parameters
 */
void SerialInterface::jerry_port_console (const char *format, /**< format string */
                            ...) /**< parameters */
    {
        if (strlen(format) == 1 && format[0] == 0x0a) { // line feed (\n)
            printf("\r"); // add CR for proper display in serial monitors

            //jerry_port_console_printing = false; // not printing anymore...
        }

        if (!jerry_port_console_printing) {
            pc.printf("\33[100D\33[2K");
            //jerry_port_console_printing = true;
        }

        va_list args;
        va_start(args, format);
        vfprintf(stdout, format, args);
        va_end(args);

        if (strlen(format) == 1 && format[0] == 0x0a && serialInterface) {
            serialInterface->printJustHappened();
        }
    } /* jerry_port_console */
