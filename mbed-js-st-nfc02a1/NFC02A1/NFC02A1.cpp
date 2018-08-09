/**
 ******************************************************************************
 * @file    NFC02A1.cpp
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


/* Includes ------------------------------------------------------------------*/

#include "NFC02A1.h"
#include "mbed.h"

/** init
 * @brief	Initiale NFC Tag using DevI2C.
 * @param	DevI2c object of an helper class which handles the DevI2C peripheral
 */
void NFC02A1::init(DevI2C &devI2c){
	/* Using default board pinout. */
  nfcNucleo = XNucleoNFC02A1::instance(devI2c,
										XNucleoNFC02A1::DEFAULT_GPO_PIN,XNucleoNFC02A1::DEFAULT_RF_DISABLE_PIN,
										XNucleoNFC02A1::DEFAULT_LED1_PIN,XNucleoNFC02A1::DEFAULT_LED2_PIN,
										XNucleoNFC02A1::DEFAULT_LED3_PIN);
  
  tag = &nfcNucleo->get_M24LR().get_NDef_tag();
  mM24LRp = &nfcNucleo->get_M24LR();
  
  /* Enabling Energy Harvesting. */
  mM24LRp->enable_energy_harvesting();

}

/**
 * Read NFC tag
 */
int NFC02A1::read_tag(char* output) {
  
  if (tag->open_session() == true) {
    //printf("Open Session\r\n");
    NDefLib::Message readMsg;

    tag->read(&readMsg);
    //printf("Message Read\r\n");

    if (readMsg.get_N_records()==0) {
      //printf("Error Read\r\n");
      return 1;
    } else {
      for (uint32_t i=0;i<readMsg.get_N_records();i++) {
        Record *r = readMsg[i];
        //printRecord(r);
        RecordURI *const temp = (RecordURI*)r;
        
        /* Display Info
        printf("Read uriId: %d\r\n",temp->get_uri_id());
        printf("Read uriType: %s\r\n",temp->get_uri_type().c_str());
        printf("Read uriContent: %s\r\n",temp->get_content().c_str());
        */
        
        //output = (char *)malloc(sizeof(char) * (strlen(temp->get_content().c_str()) + 1));
        strcpy(output, temp->get_content().c_str());
        
        delete r;
      } //for
    } //if-else

    tag->close_session();
    //printf("Close session\r\n");
    return 0;
  } else {
    //printf("Error open read Session\n\r");
    return 1;
  }
}


/**
 * Write NFC tag
 */
int NFC02A1::write_tag(char* input) {
  
  /* Opening the i2c session with the nfc chip. */
  if (tag->open_session() == true) {
    //printf("Session opened\n\r");
    //nfcNucleo->get_led1() = 1;
    
    /* Creating the NDef message and record. */
    NDefLib::Message msg;
    NDefLib::RecordURI rUri(NDefLib::RecordURI::HTTP_WWW, input);
    msg.add_record(&rUri);
    
    /* Writing the tag-> */
    if (tag->write(msg) == true) {
      //printf("Tag written\n\r");
      //nfcNucleo->get_led2() = 1;
    } else {
      //printf("Error writing \n\r");
      return 1;
      //nfcNucleo->get_led1() = 0;
    } //if-else
    
    /* Closing the i2c session. */
    if (tag->close_session() == true) {
      //printf("Session closed\n\r");
      //nfcNucleo->get_led3() = 1;
      return 0;
    } else {
      //printf("Error closing the session\n\r");
      return 1;
    } //if-else
  } else {
    //printf("Error opening the session\n\r");
    return 1;
  }
}





NFC02A1::~NFC02A1(){}