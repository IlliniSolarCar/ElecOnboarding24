/*
* can_data.h - Adapted from Argo and Zephyr can_struct.h
 * Purpose: Shared CAN data structs, enums, etc.
 * Author(s): Jonathan Mullen
 */

#ifndef BRIZO_CAN_DATA_H
#define BRIZO_CAN_DATA_H

#include <stdint.h>

namespace BRIZO_CAN{

	/*
	 *
	 * 		Below are data structs for data sent on CAN
	 * 		Additionally, bitmaps/enums for messages should be stored here
	 * 		For enums and bitmaps, please follow the naming convention to avoid naming conflicts:
	 *
	 * 			enum BoardNameDataName {
	 * 				boardNameDataName_firstItem = #,
	 * 				boardNameDataName_secondItem = #
	 * 			}
	 *
	 */

	/*
	 * * * * * * * * * * * *
	 * 		DASH DATA     *
	 * * * * * * * * * * * *
	 */

	/*
	 * Dash Data
	 */
	enum DashDriveDirection : uint8_t {
		dashDriveDirection_forward = 0,
		dashDriveDirection_neutral = 1,
		dashDriveDirection_reverse = 2
	};

	struct DashBrakeAndDirection {
		DashDriveDirection drive_dir;
		uint8_t mechBrakePressed;
	};

	enum DashLightState {
		dashLightState_leftTS,
		dashLightState_rightTS,
		dashLightState_hazards,
		dashLightState_brakes,
		dashLightState_headlights,
		dashLightState_leftDRL,
		dashLightState_rightDRL,
		dashLightState_parking,
		dashLightState_reverse,
	};

	enum DashPeripheralStates {
		dashPeripheralStates_revCamEnable,
		dashPeripheralStates_revCamBtnEnabled,
		dashPeripheralStates_hornState,
		dashPeripheralStates_drlHeadlightsButtonState,
		dashPeripheralStates_hazardsParkingButtonState,
	};


	/*
	 * * * * * * * * * * * *
	 * 		WHEEL DATA     *
	 * * * * * * * * * * * *
	 */

	struct WheelTemps {
		uint8_t tempMCU;
		uint8_t tempLED;
		uint8_t tempPWR;
	};

	enum WheelWarnings {
		wheelWarning_resetCAN = 1
	};

	enum WheelErrors {
		wheelError_watchdogReset = 1
	};

	/*
	 * Wheel turn + horn signal enums/structs
	 */
	enum WheelTurnSignal : uint8_t {
		wheelTurnSignal_off,
		wheelTurnSignal_on,
		wheelTurnSignal_requestOff,
		wheelTurnSignal_requestOn,
		wheelTurnSignal_unknown,
	};
	struct WheelTurnAndHorn {
		WheelTurnSignal left_turn_signal_state;
		WheelTurnSignal right_turn_signal_state;
		uint8_t horn_button_state;
	};




} // end namespace CAN



//  Some of the data structs from ARGO for inspiration


//struct MPPTData {
//	uint16_t arrayVoltage_10mV;
//	uint16_t arrayCurrent_mA;
//	uint16_t batteryVoltage_10mV;
//	uint16_t temperature_10mC;
//};
//
//struct pedalPos {
//    float accel;
//    float brake;
//};
//
//
////struct to hold flags for the mcc
//struct driveFlags {
//	bool foward : 1;
//	bool rev : 1;
//	bool neutral : 1;
//	bool regen_on : 1;
//};
//
//
//
//// Sent as CAN_BMS_CAR_SHUTDOWN when turning off the car
//enum BMSMeasurementStatus {
//	NO_PROBLEM,
//	LTC6804_UNREACHABLE,
//	CELL_UNDERVOLTAGE,
//	CELL_OVERVOLTAGE,
//	OVERTEMPERATURE,
//	OVERCURRENT,
//	BATTERY_POWERED,
//	OFF_BUTTON_PRESS,
//	OVERCHARGE,
//	THERMISTORSBOARD_UNREACHABLE
//};
//
///**
// * To be sent out periodically, notifying the rest of the can nodes on Zephyr
// * of the state of BMS.
// */
//struct BMSState {
//	BMSMeasurementStatus status;
//	char flags;
//};
//
////struct to hold what user controlled contactors are on
//struct contactorFlags {
//	bool contactor_solar : 1;
//	bool contactor_charge : 1;
//
//};

#endif /* BRIZO_CAN_DATA_H */
