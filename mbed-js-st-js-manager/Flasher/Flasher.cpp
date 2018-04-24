/**
 ******************************************************************************
 * @file    Flasher.cpp
 * @author  ST
 * @version V1.0.0
 * @date    25 October 2017
 * @brief   Library for performing flash tasks like wrting, erasing.
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
#include "Flasher.h"

/* Class Implementation ------------------------------------------------------*/

FlashIAP Flasher::flash;

/** Constructor
 * @brief	Constructor.
 */
Flasher::Flasher(){

}

/** Destructor
 * @brief	Destructor.
 */
Flasher::~Flasher(){

}

/** get_flash_address
 * @brief	Returns the flash start address.
 * @return  Start address
 */
uint32_t Flasher::get_flash_address(){
    uint32_t address = POST_APPLICATION_ADDR;

    // Get start address
    // Way 1, start from the beginnning and keep going until we find a sector
    // that is close to the post application address
    uint32_t addr = flash.get_flash_start();
    
    // ->inttypes.h
    //printf("Flash address: %" PRIu32 "\n", addr);
    
    while(addr < address){
        addr = addr + flash.get_sector_size(addr);
    }

    // Way 2,
    // just use the post application address
    //addr = address;
    
    return addr;
}
    
/** erase_flash
 * @brief	Erases theflash.
 * @return  Return code
 */
int Flasher::erase_flash(){
    flash.init();
    uint32_t addr = get_flash_address();
    if(flash.erase(addr, flash.get_sector_size(addr)) != 0){
        printf("Error erasing Flash...\n");
        flash.deinit();
        return 1; // Error while erasing
    }
    return 0;
}

/** write_to_flash
 * @brief	Writes string to flash.
 * @param	data
 * @return  Return code
 */
int Flasher::write_to_flash(string buffer){
    return write_to_flash((char *)buffer.c_str());
}

/** write_to_flash
 * @brief	Writes char pointer to flash.
 * @return  Return code
 */
int Flasher::write_to_flash(char *data){
    //printf("Flashing: %s\r\nLength: %i\r\n", data, strlen(data));
      
    flash.init();
    
    uint32_t addr = get_flash_address();
    //uint32_t next_sector = addr + flash.get_sector_size(addr);
    //size_t pages_flashed = 0;
    //uint32_t percent_done = 0;
    bool sector_erased = false;
    
    while (true) {

        // Read data for this page
        /*
        memset(page_buffer, 0, sizeof(page_buffer));
        int size_read = fread(page_buffer, 1, page_size, file);
        if (size_read <= 0) {
            break;
        }
        */

        // Erase this page if it hasn't been erased
        if (!sector_erased) {
            if(flash.erase(addr, flash.get_sector_size(addr)) != 0){
                //printf("Error erasing Flash...\n");
                flash.deinit();
                return 1; // Error while erasing
            }
            printf("Erased Flash...\n");
            sector_erased = true;
        }

        // Program page
        if(flash.program(data, addr, flash.get_page_size()) != 0){
            //printf("Error Flashing...\n");
            flash.deinit();
            return 2; // Error while flashing
        }

        printf("Flashed %i bytes\n", strlen(data));
    
        // Multiple sector write support. Not implemented yet
        /*
        addr += page_size;
        if (addr >= next_sector) {
            next_sector = addr + flash.get_sector_size(addr);
            sector_erased = false;
        }
        */
        /*
        if (++pages_flashed % 3 == 0) {
            uint32_t percent_done_new = ftell(file) * 100 / len;
            if (percent_done != percent_done_new) {
                percent_done = percent_done_new;
                printf("Flashed %3ld%%\r", percent_done);
            }
        }
        */
        flash.deinit();
        break;
        
    }
    
    //char *data_check;
    //read_from_flash(data_check);
    //delete[] page_buffer;
    return 0;
}

/** read_from_flash
 * @brief	Reads data from flash.
 * @return  Data
 */
char *Flasher::read_from_flash(){
    //uint32_t address = POST_APPLICATION_ADDR;
    char *data = (char *)get_flash_address();
    if((int)data[0] == 255){
        return 0;
    }
    return data;
}


/** print_flash
 * @brief	Print the data in flash to terminal.
 * @return  Return code
 */
int Flasher::print_flash(){
    uint32_t address = get_flash_address();
    char *data = (char *)address;
    
    flash.init();
    
    if(flash.read(data, address, flash.get_page_size()) != 0){
        //printf("Error reading Flash...\n");
        flash.deinit();
        return 1; // Error reading
    }

    if((int)data[0] == 255){
        //printf("No data exists in flash...\n");
        flash.deinit();
        return 2; // No data exists 
    }

    printf("Data: ");
    for(int i = 0; data[i] != '\0'; i++){
        //printf("%c", *((char *) (address+i)));
        printf("%c", data[i]);
    }
    printf("\n");

    flash.deinit();
        
    return 0;
}

/* Sample code for applying update----------------------------------------------*/
/*
//#include "SDBlockDevice.h"
//#include "FATFileSystem.h"

//#define SD_MOUNT_PATH           "sd"
//#define FULL_UPDATE_FILE_PATH   "/" SD_MOUNT_PATH "/" MBED_CONF_APP_UPDATE_FILE

//Pin order: MOSI, MISO, SCK, CS
//SDBlockDevice sd(MBED_CONF_APP_SD_CARD_MOSI, MBED_CONF_APP_SD_CARD_MISO,
//                 MBED_CONF_APP_SD_CARD_SCK, MBED_CONF_APP_SD_CARD_CS);
//FATFileSystem fs(SD_MOUNT_PATH);

int write_to_flash()
{
    
    sd.init();
    fs.mount(&sd);

    FILE *file = fopen(FULL_UPDATE_FILE_PATH, "rb");
    if (file != NULL) {
        printf("Firmware update found\r\n");

        apply_update(file, POST_APPLICATION_ADDR);

        fclose(file);
        remove(FULL_UPDATE_FILE_PATH);
    } else {
        printf("No update found to apply\r\n");
    }

    fs.unmount();
    sd.deinit();
    
    printf("Starting application\r\n");

    mbed_start_application(POST_APPLICATION_ADDR);
    return 0;
}

void apply_update(FILE *file, uint32_t address)
{
    fseek(file, 0, SEEK_END);
    long len = ftell(file);
    printf("Firmware size is %ld bytes\r\n", len);
    fseek(file, 0, SEEK_SET);
  
    flash.init();

    const uint32_t page_size = flash.get_page_size();
    char *page_buffer = new char[page_size];
    uint32_t addr = address;
    uint32_t next_sector = addr + flash.get_sector_size(addr);
    bool sector_erased = false;
    size_t pages_flashed = 0;
    uint32_t percent_done = 0;
    while (true) {

        // Read data for this page
        memset(page_buffer, 0, sizeof(page_buffer));
        int size_read = fread(page_buffer, 1, page_size, file);
        if (size_read <= 0) {
            break;
        }

        // Erase this page if it hasn't been erased
        if (!sector_erased) {
            flash.erase(addr, flash.get_sector_size(addr));
            sector_erased = true;
        }

        // Program page
        flash.program(page_buffer, addr, page_size);

        addr += page_size;
        if (addr >= next_sector) {
            next_sector = addr + flash.get_sector_size(addr);
            sector_erased = false;
        }

        if (++pages_flashed % 3 == 0) {
            uint32_t percent_done_new = ftell(file) * 100 / len;
            if (percent_done != percent_done_new) {
                percent_done = percent_done_new;
                printf("Flashed %3ld%%\r", percent_done);
            }
        }
    }
    printf("Flashed 100%%\r\n", ftell(file), len);

    delete[] page_buffer;

    flash.deinit();
}
*/