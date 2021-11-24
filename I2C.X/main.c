/*
 * File:   newmain.c
 * Author: Dell
 *
 * Created on November 22, 2021, 5:02 PM
 */


#include <xc.h>
#include "nvm.h"
void main(void) {
    uint8_t data_read_eeprom = 0;
    nvm_Write('M',0x7f00);
    nvm_Read(data_read_eeprom,0x7f00);
        nvm_Write(data_read_eeprom,0x7f21);
    while (1){
        
    }
    return;
}
