/**
 ******************************************************************************
 * @file    NFC02A1.h
 * @author  ST
 * @version V1.0.0
 * @date    9 October 2017
 * @brief   Implementation of an NFC02A1 Dynamic NFC Tag for
 *          use with Javascript.
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

#ifndef __NFC02A1_H__
#define __NFC02A1_H__

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include "mbed.h"

#include "XNucleoNFC02A1.h"
#include "DevI2C.h"
#include "NDefLib/NDefNfcTag.h"
#include "NDefLib/RecordType/RecordURI.h"

using namespace NDefLib;


/* Class Declaration ---------------------------------------------------------*/

/**
 * Abstract class of an NFC02A1 Dynamic NFC Tag for Javascript.
 */
class NFC02A1 {
private:
    /* Helper classes. */
    XNucleoNFC02A1 *nfcNucleo;
  
    NDefLib::NDefNfcTag *tag;
    M24LR *mM24LRp;
  
public:
    /* Constructors */
    NFC02A1(){}
    
    void init(DevI2C &devI2c);
    
    /* Destructor */
    ~NFC02A1();
    
    /* Declarations */
    int read_tag(char* output);
    int write_tag(char* input);
};

#endif