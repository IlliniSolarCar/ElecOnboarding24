/*
* can_id.h - Adapted from Argo and Zephyr
 * Purpose: Can ID Definitions
 * Author(s): Jonathan Mullen, Derek Chou
 */

#ifndef BRIZO_CAN_ID_H
#define BRIZO_CAN_ID_H

#include <stdint.h>

/*
 * Place any network wide CAN configurations here
 */
#define CAN_FREQUENCY				500000



namespace BRIZO_CAN{

	/*
	 * Struct for formatting info about CAN messages
	 */
	struct can_message_info{
		int ID;
		uint32_t RATE;
	};

	/*
	 * Define CAN messages and their Rate here.
	 * Message ID allocation and their frequency requires approval
	 * Lower ID's are higher priority
	 *
	 * Follow the naming convention:   <sending board>_<message name>
	 *
	 * See the CAN/README.md for more details on choosing IDs
	 */



	// 0x0## High Priority / Low Frequency
	constexpr can_message_info DEMO_HEART 		{0x020, 1000000};
	// DASH
	constexpr can_message_info DASH_HEART		{0x050, 1000000};
	// WHEEL
	constexpr can_message_info WHEEL_HEART		{0x070, 1000000};
	constexpr can_message_info WHEEL_ERROR		{0x071, 0};
	constexpr can_message_info WHEEL_WARN		{0x072, 0};
	constexpr can_message_info WHEEL_TEMPS		{0x074, 1000000};

	// 0x1## Reserved for Testing and Chase Car messages
	constexpr can_message_info CHASE_CAR_LIGHT_ON		{0x100, 0};
	constexpr can_message_info CHASE_CAR_LIGHT_OFF		{0x101, 0};
	// 0x2## Critical Power and Drive messages
	constexpr can_message_info DASH_DRIVE_DIR_AND_BRAKE		{0x250, 100000};

	// 0x3## Ancillary Control messages
	constexpr can_message_info DASH_LIGHT_SET_STATES		{0x300, 200000};
	constexpr can_message_info WHEEL_TURN_SIGNALS_HORN		{0x301, 250000};
	constexpr can_message_info DASH_PERIPHERALS_STATES		{0x302, 250000};
	constexpr can_message_info DASH_LIGHT_OUTPUT			{0x303, 200000};

	// 0x4## Diagnostics info and Raw data

	//Wheel Diagnostics
	const can_message_info WHEEL_RAWBTN			{0x471, 50000};

	// 0x56# to 0x5FF Reserved for Neutrino MPPTs
	// 0x7F0 to 0x7FF Reserved for Wavesculptor MPPTs

} // end namespace CAN

//ARGO ID's for inspiration

//// Heartbeats
//#define CAN_HEART_BMS				0x040
//#define CAN_HEART_MCC_LEFT			0x042
//#define CAN_HEART_MCC_RIGHT			0x043
//#define CAN_HEART_LPCTELEMETRY		0x048
//#define CAN_HEART_MPPT(I)           0x060 + I
//#define CAN_HEART_DEMO_CODE			0x050
//#define CAN_HEART_DASH				0x045
//#define CAN_HEART_LIGHT		        0x046
//
//
//#define CAN_HEART_PDS				0x047
//
//
//// BMS controls and messages
//#define CAN_BMS_CAR_SHUTDOWN        0x30 // Enum, defined in BMS
//#define CAN_BMS_CAR_WARNING			0x31
//
//#define CAN_PACK_VOLTAGE			0x123
//#define CAN_PACK_CURRENT			0x124
//#define CAN_CELL_VOLTAGE(I,J)		(0x130 + I*0x10 + J)
//#define CAN_PACK_TEMPERATURE_HIGH	0x125
//#define CAN_PACK_TEMPERATURE_LOW	0x126
//#define CAN_PACK_TEMPERATURE_AVG	0x127
//#define CAN_BMS_BALANCING			0x128
//#define CAN_BMS_STATES				0x129
//#define CAN_PACK_TEMPERATURE(I)     (0x160 + I)
//
//
//#define CAN_BMS_SHUTDOWN_VOLTAGE	0x32
//#define CAN_BMS_SHUTDOWN_CURRENT	0x32
//#define CAN_BMS_SHUTDOWN_TEMP		0x33
//#define CAN_PACK_VOLTAGE			0x123
//#define CAN_PACK_CURRENT			0x124
//#define CAN_PACK_CHARGE			        0x122
//#define CAN_CELL_VOLTAGE(I)			(0x130 + (I))
//#define CAN_PACK_TEMPERATURE_HIGH	0x125
//#define CAN_PACK_TEMPERATURE_LOW	0x126
//#define CAN_PACK_TEMPERATURE_AVG	0x127
//#define CAN_BMS_TRIGGER_BALANCING		0x128
//#define CAN_BMS_STATES				0x129
//#define CAN_PACK_TEMPERATURE(I)     (0x160 + (I))
//#define CAN_BMS_FAN_SPEED(I)		(0x170 + (I))
//#define CAN_BMS_CELLS_BALANCING	0x180
//
//
//#define CAN_LIGHT_CONTROL			0x230
//#define CAN_HORN					0x231
//#define CAN_DASH_BUTTONS			0x232
//#define CAN_DASH_BUTTONS_REDUN		0x233
//#define CAN_BRAKE_LIGHT				0x234
//
//#define CAN_DASH_SWITCHES			0x700
//
//#define CAN_PDS_STATE				0x7bb
//
//
//// MCC queries - left
//#define CAN_MCC_LEFT_RPM      		0x310
//
//// MCC queries - right
//#define CAN_MCC_RIGHT_RPM     		0x311
//
//// MCC Input
//#define CAN_PEDAL_POS				0x282
//
//
//#define CAN_BRAKE_BUTTON            0x283
//
//
//// MCC thermistors
//#define CAN_MCC_LEFT_TEMP			0x320
//#define CAN_MCC_RIGHT_TEMP			0x321
//
//#define CAN_MOTOR_OVERHEAT_L		0x322
//#define CAN_MOTOR_OVERHEAT_R		0x323
//
//#define CAN_MPPT_PWR(I)    0x550 + I
//#define CAN_MPPT_VC(I)     0x560 + I
//#define CAN_MPPT_T(I)      0x570 + I
//#define CAN_MPPT_DATA(I)   0x580 + I
//
//
//// MPPT controls and messages
//// http://goo.gl/KFx2nd
//#define CAN_FRONT_RIGHT_MPPT_STATUS	0x600
//#define CAN_FRONT_LEFT_MPPT_STATUS	0x601
//#define CAN_BACK_RIGHT_MPPT_STATUS	0x602
//#define CAN_BACK_LEFT_MPPT_STATUS	0x603
//#define CAN_FRONT_RIGHT_MPPT_ENABLE	0x610
//#define CAN_FRONT_LEFT_MPPT_ENABLE	0x611
//#define CAN_BACK_RIGHT_MPPT_ENABLE	0x612
//#define CAN_BACK_LEFT_MPPT_ENABLE	0x613
//
//
//#define CAN_DRIVE_CONTROL			0x700
//#define CAN_BRAKE_LIMIT				0x704
//
//
//
///** Mostly just tells the current RTC time. */
//#define CAN_TELEMETRY_INFO          0x800
//#define CAN_TELEMETRY_STAT          0x801
//#define CAN_TELEMETRY_RTC           0x802
//#define CAN_TELEMETRY_TEMP          0x803
//
///*
// * FOR IIC TEST
// */
//#define IIC_TEST_HEARTBEAT 			0X700
//
//#define CAN_CONTACTOR_CONTROL		0x701



#endif // BRIZO_CAN_ID_H //
