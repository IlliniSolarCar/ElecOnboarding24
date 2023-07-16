/*
 * This is where you should declare any simple inputs/outputs, like
 * instances of DigitalOut, DigitalIn, AnalogIn, PwmOut, InterruptIn
 * which you might pass in as arguments to more complicated peripherals
 * or use directly.
 *
 * If using macros for pin names do so like so:
 * #define P_LED_FOO P2_4
 *
 * You should place those definitions here.
 */

#ifndef MBED15X9_SKELETON_PINS_H_
#define MBED15X9_SKELETON_PINS_H_

#include <mbed.h>

/*
 *    COMMON PIN DEFINITIONS
 *    UPDATE FOR EACH BOARD!
 */
#define P_CAN_rd P0_21
#define P_CAN_td P0_22
#define P_LED1 P1_20
#define P_LED2 P1_21
#define P_LED3 P1_22
#define P_LED4 P1_23

/*
 * BOARD SPECIFIC PINS
 */

//Power Management
#define P_CAP_SENSE P0_3
#define P_CAP_STAT  P0_9
#define P_CAP_EN	P0_8

//Temperature Sensing
#define P_MCU_TEMP	P0_23
//#define P_PWR_TEMP	P1_2
#define P_LED_TEMP	P0_25

//Indicator LEDs
#define P_RSIGNAL	P2_4
#define P_LSIGNAL	P2_6
#define P_LLED		P2_5
#define P_RLED		P2_3

//SPI Devices
#define P_SPI_CLK	P0_15
#define P_SPI_MOSI	P0_18
#define P_SPI_MISO	P0_17

//#define P_CS_ACCEL	P0_9

#define P_CS_LED	P0_28
#define P_EN_LED	P0_27
#define P_RES_LED	P3_25

#define P_CS_OLED	P2_1
#define P_RES_OLED	P2_0

//#define P_CS_ENC	P0_30 //Controlled by MUX in hardware
#define P_RES_ENC	P3_26

//Button Inputs
#define P_PTT			P0_24
#define P_CRUISE_EN		P1_15
#define P_CRUISE_UP		P1_0
#define P_COAST			P1_31

//MUX
#define P_MUX_SEL		P0_16
#define P_MUX_EN		P0_19


// Encoder Pins No separate encoder SPI in v8
//#define P_ENC_RESET 	P1_1
//#define P_ENC_SPI_CLK 	P0_27
//#define P_ENC_SPI_MISO 	P0_1

// i2c pins No i2c in v8
//#define P_SCL P0_22
//#define P_SDA P0_23

#endif

/*
 * COMMON PIN OBJECT DECLARATIONS
 */

extern DigitalOut led1;
extern DigitalOut led2;
extern DigitalOut led3;
extern DigitalOut led4;

/*
 * BOARD SPECIFIC PIN OBJECT DECLARATIONS
 */

extern DigitalIn capSense;
extern DigitalIn capStat;
extern DigitalOut chargeEn;

extern DigitalOut sevenSegCS;
extern DigitalOut sevenSegReset;
extern DigitalOut sevenSegEn;

extern DigitalOut OLEDCS;

extern DigitalOut OLEDReset;

extern DigitalOut ENC_CS;
extern DigitalOut ENC_RES;

extern AnalogIn mcuTemp;
extern AnalogIn pwrTemp;
extern AnalogIn ledTemp;

extern DigitalOut MUXSel;
extern DigitalOut MUXEn;
