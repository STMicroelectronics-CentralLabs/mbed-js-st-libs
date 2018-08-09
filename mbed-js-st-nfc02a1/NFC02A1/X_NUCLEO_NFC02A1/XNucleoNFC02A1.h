/**
  ******************************************************************************
  * @file       X_NUCLEO_NFC02A1.cpp
  * @author     AMG Central Lab
  * @version    V2.0.0
  * @date       19 May 2017
  * @brief      Singleton class that controls all the electronics inside the 
  * 			X_NUCLEO_NFC02A1 expansion board.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
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

#ifndef X_NUCLEO_NFC02A1_H_
#define X_NUCLEO_NFC02A1_H_
#include <stdint.h>

#include "mbed.h"

#include "m24lr/M24LR.h"

/**
 * Singleton class that controls all the electronics inside the X_NUCLEO_NFC02A1 expansion board.
 */
class XNucleoNFC02A1 {

public:

private:
	/**
	 * Pointer to the singleton instance, NULL if not allocated.
	 */
	static XNucleoNFC02A1 *mInstance;
	/**
	 * I2C address of the M24LR chip.
	 */
	static const uint8_t M24LR_ADDR;
        
        static const uint8_t M24LR_ADDR_DATA;

	/**
	 * Constructor
	 * @param devI2C I2C channel used to communicate with the board.
	 * @param eventCallback Function that will be called when the gpo pin status change.
	 * @param gpoName Name of the gpio pin of the M24LR chip.
	 * @param RFDisableName Pin that controls the rf antenna status.
	 * @param led1Name Pin to control the led1 status.
	 * @param led2Name Pin to control the led1 status.
	 * @param led3Name Pin to control the led1 status.
	 */
	XNucleoNFC02A1(DevI2C &devI2C,
			const PinName &gpoName,	const PinName &RFDisableName,
			const PinName &led1Name, const PinName &led2Name,
			const PinName &led3Name):
 				mM24LR(M24LR_ADDR, M24LR_ADDR_DATA, devI2C),
				mNfcLed1(led1Name),mNfcLed2(led2Name),mNfcLed3(led3Name){}

public:
	static const PinName DEFAULT_SDA_PIN; //!< Default pin used for the M24LR SDA signal.
	static const PinName DEFAULT_SDL_PIN; //!< Default pin used for the M24LR SDL signal.
	static const PinName DEFAULT_GPO_PIN; //!< Default pin used for the M24LR GPO signal.
	static const PinName DEFAULT_RF_DISABLE_PIN; //!< Default pin used for M24LR RF_DISABLE signal.
	static const PinName DEFAULT_LED1_PIN; //!< Default pin to control the led 1.
	static const PinName DEFAULT_LED2_PIN; //!< Default pin to control the led 2.
	static const PinName DEFAULT_LED3_PIN; //!< Default pin to control the led 3.

    /**
	 * Create or return an instance of X_NUCLEO_NFC02A1.
	 * @param devI2C I2C channel used to communicate with the board.
	 * @param eventCallback Function that will be called when the gpo pin status change.
	 * @param gpoName Name of the gpio pin of the M24LR chip.
	 * @param RFDisableName Pin that controls the rf antenna status.
	 * @param led1Name Pin to control the led1 status.
	 * @param led2Name Pin to control the led1 status.
	 * @param led3Name Pin to control the led1 status.
	 */
	static XNucleoNFC02A1* instance(DevI2C &devI2C,
			const PinName &gpoName = DEFAULT_GPO_PIN,
 			const PinName &RFDisableName = DEFAULT_RF_DISABLE_PIN,
 			const PinName &led1Name = DEFAULT_LED1_PIN,
 			const PinName &led2Name = DEFAULT_LED2_PIN,
 			const PinName &led3Name = DEFAULT_LED3_PIN);

	/**
	 * @return board led1.
	 */
	DigitalOut& get_led1() {
		return mNfcLed1;
	}

	/**
	 * @return board led2.
	 */
	DigitalOut& get_led2() {
		return mNfcLed2;
	}

	/**
	 * @return board led3.
	 */
	DigitalOut& get_led3() {
		return mNfcLed3;
	}

	/**
	 * @return NFC Chip.
	 */
    M24LR& get_M24LR() {
		return mM24LR;
	}

	virtual ~XNucleoNFC02A1() {
	}

private:
    M24LR mM24LR;

	DigitalOut mNfcLed1;
	DigitalOut mNfcLed2;
	DigitalOut mNfcLed3;

};
#endif /* X_NUCLEO_NFC02A1_H_ */
