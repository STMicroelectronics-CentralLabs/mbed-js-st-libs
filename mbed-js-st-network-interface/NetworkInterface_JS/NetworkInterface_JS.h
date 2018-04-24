/**
 ******************************************************************************
 * @file    NetworkInterface_JS.h
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

/* Prevent recursive inclusion -----------------------------------------------*/

#ifndef _NetworkInterface_JS_H_
#define _NetworkInterface_JS_H_

/* Includes ------------------------------------------------------------------*/

#include "mbed.h"
#include "NetworkInterface.h"

#include <string>
using namespace std;

/* Class Declaration ---------------------------------------------------------*/

/**
 * class of NetworkInterface for Javascript.
 */
class NetworkInterface_JS{
private:

    /* Helper classes. */
    NetworkInterface* network;
    static NetworkInterface_JS* instance;

public:
    
    /* Constructors */
    NetworkInterface_JS();

    /* Destructors */
    ~NetworkInterface_JS();
    
    /* Functions */
    void connect();
    NetworkInterface* getNetworkInterface();
    static NetworkInterface_JS* getInstance();
    static void deleteInstance();
    
};

#endif  // _NetworkInterface_JS_H_