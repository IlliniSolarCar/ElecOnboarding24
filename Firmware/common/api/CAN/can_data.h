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
	 * 			Design your structs with Bit Alignment in mind
	 *			In C data types can only be aligned to bytes a multiple of their size
	 *			The simplest way is to order items largest to smallest, 
	 *				smaller types can always be aligned to the end of a bigger type
	 *			A uint8_t (1 byte) can be aligned to any byte, 
	 *				but uint16_t (2 bytes) only to even bytes
	 * 			Additionally the struct size will always be a multiple of the size of
	 *				the largest item. So a struct with a uint32_t will be 4 or 8 bytes
	 *
	 *			For example the left struct is 6 bytes, but the right one is 4 bytes
 	 *				struct DemoStruct {			struct DemoStruct {
	 *					uint8_t oneByte;			uint16_t twoBytes;
	 *					uint16_t twoBytes;			uint8_t oneByte;
	 *					uint8_t anotherByte;			uint8_t anotherByte;
	 *				};					};
	 *
	 *
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
	 * 		GENERIC DATA   *
	 * * * * * * * * * * * *
	 */

	// the operating mode of the board
	// not all boards will implement all of them
	enum operationMode : uint8_t {
		operationMode_startUp = 0,
		operationMode_normalAuxPower = 9,
		operationMode_normal = 10,
		operationMode_normalRoad,
		operationMode_normalTrack,
		operationMode_normalScrutineering,
		operationMode_dischargeOnly = 20,
		operationMode_chargingMode = 30,
		operationMode_shutdown = 50,
	};

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

	enum DashLightOutput {
		dashLightOutput_whiteFR1_head,
		dashLightOutput_whiteFR1_drl,
		dashLightOutput_whiteFR2_head,
		dashLightOutput_whiteFL1_head,
		dashLightOutput_whiteFL1_drl,
		dashLightOutput_whiteFL2_head,
		dashLightOutput_whiteR_BPSfault,
		dashLightOutput_whiteR_reverse,
		dashLightOutput_redR_highBrake,
		dashLightOutput_redRR1_brake,
		dashLightOutput_redRR1_tail,
		dashLightOutput_redRR2_brake,
		dashLightOutput_redRR2_tail,
		dashLightOutput_redRL1_brake,
		dashLightOutput_redRL1_tail,
		dashLightOutput_redRL2_brake,
		dashLightOutput_redRL2_tail,
	};
	enum DashFlashLightOutput {
		dashLightFlashOutput_amberFR1_turn,
		dashLightFlashOutput_amberFR1_park,
		dashLightFlashOutput_amberFR2_turn,
		dashLightFlashOutput_amberFR2_park,
		dashLightFlashOutput_amberSR_turn,
		dashLightFlashOutput_amberSR_park,
		dashLightFlashOutput_amberFL1_turn,
		dashLightFlashOutput_amberFL1_park,
		dashLightFlashOutput_amberFL2_turn,
		dashLightFlashOutput_amberFL2_park,
		dashLightFlashOutput_amberSL_turn,
		dashLightFlashOutput_amberSL_park,
		dashLightFlashOutput_amberRR1_turn,
		dashLightFlashOutput_amberRR1_park,
		dashLightFlashOutput_amberRR2_turn,
		dashLightFlashOutput_amberRR2_park,
		dashLightFlashOutput_amberRL1_turn,
		dashLightFlashOutput_amberRL1_park,
		dashLightFlashOutput_amberRL2_turn,
		dashLightFlashOutput_amberRL2_park
	};

	enum DashPeripheralStates {
		dashPeripheralStates_revCamEnable,
		dashPeripheralStates_revCamBtnEnabled,
		dashPeripheralStates_hornState,
		dashPeripheralStates_drlHeadlightsButtonState,
		dashPeripheralStates_hazardsParkingButtonState,
		NUM_DASH_PERIPHERAL_STATES
	};

	enum DashPowerCtrl {
		dashPowerCtrl_chargingEnabled = 0,
		dashPowerCtrl_motorOn
	};

	/*
	 * * * * * * * * * * * *
	 *      WHEEL DATA     *
	 * * * * * * * * * * * *
	 */

	struct WheelTemps {
		uint8_t tempMCU;
		uint8_t tempLED;
		uint8_t tempPWR;
	};

	enum WheelWarnings {
		wheelWarning_none = 0,
		wheelWarning_resetCAN,
		wheelWarning_MCUTemp,
		wheelWarning_LEDTemp,
		wheelWarning_PowerTemp,
		wheelWarning_superCapPower,
		wheelWarning_canReadLimitHit,
		wheelBridgeWarning_encoderParityError,
		wheelBridgeWarning_encoderLinearityError,
		wheelBridgeWarning_encoderCordOvError,
		wheelWarning_EEPROMWriteSkipped,
		wheelWarning_EEPROMCRCMismatches
	};

	enum WheelErrors {
		wheelError_none = 0,
		wheelError_watchdogReset,
		wheelError_startOnCapPower,
		wheelError_superCapPower,
		wheelError_sevenSegOverTemp,
		wheelError_sevenSegOutput,
		wheelError_sevenSegSetup,
		wheelError_OLEDSetup,
		wheelError_encoderTimeout,
		wheelError_callBacks,
		wheelError_configSetToDefault,
		wheelError_brownOutReset,
		wheelError_externalReset,
		wheelError_softwareReset
	};

	enum WheelBridgeWarnings : uint8_t {
		wheelBridgeWarning_none = 0,
		wheelBridgeWarning_resetCAN,
		wheelBridgeWarning_wheelCANReadLimitHit,
		wheelBridgeWarning_vehicleCANReadLimitHit,
		wheelBridgeWarning_highTemp
	};

	enum WheelBridgeErrors : uint8_t {
		wheelBridgeError_none = 0,
		wheelBridgeError_unconnected,
		wheelBridgeError_watchdogReset,
		wheelBridgeError_noRxWheelCAN,
		wheelBridgeError_noRxVehicleCAN
	};
	struct WheelBridgeTempHeart {
		uint32_t heartbeat;
		uint8_t temp;
	};

	enum Wheel7SegDriverDevice : uint8_t {
		wheelDevice0,
		wheelDevice1,
		wheelDevice2,
		wheelDevice3
	};

	struct Wheel7SegDriverCktError {
		uint8_t errorType;
		Wheel7SegDriverDevice deviceIndex;
		uint16_t LED;
	};

	enum WheelEEPROMBitMap : uint8_t {
		/* Note, this EEPROM is not used in the Wheel Code for Safety around EEPROM
		 * It should mirror the one in WheelMemory.h so that CAN messages can be decoded */
		wheelEEPROMBitMap_writeCount = 0,
		wheelEEPROMBitMap_config,
		wheelEEPROMBitMap_configBackup,
		wheelEEPROMBitMap_maxEEPROMAddr //always last!
	};

	struct WheelEEPROMInfo {
		uint32_t recordsWritten;
		uint32_t writeCount;
	};

	struct WheelVersions {
		uint16_t canSpec;
		uint8_t hardware;
		uint8_t firmwareMajorMinor;
		uint8_t firmwarePatch;		
	};


	enum WheelConfig : uint8_t {
		/* Changing the order of this will break data saved on the wheel!
		 * Take care with changes other than appending new ones!  */
		wheelConfig_localBuild,
		wheelConfig_boardID0,
		wheelConfig_boardID1,
		wheelConfig_boardID2,
		wheelConfig_debugMessages,
		wheelConfig_useKMH,
		wheelConfig_enableEEPROM,
		wheelConfig_bypassSafeStart,
		wheelConfig_OLEDBrightness0,
		wheelConfig_OLEDBrightness1,
		wheelConfig_OLEDBrightness2,
		wheelConfig_7SegBrightness0,
		wheelConfig_7SegBrightness1,
		wheelConfig_7SegBrightness2,
		/* enum Count should be last always, it is not used in memory
		 * New items can safely be appended to the list before this comment   */
		wheelConfig__lastEnumItem,
	};
	/*
	 *  Wheel drive button bitmap, RPM, and torque
	 */
	enum WheelDriveControlModes : uint8_t {
		wheelDriveControlModes_coast,
		wheelDriveControlModes_regen,
		wheelDriveControlModes_CCInternal,
		wheelDriveControlModes_CCReqOff,
		wheelDriveControlModes_CCReqOn,
	};

	struct WheelDriveControls{
		uint16_t RPM;
		uint8_t buttonStatus;
		uint8_t torque;
	};

	/*
	 * Wheel turn + horn signal enums/structs
	 */
	struct WheelFlagPTT {
		uint8_t flagHeldTime;
		uint8_t pttHeldTime;
	};

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

	struct WheelExternalConfig {
		uint32_t toChange;
		uint32_t configValues;
	};

	/*
	 * * * * * * * * * * * *
	 * 		MCC DATA	   *
	 * * * * * * * * * * * *
	 */

	enum MccWarnings : uint8_t {
		mccWarning_none = 0,
		mccWarning_resetCAN,
	};

	enum MccErrors : uint8_t {
		mccError_none = 0,
		mccError_watchdogReset,
		mccError_initFailure,
		mccError_failToAccelTimeout,
		mccError_incrementError,
		mccError_potentiometerError,
		mccError_accelTimeout,
		mccError_accelTimeoutAndIncrementErr,
		mccError_requestAccelFailure,
		mccError_requestRegenFailure,
		mccError_setDriveDirFailure,
		mccError_brakeTimeout,
		mccError_highTemperatureMcc,
		mccError_highTemperatureMotor,
		mccError_PDSTimeout,
		mccError_PDSbadState,
		mccError_clutchOnFailure,
		mccError_clutchOffFailure

	};

	enum MccMCState : uint8_t {
		mccMCState_forward = dashDriveDirection_forward,
		mccMCState_neutral = dashDriveDirection_neutral,
		mccMCState_reverse = dashDriveDirection_reverse,
		mccMCState_error
	};

	enum MccMCErrors : uint8_t {
		mccMCErrors_none = 0,
		mccMCErrors_overCurrent,
		mccMCErrors_hallSensorFault,
		mccMCErrors_motorLocked,
		mccMCErrors_sensorFault1,
		mccMCErrors_sensorFault2,
		mccMCErrors_highBatteryVoltage,
		mccMCErrors_overHeat,
	};

	enum MmmMCStatusBits : uint8_t {
		mccMCStatusBits_pwrReq = 0,
		mccMCStatusBits_pwrEco,
		mccMCStatusBits_driveDir,
		mccMCStatusBits_cruiseActive,
		mccMCStatusBits_isWaveSculptor
	};

	struct MccMCStatus1 {
		uint8_t accel;
		uint8_t regen;
		uint8_t requestedAccel;
		uint8_t requestedRegen;
	};
	struct MccMCStatus2 {
		MccMCState state;
		uint8_t statusBits;
	};
	struct MccTemps {
			uint16_t tempMccOne;
			uint16_t tempMccTwo;
			uint16_t tempMotorOne;
			uint16_t tempMotorTwo;
	};
	/*
	 * * * * * * * * * * * *
	 *      BMS DATA       *
	 * * * * * * * * * * * *
	 */

	enum BatteryShutdown : uint8_t {
		batteryShutdown_off = 0,
		batteryShutdown_cellUnderVoltage,
		batteryShutdown_cellOverVoltage,
		batteryShutdown_overCurrentDischarge,
		batteryShutdown_overCurrentCharge,
		batteryShutdown_overTemperatureDischarge,
		batteryShutdown_overTemperatureCharge,
		batteryShutdown_auxPackPowered,
		batteryShutdown_LTC6811Unreachable,
		batteryShutdown_currentADCUnreachable,
		batteryShutdown_emergencyStop,
		BATTERY_NUM_SHUTDOWNS
	};

	enum BatteryWarnings : uint8_t {
		batteryWarning_underVoltage = 0,
		batteryWarning_overVoltage,
		batteryWarning_overCurrentDischarge,
		batteryWarning_overCurrentCharge,
		batteryWarning_overTemperatureDischarge,
		batteryWarning_overTemperatureCharge,
		batteryWarning_underVoltageCritical,
		batteryWarning_overVoltageCritical,
		batteryWarning_overCurrentDischargeCritical,
		batteryWarning_overCurrentChargeCritical,
		batteryWarning_overTemperatureDischargeCritical,
		batteryWarning_overTemperatureChargeCritical,
		batteryWarning_contactorLowFailure,
		batteryWarning_contactorHighFailure,
		batteryWarning_contactorLowWeld,
		batteryWarning_contactorHighWeld,
		BATTERY_NUM_WARNINGS
	};
	enum BmsErrors {
		bmsError_none = 0,
		bmsError_watchdogReset,
		bmsError_EnergySetToDefault,
		bmsError_EnergyHiSetToDefault,
		bmsError_EnergyLoSetToDefault
	};
	enum BMSWarnings {
		bmsWarning_none = 0,
		bmsWarning_resetCAN,
		bmsWarning_EEPROMWriteSkipped,
		bmsWarning_EEPROMCRCMismatches
	};

	struct BMSEEPROMInfo {
		uint32_t recordsWritten;
		uint32_t writeCount;
	};

	struct BMSMinMaxAvg {
		uint16_t minVal;
		uint16_t maxVal;
		uint16_t avgVal;
	};

	/*
		 * * * * * * * * * * * *
		 *      PDS DATA       *
		 * * * * * * * * * * * *
		 */

	enum PdsState : uint8_t {
		pdsState_StartOff,
		pdsState_Charging,
		pdsState_Precharge,
		pdsState_PrechargeSwap,
		pdsState_DischargeOnly,
		pdsState_Operational,
	};

	enum PdsError : uint8_t {
		pdsError_None = 0,
		pdsError_PrechargeFuseError,
		pdsError_MotorContactorFailure,
		pdsError_SolarContactorFailure,
		pdsError_MotorContactorWeld,
		pdsError_SolarContactorWeld,
		pdsError_NoMotHeart,
		pdsError_NoBatHeart,
		pdsError_ADCConfigFailure,
		pdsError_ADCReadFailure,
		pdsError_Wdt,
		pdsError_ChargeSwitchToggleError
	};

	enum PdsWarn: uint8_t {
		pdsWarn_None = 0,
		pdsWarn_NoMotHeart,
		pdsWarn_NoBatHeart,
		pdsWarn_ADCConfigErrorRemoved,
		pdsWarn_PrechargeFaultyADCBypass,
		pdsWarn_PrechargeToolongBypass
	};

	enum PdsPrechargeVoltageState : uint8_t {
		PdsPrechargeVoltageState_normalVoltage = 0,
		PdsPrechargeVoltageState_fuseBlown,
		PdsPrechargeVoltageState_readFailure = 2,
		PdsPrechargeVoltageState_configFailure = 3
	};
	enum PdsPrechargeCurrentState : uint8_t {
		PdsPrechargeCurrentState_safeCurrent = 0,
		PdsPrechargeCurrentState_semiSafeCurrent,
		PdsPrechargeCurrentState_unsafeCurrent,
		PdsPrechargeCurrentState_readFailure = 3,
		PdsPrechargeCurrentState_configFailure = 4
	};
	enum PdsPrechargeState : uint8_t {
		PdsPrechargeState_doneNormally = 0,
		PdsPrechargeState_doneSemiSafe = 1,
		PdsPrechargeState_doneAdcBrokenTimeout = 2,
		PdsPrechargeState_currentNotSafe,
		PdsPrechargeState_FuseBlown
	};
	struct PdsPrechargeStatus {
		uint16_t voltage;
		int16_t current;
		PdsPrechargeVoltageState voltageState;
		PdsPrechargeCurrentState currentState;
		PdsPrechargeState prechargeState;

	};
	struct PdsHVVoltages {
		uint16_t batteryVoltage;
		uint16_t busVoltage;
	};
	enum PdsOutputs : uint8_t {
		PdsOutputs_motorContactor = 0,
		PdsOutputs_solarContactor,
		PdsOutputs_precharge,
		PdsOutputs_chargeSwitch,
		PdsOutputs_chargeSwitchRequested
	};
	struct PdsStateInfo {
		PdsState state;
		uint8_t outputs;
	};

	/*
	 * * * * * * * * * * * *
	 *   TELEMETRY DATA    *
	 * * * * * * * * * * * *
	 */


	enum TelemetryWarnings : uint8_t {
		telemetryWarning_none = 0,
		telemetryWarning_resetCAN,
		telemetryWarning_unsafeMessage,
	};

	enum TelemetryErrors : uint8_t {
		telemetryError_none = 0,
		telemetryError_watchdogReset,
		telemetryError_decodeInputFailure,
		telemetryError_decodeOverflow,
		telemetryError_checkSumFailure,
		telemetryError_invalidDecodeFailure,
		telemetryError_receiveBufferOverflow,
		telemetryError_writeToXbeeFailure,
		telemetryError_sendCANError,
	};

	struct TelemetryMessageCounts {
		uint32_t numMessagesReceivedCAN;
		uint32_t numMessagesReceivedXbee;
	};

	struct TelemetryStats {
		int16_t boardTemp;
		uint8_t rssi;
		uint8_t sense5v;
		uint8_t sense12v;
	};

	/*
	 * * * * * * * * * * * *
	 *    WAVESCULPTOR     *
	 * * * * * * * * * * * *
	 */

	struct wsIDInfo {
		uint32_t prohelionID = 0x4003;
		uint32_t wave_serialID;
	};

	enum wsLimitFlags : uint16_t{
		wsLimitFlags_outputVoltagePWM,
		wsLimitFlags_motorCurrent,
		wsLimitFlags_velocity,
		wsLimitFlags_busCurrent,
		wsLimitFlags_busVoltageUpperLimit,
		wsLimitFlags_BusVoltageLowerLimit,
		wsLimitFlags_motorTemperature,
		wsLimitFlags_lReserved7,
		wsLimitFlags_lReserved8,
		wsLimitFlags_lReserved9,
		wsLimitFlags_lReserved10,
		wsLimitFlags_lReserved11,
		wsLimitFlags_lReserved12,
		wsLimitFlags_lReserved13,
		wsLimitFlags_lReserved14,
		wsLimitFlags_lReserved15,
	};

	enum wsErrorFlags : uint16_t{
		wsErrorFlags_hardwareOverCurrent,
		wsErrorFlags_softwareOverCurrent,
		wsErrorFlags_DCBusOverVoltage,
		wsErrorFlags_badMotorPositionHallSequence,
		wsErrorFlags_watchdogCausedLastReset,
		wsErrorFlags_configReadError,
		wsErrorFlags_v15UnderVoltageLockOut,
		wsErrorFlags_desaturationFault,
		wsErrorFlags_motorOverSpeed,
		wsErrorFlags_eReserved9,
		wsErrorFlags_eReserved10,
		wsErrorFlags_eReserved11,
		wsErrorFlags_eReserved12,
		wsErrorFlags_eReserved13,
		wsErrorFlags_eReserved14,
		wsErrorFlags_eReserved15,
	};

	enum wsActiveMotor : uint16_t{
		wave_normalCoil,
		wave_overtakeCoil,
	};

	struct WavesculptorStatusInfo{
		uint16_t limitFlags;  //bitmpa
		uint16_t errorFlags; //bitmap
		wsActiveMotor activeMotor;
		uint8_t txErrorCount;
		uint8_t rxErrorCount;
	};

	struct WavesculptorBus {
		float busVoltage;
		float busCurrent;
	};

	struct WavesculptorVelocity {
		float motorVelocity;
		float vehicleVelocity;
	};

	struct WavesculptorPhaseCurrent {
		float phaseBCurrent;
		float phaseCCurrent;
	};

	struct WavesculptorVVectorMeasurement {
		float VqImaginary;
		float VdReal;
	};

	struct WavesculptorIVectorMeasurement {
		float IqImaginary;
		float IdReal;
	};

	struct WavesculptorMotorBackEMF {
		float BEMFd;
		float BEMFq;
	};

	struct Wavesculptor15VRail {
		uint32_t unused;
		float supplyVoltage15V;
	};

	struct Wavesculptor3V3_1V9VRail {
		float supplyVoltage1V9;
		float supplyVoltage3V3;
	};

	struct WavesculptorTemp {
		uint32_t motorTemp;
		uint32_t heatSinkTemp;
	};

	struct WavesculptorDSPBoardTemp {
		uint32_t DSPBoardTemp;
		uint32_t unused;
	};

	struct WavesculptorOdometer_BusAmpHours  {
		float odometer;
		float DCBusAmpHours;
	};

	struct WavesculptorSlipSpeed {
		uint32_t unused;
		float slipspeed;
	};

	/*
	 * * * * * * * * * * * *
	 *  MOTOR DRIVE WAVE   *
	 * * * * * * * * * * * *
	 */

	struct MotorDriveControls{
		float RPM;
		float motorCurrent;
	};

	struct MotorPower{
		uint32_t reserved;
		float busCurrent;
	};

	struct resetWavesculptor {
		uint32_t r1;
		uint32_t r2;
	};

	struct activeMotorChange{
		uint32_t accessKey1 = 0x544F4D54;
		uint16_t accessKey2 = 0x4341;
		uint16_t activeMotor = 0;
	};

	/*
	 * * * * * * * * * * * *
	 *  DATALOGGER DATA    *
	 * * * * * * * * * * * *
	 */

	enum DataloggerWarnings : uint8_t {
		dataloggerWarning_none = 0,
		dataloggerWarning_resetCAN,
		dataLoggerWarning_noCard,
		dataLoggerWarning_brownOut,
		dataloggerWarning_timeDrift,
		dataloggerWarning_lowRTCBattery,
	};

	enum DataloggerErrors : uint8_t {
		dataloggerError_none = 0,
		dataloggerError_watchdogReset,
		dataloggerError_rtcBadTime,
		dataLoggerError_badCard,
		dataLoggerError_unsafeDismount,
		dataLoggerError_fullCANBufferRx,
		dataLoggerError_fullCANBufferTx,
	};

	struct DataloggerVoltageStats {
		uint16_t busVAvg;
		uint16_t capVAvg;
	};

	enum DataloggerState : uint8_t {
		dataloggerState_inactive = 0,
		dataloggerState_active,
		dataloggerState_badCard,
		dataloggerState_shutdown,
		dataloggerState_userDismount,
	};


	struct DateTime {
		uint8_t year; //1900 + year = current year
		uint8_t month; // 0=Jan ... 11 = Dec
		uint8_t day; //day of month (1..31)
		uint8_t weekday; //days since sunday
		uint8_t hour; //hour of day (24hr 0..23)
		uint8_t minute; //minute (0..59)
		uint8_t second; //second (0..59)
	};

	struct MPPTPower {
		int32_t Voltage;
		int32_t Current;
	};
} // end namespace CAN

#endif /* BRIZO_CAN_DATA_H */
