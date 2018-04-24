/**
 ******************************************************************************
 * @file    SerialBuffer.cpp
 * @author  ST
 * @version V1.0.0
 * @date    25 October 2017
 * @brief   Implementation of SerialBuffer for SerialInterface.
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

#include "SerialBuffer.h"


/** constructor
 * @brief	Constructor.
 */
SerialBuffer::SerialBuffer() {
    position = 0;
}

/** destructor
 * @brief	Destructor.
 */
SerialBuffer::~SerialBuffer() {
    position = 0;
}

/** clear
 * @brief	Clears the buffer.
 */
void SerialBuffer::clear() {
    buffer.clear();
    position = 0;
}

/** add
 * @brief	Adds string to buffer.
 * @param	string data
 */
void SerialBuffer::add(string s) {
    for(string::iterator it = s.begin(); it != s.end(); ++it) {
        buffer.insert(buffer.begin() + position, *it);
        position++;
    }
}

/** add
 * @brief	Adds character to buffer.
 * @param	Character
 */
void SerialBuffer::add(char c) {
    buffer.insert(buffer.begin() + position, c);
    position++;
}

/** begin
 * @brief	Returns the beginning of buffer.
 * @return  buffer begin iterator
 */
vector<char>::iterator SerialBuffer::begin() {
    return buffer.begin();
}

/** end
 * @brief	Returns the end of buffer.
 * @return  buffer end iterator
 */
vector<char>::iterator SerialBuffer::end() {
    return buffer.end();
}

/** getPosition
 * @brief	Returns the current position.
 * @return  Position
 */
size_t SerialBuffer::getPosition() {
    return position;
}

/** setPosition
 * @brief	Sets the position.
 * @param	Position
 */
void SerialBuffer::setPosition(size_t pos) {
    position = pos;
}

/** size
 * @brief	Returns the size of buffer.
 * @return  Buffer size
 */
size_t SerialBuffer::size() {
    return buffer.size();
}

/** get_string
 * @brief	Returns the buffer as string.
 * @return  Buffer string
 */
string SerialBuffer::get_string(){
    string s(buffer.begin(), buffer.end());
    return s;
}

/** get_char_array
 * @brief	Returns the buffer as char array.
 * @return  Buffer character array
 */
char *SerialBuffer::get_char_array(){
    string s(buffer.begin(), buffer.end());
    char *data = (char *)s.c_str();
    data[buffer.size()] = '\0';
    return data;
}
