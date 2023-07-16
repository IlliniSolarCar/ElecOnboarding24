#ifdef TARGET_LPC15XX

#include "Reset.h"
#include "cmsis.h"

bool Reset::watchdogCausedReset(){
    uint16_t resetstat = LPC_SYSCON->SYSRSTSTAT;
    LPC_SYSCON->SYSRSTSTAT = 1<<2;
    if(resetstat & (1<<2)) { //The 2nd bit is the WDT reset bit
        return true;
    }
    else {
        return false;
    }
}


bool Reset::externalCausedReset(){
    uint16_t resetstat = LPC_SYSCON->SYSRSTSTAT;
    LPC_SYSCON->SYSRSTSTAT = 1<<1;
    if(resetstat & (1<<1)) { //The 1st bit is external reset
        return true;
    }
    else {
        return false;
    }
}

bool Reset::brownOutCausedReset(){
    uint16_t resetstat = LPC_SYSCON->SYSRSTSTAT;
    LPC_SYSCON->SYSRSTSTAT = 1<<3;
    if(resetstat & (1<<3)) { //The 3rd bit is the BOD reset bit
        return true;
    }
    else {
        return false;
    }
}

bool Reset::softwareCausedReset(){
    uint16_t resetstat = LPC_SYSCON->SYSRSTSTAT;
    LPC_SYSCON->SYSRSTSTAT = 1<<4;
    if(resetstat & (1<<4)) { //The 4th bit is the software reset bit
        return true;
    }
    else {
        return false;
    }
}


#endif
