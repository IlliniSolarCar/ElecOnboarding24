#ifdef TARGET_LPC15XX

#include "WDT.h"
#include "cmsis.h"

WDT::WDT(uint32_t timeout_us) {
    LPC_SYSCON->SYSAHBCLKCTRL0 |= (1<<22); //Set bit 22 to 1 to enable WDT register interface
    LPC_SYSCON->PDRUNCFG &= ~(1<<20); //Set bit 20 to 0 to power WDT analog block
    LPC_WWDT->MOD = 0x02; //Disable, Reset on timeout, Clear timeout flag, Clear warning interrupt, TC can be changed anytime, Unlocked
    setTimeout(timeout_us);
}

void WDT::setTimeout(uint32_t timeout_us) {
    /*
     * Calculating TC Value from timeout in microseconds
     * TC*T_503*4=timeout
     * TC=timeout/(T_503*4)
     * TC=timeout/(4*1000/503)
     * TC=timeout*503/4000
     */
    uint32_t TCValue;
    TCValue = timeout_us*503/4000;
    TCValue &= ((1<<24)-1); //Mask so it doesn't write to reserved registers (24-31)
    LPC_WWDT->TC=TCValue; //Load the value into the register
}

void WDT::enable() {
    LPC_WWDT->MOD |= 0x01; //set enable bit
    feed(); //feed once to start
}

bool WDT::causedReset() {
    uint16_t resetstat = LPC_SYSCON->SYSRSTSTAT;
    if(resetstat & (1<<2)) { //The 2nd bit is the WDT reset bit
        return true;
    }
    else {
        return false;
    }
}

void WDT::feed() {
    //Disable interrupts while feeding
    __disable_irq();
    //The feed register is fed with 0xAA then 0x55 to reset the counter
    LPC_WWDT->FEED = 0xAA;
    LPC_WWDT->FEED = 0x55;
    __enable_irq();
}

#endif
