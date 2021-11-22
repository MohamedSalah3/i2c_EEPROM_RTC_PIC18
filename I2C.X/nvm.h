/* 
 * File:   nvm.h
 * Author: Dell
 *
 * Created on November 22, 2021, 8:16 PM
 */

#ifndef NVM_H
#define	NVM_H

#define	NVM_H
#include "i2c_EEPROM.h"
#include "std_types.h"
#include "error.h"

ERROR_STATUS nvm_Write(uint8_t u8_data,uint16_t u16_address);

ERROR_STATUS nvm_Read(uint8_t *u8_data,uint16_t u16_address);


#endif	/* NVM_H */

