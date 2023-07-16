/*
 * This is where you should instantiate any simple inputs/outputs, like
 * instances of DigitalOut, DigitalIn, AnalogIn, PwmOut, InterruptIn
 * which you might pass in as arguments to more complicated peripherals
 *
 */

#include <mbed.h>
#include <pins.h>

/*
 * PIN OBJECT INSTANTIATIONS
 */

DigitalIn capSense(P_CAP_SENSE);
DigitalIn capStat(P_CAP_STAT);
DigitalOut chargeEn(P_CAP_EN);


//// 7 Segment Display I/O
//DigitalOut sevenSegCS(P_CS_LED);
//DigitalOut sevenSegReset(P_RES_LED);
//DigitalOut sevenSegEn(P_EN_LED);

// OLED Display I/0
DigitalOut OLEDCS(P_CS_OLED);
DigitalOut OLEDReset(P_RES_OLED);

// Encoder I/O
//DigitalOut ENC_CS(P_CS_ENC);
DigitalOut ENC_RES(P_RES_ENC);

AnalogIn mcuTemp(P_MCU_TEMP);
//AnalogIn pwrTemp(P_PWR_TEMP);
AnalogIn ledTemp(P_LED_TEMP);

/*
 * COMMON PIN OBJECT INSTANTIATIONS
 */

DigitalOut led1(P_LED1);
DigitalOut led2(P_LED2);
DigitalOut led3(P_LED3);
DigitalOut led4(P_LED4);

DigitalOut MUXSel(P_MUX_SEL);
DigitalOut MUXEn(P_MUX_EN);

