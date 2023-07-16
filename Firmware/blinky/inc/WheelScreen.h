/*
 * WheelScreen.h
 *
 *  Created on: May 24, 2021
 *      Author: Daniel Wong
 */

#ifndef WHEEL_WHEELSCREEN_H_
#define WHEEL_WHEELSCREEN_H_

#include "US2066.h"
#include "CAN/can_data.h"
#include "CAN/can_id.h"
#include "MovingAverage.h"

class WheelScreen {
public:
	enum display {
		primary = 0,
		powerStatus = 1,
		boardStatus = 2
	};

	/*
	 * Create the WheelScreen object to update/handle the OLED display
	 * @param _OLEDDriver - driver class for the OLED display
	 */
	WheelScreen(SPI & spi, DigitalOut & chip_select, DigitalOut & reset);

	/*
	 * Initialize the WheelScreen object, which also initializes the OLED driver
	 * @return - see US2066.h init(..) return values
	 */
	uint8_t init(uint8_t contrast = 127);

	// NOTE: Most of the below methods are there to update the appropriate chars in one of the display char arrays

	/*
	 * * * * * * * * * * * * * * * * * *
	 * Common Display Data/Functions   *
	 * * * * * * * * * * * * * * * * * *
	 */

	/*
	 * Set drive direction and brake status in the char arrays
	 * @param driveInfo - struct containing information about car's drive direction and brake status
	 */
	void setDriveInfo(BRIZO_CAN::DashBrakeAndDirection driveInfo);

	/*
	 * Write the display data array to screen
	 * @param time - time that this method was called (so we can verify the recency of data being displayed)
	 */
	void writeDisplay(uint32_t time);

	/*
	 * Set display
	 * 0 - _primary
	 * 1 - _powerStatus
	 * 2 - _boardStatus
	 *
	 */
	void setDisplay(display disp);

	/*
	 * * * * * * * * * * * * *
	 * Primary Display Data  *
	 * * * * * * * * * * * * *
	 */

	/*
	 * Set pack current
	 * NOTE: This updates the power usage from battery as wheel (P = IV)
	 * @param current - current IN 100ths OF AN AMPERE (so we can display decimal data)
	 * @param time - time that this method was called (so we can verify that data was recent later)
	 */
	void setPackCurrent(int16_t current, uint32_t time);

	/*
	 * Set current battery voltage
	 * @param voltage - pack full voltage in mV
	 * @param time - current time for timeout
	 */
	void setPackVoltage(uint32_t voltage, uint32_t time);

	/*
	 * Set high battery cell value
	 * @param value - value IN 100ths OF A VOLT (so we can display decimal data)
	 * @param time - time that this method was called (so we can verify that data was recent later)
	 */
	void setHighCellValue(uint16_t value, uint32_t time);

	/*
	 * Set low battery cell value
	 * @param value - value IN 100ths OF A VOLT (so we can display decimal data)
	 * @param time - time that this method was called (so we can verify that data was recent later)
	 */
	void setLowCellValue(uint16_t value, uint32_t time);

	/*
	 * Set highest temperature in battery
	 * @param temp - value IN 1000ths OF deg C (so we can display decimal data)
	 * @param time - time that this method was called (so we can verify that data was recent later)
	 */
	void setHighCellTemp(uint16_t temp, uint32_t time);

	/*
	 * Set wheel status based on whatever operation mode is set in common class
	 */
	void setWheelStatus();

	/*
	 * Set cruise control speed (0 if car is not in cruise control mode)
	 */
	void setCCSpeed(uint16_t speed);

	/*
	 * Set acceleration percentage (from encoder)
	 */
	void setAccelPercentage(uint8_t accelPercent);

	/*
	 * Set headlight status
	 * @param on - whether headlights are on or not
	 */
	void setHeadLightStatus(bool on);

	/*
	 * Set regen status
	 */
	void setRegenStatus(bool on);

	/*
	 * * * * * * * * * * * * * * * *
	 * Power Status Display Data   *
	 * * * * * * * * * * * * * * * *
	 */

	/*
	 * Set total MPPT power
	 */
	void setTotalMPPT();
	/*
	 * Set left array MPPT power status
	 */
	void setMPPT1Power(int16_t power);

	/*
	 * Set left array MPPT power status
	 */
	void setMPPT2Power(int16_t power);

	/*
	 * Set back array MPPT power status
	 */
	void setMPPT4Power(int16_t power);

	/*
	 * * * * * * * * * * * * * * * *
	 * Board Status Display Data   *
	 * * * * * * * * * * * * * * * *
	 */

	/*
	 * Set PDS board status
	 */
	void setPDSStatus(BRIZO_CAN::PdsState pdsState);

	/*
	 * Set BMS board status
	 */
	void setBMSStatus(BRIZO_CAN::operationMode mode);

	/*
	 * Set MCC board status
	 */
	void setMCCStatus(uint8_t statusBits, uint32_t now);
	void setMotorPower(int16_t power);
	void WaveErrors(bool isError, uint32_t now);

	/*
	 * Set if clutch is active or not
	 */

	void setClutch(bool active);

	/*
	 * Set Chase board status
	 */
	void setChaseStatus(uint32_t now);

	/*
	 * * * * * * *
	 * Pop-ups   *
	 * * * * * * *
	 */

	/*
	 * Clear popup signal to make popup go away on next writeDisplay(...) call
	 */
	void clearPopup();

	/*
	 * Raise battery shutdown popup
	 */
	void batteryShutdownPopup(BRIZO_CAN::BatteryShutdown batteryShutdown);

	/*
	 * Raise wheel error popup
	 */
	void wheelErrorPopup(BRIZO_CAN::WheelErrors wheelError);

private:
	US2066 _driver;
	//store pack current in 1000ths of an amp
	int16_t _packCurrent;
	// _powerUsage stores battery power usage in 10ths of a watt
	int _powerUsage;

	bool _clutch = false;

	/*
	 * Set numerical display data in _displayData char array
	 * @param display - index specifying which of the 3 displays that the numerical data will be stored in
	 * @param row - index specifying which row the numerical data will be stored in
	 * @param columns[] - array of column indices that numerical data will be stored in
	 * 	NOTE: This array should be in increasing numerical order! Ex: {0, 1, 2, 3} NOT {3, 2, 1, 0}
	 * @param columnsSize - size of columns[] array
	 * @param data - actual numerical data which will be processed and put in _displayData char array
	 * 	EX: Inputting 1234 for the data argument will store the chars '1','2','3','4' in the appropriate slots in the _displayData char array
	 * @param showSign - true if we want to display '+' or '-' in front of numerical data
	 */
	void _setNumData(int display, int row, int columns[], int columnsSize, int data, bool showSign = false);

	/*
	 * Set character display data (will mainly be used for setting board statuses in the display
	 * @params display, row, columns[], columsSize - same as in _setNumData(...)
	 * @param data[] - character data to be put in display data array
	 * @param dataSize - size of data[] array
	 */
	void _setCharData(int display, int row, int columns[], int columnsSize, char data[], int dataSize);

	/*
	 * Set popup num data
	 * @params - see _setNumData
	 */
	void _setPopupNumData(int row, int columns[], int columnsSize, int data, bool showSign);

	/*
	 * Set popup display data and raise popup signal to display popup on next writeDisplay(...) call
	 * @params - see _setCharData(...) params
	 */
	void _setPopupData(int row, int columns[], int columnsSize, char data[], int dataSize);

	/*
	 * Check that each piece display data is recent. If a piece of display data is not recent, replace it with ? marks
	 * @param time - time that this method was called (so we can verify the recency of other data)
	 */
	void _recentDataCheck(uint32_t time);

	/*
	 * Helper method for _recentDataCheck
	 * @param lastTime - last time data was updated
	 * @param time - current time
	 * @param timeLimit - maximum acceptable difference between last updated time and current time
	 * @param unitSize - alphabetical length of unit on screen (ex. "W" would be 1, "mph" would be 3)
	 * rest of params - see _setNumData params
	 */
	void _recentDataCheckHelper(uint32_t lastTime, uint32_t time, uint32_t timeLimit, int display, int row, int columns[],
			int unitSize);

	/*
	 * Set up next popup, if there is one
	 */
	void _setUpPopup();

	/*
	 * Set popup to display battery shutdown popup
	 */
	void _setBatteryShutdownPopup(BRIZO_CAN::BatteryShutdown batteryShutdown);

	/*
	 * Set popup to display battery shutdown popup
	 */
	void _setWheelErrorPopup(BRIZO_CAN::WheelErrors wheelError);

	display _currDisplay = primary;

	int _driveCtrlIndicatorColumn = 19;
	enum _driveCtrlRow {
		_forwardRow = 0,
		_neutralRow = 1,
		_reverseRow = 2,
		_brakeRow = 3
	};
	uint8_t _forwardSymbol = 0xDE;
	uint8_t _cruiseSymbol = 'C';
	uint8_t _regenSymbol = 'R';
	uint8_t _neutralSymbol = 0x6F;
	uint8_t _reverseSymbol = 0xE0;
	uint8_t _brakeSymbol = 0x21;

	display _battCurrentDisplay = primary;
	int _battCurrentRow = 0;
	int _battCurrentColumns[5] = {0, 1, 2, 4, 5};
	uint32_t _lastBattCurrentTime;
	uint32_t _battCurrentTimeLim = BRIZO_CAN::BMS_PACK_CURRENT.RATE * 5;

	display _battPowerDisplay = primary;
	int _battPowerRow = 0;
	int _battPowerColumns[5] = {8, 9, 10, 11, 12};
	MovingAverage<int32_t, int64_t, 10> _PowerMovingAvg;
	uint32_t _lastBattVoltageTime;
	uint32_t _battVoltageTimeLim = BRIZO_CAN::BMS_PACK_VOLTAGE.RATE * 5;

	display _highCellValDisplay = primary;
	int _highCellValRow = 1;
	int _highCellValColumns[4] = {0, 2, 3, 4};
	uint32_t _lastHighCellValTime;
	uint32_t _highCellValTimeLim = BRIZO_CAN::BMS_VOLTAGES.RATE * 5;

	display _lowCellValDisplay = primary;
	int _lowCellValRow = 1;
	int _lowCellValColumns[4] = {8, 10, 11, 12};
	uint32_t _lastLowCellValTime;
	uint32_t _lowCellValTimeLim = BRIZO_CAN::BMS_VOLTAGES.RATE * 5;

	display _highCellTempDisplay = primary;
	int _highCellTempRow = 2;
	int _highCellTempColumns[4] = {0, 1, 2, 4};
	uint32_t _lastHighCellTempTime;
	uint32_t _highCellTempTimeLim = BRIZO_CAN::BMS_PACK_TEMPS.RATE * 5;

	display _CCSpeedDisplay = primary;
	int _CCSpeedRow = 3;
	int _CCSpeedColumns[3] = {2,3,4};

	display _accelPercentDisplay = primary;
	int _accelPercentRow = 3;
	int _accelPercentColumns[4] = {10, 11, 12, 13};

	display _headlightStatusDisplay = primary;
	int _headlightStatusRow = 2;
	int _headlightStatusColumns[1] = {18};


	display _netPowerDisplay = powerStatus;
	int _netPowerRow = 0;
	int _netPowerColumns[5] = {4, 5, 6, 7, 8};

	display _motorPowerDisplay = powerStatus;
	int _motorPowerRow = 1;
	int _motorPowerColumns[5] = {4, 5, 6, 7, 8};

	display _totalMPPTDisplay = powerStatus;
	int _totalMPPTRow = 2;
	int _totalMPPTColumns[5] = {4, 5, 6, 7, 8};

	//mppts getting switched around. //1 = left 2 = right 4 = back
	int16_t _mppt1Power = 0;
	int16_t _mppt2Power = 0;
	int16_t _mppt4Power = 0;
	display _leftMPPTDisplay = powerStatus;
	int _leftMPPTRow = 0;
	int _leftMPPTColumns[4] = {12, 13, 14, 15};

	display _rightMPPTDisplay = powerStatus;
	int _rightMPPTRow = 1;
	int _rightMPPTColumns[4] = {12, 13, 14, 15};

	display _backMPPTDisplay = powerStatus;
	int _backMPPTRow = 2;
	int _backMPPTColumns[4] = {12, 13, 14, 15};

	display _wheelStatusDisplay = primary;
	int _wheelRow = 2;
	int _wheelColumns[10] = {8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
	char _operationModeStartUp[8] = {'S','t','a','r','t',' ','U','p'};
	char _operationModeNormal[8] = {'N','o','r','m','a','l',' ',' '};
	char _operationModeNormalAuxPower[8] = {'N','o','r','m', ' ', 'A', 'u', 'x'};
	char _operationModeNormalRoad[9] = {'N','o','r','m', ' ', 'R', 'o', 'a', 'd'};
	char _operationModeNormalTrack[10] = {'N','o','r','m', ' ', 'T', 'r', 'a', 'c', 'k'};
	char _operationModeNormalScrutineering[10] = {'N','o','r','m', ' ', 'S', 'c', 'r', 'u', 't'};
	char _operationModeDischargeOnly[9] = {'D','i','s','c', 'h', 'a', 'r', 'g', 'e'};
	char _operationModeChargingMode[8] = {'C','h','a','r', 'g', 'i', 'n', 'g'};
	char _operationModeShutdown[8] = {'S','h','u','t', 'd', 'o', 'w', 'n'};

	display _PDSDisplay = boardStatus;
	int _PDSRow = 0;
	int _PDSColumns[13] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
	char _PDSOff[3] = {'O', 'f', 'f'};
	char _PDSCharging[8] = {'C', 'h', 'a', 'r', 'g', 'i', 'n', 'g'};
	char _PDSPrecharge[9] = {'P', 'r', 'e', 'c', 'h', 'a', 'r', 'g', 'e'};
	char _PDSPrechargeSwap[10] = {'P', 'r', 'e', 'c', 'h', ' ', 'S', 'w', 'a', 'p'};
	char _PDSDischargeOnly[9] = {'D', 'i', 's', 'c', 'h', 'a', 'r', 'g', 'e'};
	char _PDSOperational[11] = {'O', 'p', 'e', 'r', 'a', 't', 'i', 'o', 'n', 'a', 'l'};

	display _BMSDisplay = boardStatus;
	int _BMSRow = 1;
	int _BMSColumns[13] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
	char _BMSStartup[8] = {'S', 't', 'a', 't', 't', 'U', 'p', ' '};
	char _BMSNormal[8] = {'N', 'o', 'r', 'm', 'a', 'l', ' ', ' '};
	char _BMSShutdown[8] = {'S', 'h', 'u', 't', 'd', 'o', 'w', 'n'};

	display _MCCDisplay = boardStatus;
	int _MCCRow = 2;
	bool _waveError = false;
	bool _isWave = false;
	bool _isCruise = false;
	bool _isForward = true;
	int _MCCColumns[10] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	char _MCCNoWave[7] = {'N', 'O', ' ', 'W','A','V','E'};
	char _MCCForward[7] = {'F','o','r','w','a','r','d'};
	char _MCCNeutral[7] = {'N','e','u','t','r','a','l'};
	char _MCCReverse[7] = {'R','e','v','e','r','s','e'};
	char _MCCCruise[7] = {'C','r','u','i','s','e','!'};
	char _MCCClutch[7] = {'C','l','u','t','c','h',' '};
	char _MCCWaveError[7] = {'W','S',' ','E','R','R',' '};
	uint32_t _lastWaveTime = 0;
	uint32_t _lastMCCTime = 0;
	uint32_t _lastWaveTimeout = BRIZO_CAN::MC_STATUS.RATE * 10;
	uint32_t _lastMCCTimeout = BRIZO_CAN::MCCR_HEART.RATE * 3;

	display _ChaseDisplay = boardStatus;
	uint32_t _lastChaseTime = 0;
	uint32_t _lastChaseTimeOut = BRIZO_CAN::CHASE_CAR_HEARTBEAT.RATE * 30;
	int _chaseRow = 3;
	int _chaseColumns[9] = {7, 8, 9, 10, 11, 12, 13, 14, 17};
	char _chaseConn[9] = {'C', 'o', 'n', 'n', 'e', 'c', 't', 'e', 'd' };

	// 3 displays x 4 rows x 20 columns
	char _displayData[3][4][20] = {{{' ',' ',' ','.',' ', ' ', 'A', ' ', ' ', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' '},
									{' ','.',' ',' ',' ', 'H', ' ', ' ', ' ', '.', ' ', ' ', ' ', 'L', ' ', ' ', ' ', ' ', ' ', ' '},
									{' ',' ',' ','.',' ', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
									{'T',':',' ',' ',' ', 'm', 'p', 'h', ' ', ' ', ' ', ' ', ' ', ' ', '%', ' ', ' ', ' ', ' ', ' '}},

									{{'N','E','T',':',' ', ' ', ' ', ' ', ' ', 'W', ' ', '1', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' '},
									{'M','T','R',':',' ', ' ', ' ', ' ', ' ', 'W', ' ', '2', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' '},
									{'A','R','R',':',' ', ' ', ' ', ' ', ' ', 'W', ' ', '4', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' '},
									{' ',' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}},

									{{'P','D','S',':',' ', '-', '-', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'F'},
									{'B','M','S',':',' ', '-', '-', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'N'},
									{'M','C','C',':',' ', '-', '-', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'R'},
									{'C','h','a','s','e', ':', ' ', '-', '-', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'B'}}};
	bool _writeCheck[4] = {1, 1, 1, 1};

	enum _popupType : uint8_t {
		_noPopup,
		_wheelError,
		_batteryShutdown
	};

	// Use these to keep track of pop ups
	const int _numPopups = 10;
	_popupType _popupQueue[10] = {_noPopup, _noPopup, _noPopup, _noPopup, _noPopup,
			_noPopup, _noPopup, _noPopup, _noPopup, _noPopup};
	int _currPopup = 0;
	int _nextAvailPopup = 0;
	bool _popupAvail = true;
	bool _popupCleared = true;
	bool _newPopup = false;
	int batteryShutdownCalls = 0;
	int clearCalls = 0;
	BRIZO_CAN::BatteryShutdown _lastBatteryShutdown = BRIZO_CAN::BATTERY_NUM_SHUTDOWNS;

	BRIZO_CAN::BatteryShutdown _batteryShutdownQueue[10];
	int _currBatteryShutdown = 0;
	int _nextAvailBatteryShutdown = 0;
	bool _batteryShutdownAvail = true;

	int _batteryShutdownMessageRow = 0;
	int _batteryShutdownReasonRow = 1;
	int _batteryShutdownColumns[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	char _batteryShutdownMessage[20] = {' ', ' ', 'B', 'A', 'T', 'T', 'E', 'R', 'Y', ' ', 'S', 'H', 'U', 'T', 'D', 'O', 'W', 'N', ' ', ' '};
	char _batteryShutdownOff[20] = {' ', ' ', ' ', ' ', 'B','A','T','T','E', 'R', 'Y', ' ', 'O', 'F', 'F', ' ', ' ', ' ', ' ', ' '};
	char _batteryShutdownUnderVolt[20] = {' ', 'C', 'E', 'L', 'L', ' ', 'U', 'N', 'D', 'E', 'R', 'V', 'O', 'L', 'T', 'A', 'G', 'E', ' ', ' '};
	char _batteryShutdownOverVolt[20] = {' ', ' ', 'C', 'E', 'L', 'L', ' ', 'O', 'V', 'E', 'R', 'V', 'O', 'L', 'T', 'A', 'G', 'E', ' ', ' '};
	char _batteryShutdownCurrDischarge[20] = {'O', 'V', 'E', 'R', ' ', 'C', 'U', 'R', 'R', ' ', 'D', 'I', 'S', 'C', 'H', 'A', 'R', 'G', 'E', ' '};
	char _batteryShutdownCurrCharge[20] = {' ', ' ', 'O', 'V', 'E', 'R', ' ', 'C', 'U', 'R', 'R', ' ', 'C', 'H', 'A', 'R', 'G', 'E', ' ', ' '};
	char _batteryShutdownTempDischarge[20] = {'O', 'V', 'E', 'R', ' ', 'T', 'E', 'M', 'P', ' ', 'D', 'I', 'S', 'C', 'H', 'A', 'R', 'G', 'E', ' '};
	char _batteryShutdownTempCharge[20] = {' ', ' ', 'O', 'V', 'E', 'R', ' ', 'T', 'E', 'M', 'P', ' ', 'C', 'H', 'A', 'R', 'G', 'E', ' ', ' '};
	char _batteryShutdownAuxPack[20] = {' ', ' ', 'A', 'U', 'X', ' ', 'P', 'A', 'C', 'K', ' ', 'P', 'O', 'W', 'E', 'R', 'E', 'D', ' ', ' '};
	char _batteryShutdownLTC6811[20] = {'L', 'T', 'C', '6', '8', '1', '1', ' ', 'U', 'N', 'R', 'E', 'A', 'C', 'H', 'A', 'B', 'L', 'E', ' '};
	char _batteryShutdownCurrADC[20] = {'C', 'U', 'R', 'R', ' ', 'A', 'D', 'C', ' ', 'U', 'N', 'R', 'E', 'A', 'C', 'H', 'A', 'B', 'L', 'E'};
	char _batteryShutdownEmergencyStop[20] = {' ', ' ', ' ', 'E', 'M', 'E', 'R', 'G', 'E', 'N', 'C', 'Y', ' ', 'S', 'T', 'O', 'P', ' ', ' ', ' '};

	BRIZO_CAN::WheelErrors _wheelErrorQueue[10];
	int _currWheelError = 0;
	int _nextAvailWheelError = 0;
	bool _wheelErrorAvail = true;

	int _wheelErrorMessageRow = 0;
	int _wheelErrorReasonRow = 1;
	int _wheelErrorColumns[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	char _wheelErrorMessage[20] = {' ', ' ', ' ', ' ', ' ', 'W', 'H', 'E', 'E', 'L', ' ', 'E', 'R', 'R', 'O', 'R', ' ', ' ', ' ', ' '};
	char _wheelErrorWatchDogReset[20] = {' ', ' ', ' ', 'W', 'A', 'T', 'C', 'H', ' ', 'D', 'O', 'G', ' ', 'R', 'E', 'S', 'E', 'T', ' ', ' '};
	char _wheelErrorStartCapPower[20] = {' ', 'S', 'T', 'A', 'R', 'T', ' ', 'O', 'N', ' ', 'C', 'A', 'P', ' ', 'P', 'O', 'W', 'E', 'R', ' '};
	char _wheelErrorSuperCapPower[20] = {' ', ' ', ' ', 'S', 'U', 'P', 'E', 'R', ' ', 'C', 'A', 'P', ' ', 'P', 'O', 'W', 'E', 'R', ' ', ' '};
	char _wheelError7SegOverTemp[20] = {' ', ' ', ' ', '7', '-', 'S', 'E', 'G', ' ', 'O', 'V', 'E', 'R', ' ', 'T', 'E', 'M', 'P', ' ', ' '};
	char _wheelError7SegOutput[20] = {' ', ' ', ' ', ' ', '7', '-', 'S', 'E', 'G', ' ', 'O', 'U', 'T', 'P', 'U', 'T', ' ', ' ', ' ', ' '};
	char _wheelError7SegSetup[20] = {' ', ' ', ' ', ' ', ' ', '7', '-', 'S', 'E', 'G', ' ', 'S', 'E', 'T', 'U', 'P', ' ', ' ', ' ', ' '};
	char _wheelErrorOledSetup[20] = {' ', ' ', ' ', ' ', ' ', 'O', 'L', 'E', 'D', ' ', 'S', 'E', 'T', 'U', 'P', ' ', ' ', ' ', ' ', ' '};
	char _wheelErrorEncoderTimeout[20] = {' ', ' ', ' ', 'E', 'N', 'C', 'O', 'D', 'E', 'R', ' ', 'T', 'I', 'M', 'E', 'O', 'U', 'T', ' ', ' '};

	int _numMessagesRow = 3;
	int _numMessagesColumns[2] = {0, 1};

	char _popupData[4][20] = {{' ',' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
							{' ',' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
							{' ',' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
							{' ',' ',' ','M','S', 'G', 'S', ' ', 'L', 'E', 'F', 'T', ':', ' ', 'H', 'I', 'T', ' ', 'O', 'K'}};

};

#endif /* WHEEL_WHEELSCREEN_H_ */
