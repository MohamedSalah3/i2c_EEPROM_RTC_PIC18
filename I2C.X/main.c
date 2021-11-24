/*
 * File:   newmain.c
 * Author: Dell
 *
 * Created on November 22, 2021, 5:02 PM
 */


#include <xc.h>
#include "nvm.h"
void main(void) {
    nvm_Write('M',0x7f00);
    while (1){

    }
    return;
}
