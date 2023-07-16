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
		unsigned int ID;
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

	//BMS
	constexpr can_message_info BMS_ALIVE		{0x030, 1000000};
	constexpr can_message_info BMS_ERROR		{0x031, 0};
	constexpr can_message_info BMS_WARN		{0x032, 200000};
	constexpr can_message_info BMS_BATTERY_SHUTDOWN	{0x033, 200000};
	constexpr can_message_info BMS_BATTERY_WARN		{0x034, 200000};
	constexpr can_message_info BMS_MODE				{0x035, 200000};

	//PDS
	constexpr can_message_info PDS_HEART		{0x040, 1000000};
	constexpr can_message_info PDS_ERROR		{0x041, 0};
	constexpr can_message_info PDS_WARN			{0x042, 0};

	// DASH
	constexpr can_message_info DASH_HEART		{0x050, 1000000};

	// WHEEL
	constexpr can_message_info WHEEL_HEART		{0x070, 1000000};
	constexpr can_message_info WHEEL_ERROR		{0x071, 0};
	constexpr can_message_info WHEEL_WARN		{0x072, 0};
	constexpr can_message_info WHEEL_MODE		{0x073, 1800000000};
	constexpr can_message_info WHEEL_TEMPS		{0x074, 1000000};
	constexpr can_message_info WHEEL_FLAG_PTT	{0x075, 5000000};
	constexpr can_message_info WHEEL_VERSION	{0x07A, 1800000000};
	constexpr can_message_info WHEEL_CONFIG		{0x07B, 1800000000};

	// WHEEL BRIDGE
	constexpr can_message_info WHEEL_BRIDGE_HEART_AND_TEMPS		{0x0C0, 1000000};
	constexpr can_message_info WHEEL_BRIDGE_ERROR				{0x0C1, 0};
	constexpr can_message_info WHEEL_BRIDGE_WARN				{0x0C2, 0};

	// MCC
	constexpr can_message_info MCCR_HEART		{0x080, 1000000};
	constexpr can_message_info MCCL_HEART		{0x081, 1000000};
	constexpr can_message_info MCCR_ERROR		{0x082, 0};
	constexpr can_message_info MCCL_ERROR		{0x083, 0};
	constexpr can_message_info MCCR_WARN		{0x084, 0};
	constexpr can_message_info MCCL_WARN		{0x085, 0};
	constexpr can_message_info MCCR_MC_ERROR	{0x086, 1000000};
	constexpr can_message_info MCCL_MC_ERROR	{0x087, 1000000};
	constexpr can_message_info MCCR_CURRENT 	{0x088, 100000};
	constexpr can_message_info MCCL_CURRENT 	{0x089, 100000};
	constexpr can_message_info MCCR_CLUTCH		{0x090, 2000000};
	constexpr can_message_info MCCL_CLUTCH		{0x091, 2000000};

	// TELEMETRY
	constexpr can_message_info TELEMETRY_HEART	{0x0A0, 1000000};
	constexpr can_message_info TELEMETRY_ERROR	{0x0A1, 0};
	constexpr can_message_info TELEMETRY_WARN	{0x0A2, 0};

	//WAVESCULPTOR DRIVE COMMAND STUFF
	constexpr can_message_info MOTOR_DRIVE_COMMAND	{0x201, 100000};
	constexpr can_message_info MOTOR_POWER_COMMAND	{0x202, 100000};
	constexpr can_message_info MOTOR_RESET			{0x203, 0};


	// DATALOGGER
	constexpr can_message_info DATALOGGER_HEART	{0x0B0, 1000000};
	constexpr can_message_info DATALOGGER_ERROR {0x0B1, 0};
	constexpr can_message_info DATALOGGER_WARN	{0x0B2, 0};
	constexpr can_message_info DATALOGGER_VOLTAGE_STATS	{0x0B3, 1000000};

	// 0x1## Reserved for Testing and Chase Car messages
	constexpr can_message_info CHASE_CAR_LIGHT_ON		{0x100, 0};
	constexpr can_message_info CHASE_CAR_LIGHT_OFF		{0x101, 0};
	constexpr can_message_info CHASE_CAR_MIN_FAN_PERCENT{0x102, 0};
	constexpr can_message_info CHASE_CAR_SET_BMS_ENERGY	{0x103, 0};
  constexpr can_message_info CHASE_CAR_HEARTBEAT		{0x110, 1000000};

	constexpr can_message_info DATALOGGER_SET_RTC		{0x1B0, 0};

	// 0x17x Telemetry & Testing to Wheel
	constexpr can_message_info EXTERNAL_WHEEL_CONFIG	{0x170, 0};

	// 0x2## Critical Power and Drive messages
	constexpr can_message_info BMS_PACK_VOLTAGE			{0x230, 200000};
	constexpr can_message_info BMS_PACK_CHARGE			{0x231, 1000000};
	constexpr can_message_info BMS_PACK_CURRENT			{0x232, 100000};
	constexpr can_message_info BMS_PACK_TEMPS			{0x233, 200000};
	constexpr can_message_info BMS_VOLTAGES				{0x234, 200000};
	constexpr can_message_info BMS_VOLTAGE1				{0x235, 200000};
	constexpr can_message_info BMS_VOLTAGE2				{0x236, 200000};
	constexpr can_message_info BMS_VOLTAGE3				{0x237, 200000};
	constexpr can_message_info BMS_VOLTAGE4				{0x238, 200000};
	constexpr can_message_info BMS_VOLTAGE5				{0x239, 200000};
	constexpr can_message_info BMS_VOLTAGE6				{0x23A, 200000};
	constexpr can_message_info BMS_VOLTAGE7				{0x23B, 200000};
	constexpr can_message_info BMS_TEMPERATURE1			{0x23C, 1000000};
	constexpr can_message_info BMS_TEMPERATURE2			{0x23D, 1000000};
	constexpr can_message_info BMS_TEMPERATURE3			{0x23E, 1000000};
	constexpr can_message_info BMS_12V_POWER_SENSE		{0x23F, 200000};

	constexpr can_message_info PDS_STATE        {0x240, 200000};


	constexpr can_message_info DASH_DRIVE_DIR_AND_BRAKE		{0x250, 100000};

	constexpr can_message_info WHEEL_DRIVE_CONTROLS         {0x251, 100000};
	constexpr can_message_info WHEEL_DIST_TRAVELED	{0x252, 2000000};

	constexpr can_message_info MCCR_RPM					{0x260, 100000};
	constexpr can_message_info MCCL_RPM					{0x261, 100000};
	constexpr can_message_info DASH_POWER_CTRL			{0x262, 200000};

	constexpr can_message_info BMS_FAN_SPEED			{0x2F0, 1000000};
	constexpr can_message_info BMS_BATT_SENSE_BRD_TEMPS	{0x2F1, 1000000};

	// 0x3## Ancillary Control messages
	constexpr can_message_info DASH_LIGHT_SET_STATES		{0x300, 200000};
	constexpr can_message_info WHEEL_TURN_SIGNALS_HORN		{0x301, 250000};

	//time info
	constexpr can_message_info DATALOGGER_RTC_CURR_TIME		{0x3B0, 300000000};


	// 0x4## Diagnostics info and Raw data
	constexpr can_message_info DASH_PERIPHERALS_STATES		{0x400, 250000};
	constexpr can_message_info DASH_LIGHT_OUTPUT			{0x401, 1000000};
	constexpr can_message_info DASH_FLASH_LIGHT_OUTPUT		{0x402, 200000};
	constexpr can_message_info BMS_POWER_ENERGY				{0x410, 100000};
	constexpr can_message_info BMS_EEPROM_WRITE_INFO		{0x411, 0};

	// PDS Diagnostics
	constexpr can_message_info PDS_PRECHARGE_STATUS			{0x440, 200000};
	constexpr can_message_info PDS_HV_VOLTAGES				{0x441, 200000};

	// MCC Diagnostics
	constexpr can_message_info MCCR_MC_STATUS1				{0x460, 100000};
	constexpr can_message_info MCCL_MC_STATUS1				{0x461, 100000};
	constexpr can_message_info MCCR_MC_STATUS2				{0x462, 100000};
	constexpr can_message_info MCCL_MC_STATUS2				{0x463, 100000};
	constexpr can_message_info MCCR_MC_TEMPS				{0x484, 100000};
	constexpr can_message_info MCCL_MC_TEMPS				{0x485, 100000};
	constexpr can_message_info MCCR_ENERGY					{0x486, 500000};
	constexpr can_message_info MCCL_ENERGY					{0x487, 500000};

	//Wheel Diagnostics
	constexpr can_message_info WHEEL_RAWBTN						{0x471, 50000};
	constexpr can_message_info WHEEL_7SEG_DRIVER_CKT_ERROR		{0x472, 0};
	constexpr can_message_info WHEEL_EEPROM_CRC_MISMATCH		{0x473, 0};
	constexpr can_message_info WHEEL_EEPROM_WRITE_INFO			{0x474, 600000000};
	constexpr can_message_info WHEEL_RAW_ENCODER				{0x475, 100000};


	// Telemetry Diagnostics
	constexpr can_message_info TELEMETRY_MESSAGE_COUNTS	{0x4A0, 2000000};
	constexpr can_message_info TELEMETRY_STATS			{0x4A1, 2000000};


	//Datalogger Diagnostics
	constexpr can_message_info DATALOGGER_STATE		{0x4B0, 1000000};

	// 0x56# to 0x5FF Reserved for Neutrino MPPTs
	constexpr can_message_info NEUTRINO0_BATTERY	{0x570, 500000};
	constexpr can_message_info NEUTRINO1_BATTERY	{0x571, 500000};
	constexpr can_message_info NEUTRINO2_BATTERY	{0x572, 500000};
	constexpr can_message_info NEUTRINO4_BATTERY	{0x574, 500000};

	// 0x700 to 0x720 Reserved for Wavesculptor 
	constexpr can_message_info MC_ID								{0x700, 1000000};
	constexpr can_message_info MC_STATUS							{0x701, 200000};
	constexpr can_message_info MC_BUS_MEASUREMENTS					{0x702, 200000};
	constexpr can_message_info MC_VEL_MEASUREMENTS					{0x703, 200000};
	constexpr can_message_info MC_PHASE_CURRENT_MEASUREMENTS		{0x704, 200000};
	constexpr can_message_info MC_VOLTAGE_VECTOR_MEASUREMENTS		{0x705, 200000};
	constexpr can_message_info MC_CURRENT_VECTOR_MEASUREMENTS		{0x706, 200000};
	constexpr can_message_info MC_BACKEMF_MEASUREMENTS				{0x707, 200000};
	constexpr can_message_info MC_15V_RAIL_MEASUREMENTS				{0x708, 1000000};
	constexpr can_message_info MC_3V3_1V9_RAIL_MEASUREMENTS			{0x709, 1000000};
	constexpr can_message_info MC_RESERVED_1						{0x70A, 1000000};
	constexpr can_message_info MC_HEATSINK_MOTOR_TEMPERATURE		{0x70B, 1000000};
	constexpr can_message_info MC_DSP_TEMPERATURE_MEASUREMENTS		{0x70C, 1000000};
	constexpr can_message_info MC_RESERVED_2						{0x70D, 1000000};
	constexpr can_message_info MC_ODOMETER_BUS_AH_MEASUREMENTS		{0x70E, 1000000};
	constexpr can_message_info SLIP_SPEED_MEASUREMENTS				{0x717, 200000};
	constexpr can_message_info MC_MOTOR_CHANGE						{0x712, 0};

} // end namespace CAN


#endif // BRIZO_CAN_ID_H //
