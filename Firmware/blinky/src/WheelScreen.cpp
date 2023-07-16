/*
 * WheelScreen.cpp
 *
 *  Created on: May 24, 2021
 *      Author: Daniel Wong
 */

#include <WheelScreen.h>
#include "peripherals.h"

WheelScreen::WheelScreen(SPI & spi, DigitalOut & chip_select, DigitalOut & reset)
: _driver(spi, chip_select, reset)
{
}

uint8_t WheelScreen::init(uint8_t contrast) {
	return _driver.init(contrast);
}


void WheelScreen::setDriveInfo(BRIZO_CAN::DashBrakeAndDirection driveInfo) {
	// Clear all drive control indicators
	for (int display = 0; display < sizeof(_displayData)/sizeof(_displayData[0]); display++) {
		for (int row = 0; row < sizeof(_displayData[0])/sizeof(_displayData[0][0]); row++) {
			_displayData[display][row][_driveCtrlIndicatorColumn] = ' ';
		}
	}

	// Set drive control indicator on wheel
	_driveCtrlRow driveDirRow = _forwardRow;

	switch (driveInfo.drive_dir) {
	case BRIZO_CAN::dashDriveDirection_forward:
		driveDirRow = _forwardRow;
		break;
	case BRIZO_CAN::dashDriveDirection_neutral:
		driveDirRow = _neutralRow;
		break;
	case BRIZO_CAN::dashDriveDirection_reverse:
		driveDirRow = _reverseRow;
		break;
	}
//	uint8_t driveSymbol = (driveDirRow == _forwardRow) ? _forwardSymbol : (driveDirRow == _neutralRow) ? _neutralSymbol : _reverseSymbol;
//	if (driveSymbol == _forwardSymbol && driveControls.getCruise()) {
//		driveSymbol = _cruiseSymbol;
//	}
//	if (driveSymbol == _forwardSymbol && driveControls.getRegen()) {
//		driveSymbol = _regenSymbol;
//	}
//
//	for (int display = 0; display < sizeof(_displayData)/sizeof(_displayData[0]); display++) {
//		_displayData[display][driveDirRow][_driveCtrlIndicatorColumn] = driveSymbol;
//	}

	// Set brake indicator on wheel
	if (driveInfo.mechBrakePressed) {
		for (int display = 0; display < sizeof(_displayData)/sizeof(_displayData[0]); display++) {
			_displayData[display][_brakeRow][_driveCtrlIndicatorColumn] = _brakeSymbol;
		}
	}

	if (_clutch){
		for (int display = 0; display < sizeof(_displayData)/sizeof(_displayData[0]); display++) {
			_displayData[display][_neutralRow][_driveCtrlIndicatorColumn] = 67;
		}
	}
}

void WheelScreen::writeDisplay(uint32_t time) {
	this->_recentDataCheck(time);

	if (_popupQueue[_currPopup] == _noPopup) {
		if (_currDisplay == primary) {
			this->setWheelStatus();
//			this->setCCSpeed(driveControls.getTargetSpeed());
		}
		for (int i = 0; i < 4; i++) {
			if (_writeCheck[i]) {
				_driver.write(i, _displayData[_currDisplay][i]);
				_writeCheck[i] = 0;
			}
		}
	} else if (_popupCleared || _newPopup) {
		this->_setUpPopup();
		_driver.write(_popupData[0], _popupData[1], _popupData[2], _popupData[3]);
		_popupCleared = false;
	}
}

void WheelScreen::setDisplay(display disp) {
	_currDisplay = disp;
	for (int i = 0; i < 4; i++) {
		_writeCheck[i] = 1;
	}
}

void WheelScreen::setPackCurrent(int16_t current, uint32_t time) {
	_packCurrent = current;
	_lastBattCurrentTime = time;
	_setNumData(_battCurrentDisplay, _battCurrentRow, _battCurrentColumns,
		sizeof(_battCurrentColumns)/sizeof(_battCurrentColumns[0]), _packCurrent, true);
}

void WheelScreen::setPackVoltage(uint32_t voltage, uint32_t time) {
	_lastBattVoltageTime = time;
	int64_t power = ((int64_t)voltage * (int64_t)_packCurrent);
	_PowerMovingAvg.update(power / 1000000);
	_setNumData(_battPowerDisplay, _battPowerRow, _battPowerColumns,
		sizeof(_battPowerColumns)/sizeof(_battPowerColumns[0]), _PowerMovingAvg.read(), true);
	_setNumData(_netPowerDisplay, _netPowerRow, _netPowerColumns,
			sizeof(_netPowerColumns)/sizeof(_netPowerColumns[0]), _PowerMovingAvg.read(), true);
}

void WheelScreen::setHighCellValue(uint16_t value, uint32_t time) {
	_lastHighCellValTime = time;
	_setNumData(_highCellValDisplay, _highCellValRow, _highCellValColumns,
		sizeof(_highCellValColumns)/sizeof(_highCellValColumns[0]), (int)value);
}

void WheelScreen::setLowCellValue(uint16_t value, uint32_t time) {
	_lastLowCellValTime = time;
	_setNumData(_lowCellValDisplay, _lowCellValRow, _lowCellValColumns,
		sizeof(_lowCellValColumns)/sizeof(_lowCellValColumns[0]), (int)value);
}

void WheelScreen::setHighCellTemp(uint16_t temp, uint32_t time) {
	_lastHighCellTempTime = time;
	_setNumData(_highCellTempDisplay, _highCellTempRow, _highCellTempColumns,
		sizeof(_highCellTempColumns)/sizeof(_highCellTempColumns[0]), (int)temp/10);
}

void WheelScreen::setWheelStatus() {
	BRIZO_CAN::operationMode wheelStatus = common.GetOperationMode();
	switch (wheelStatus) {
	case BRIZO_CAN::operationMode_startUp:
		_setCharData(_wheelStatusDisplay, _wheelRow, _wheelColumns, sizeof(_wheelColumns)/sizeof(_wheelColumns[0]),
			_operationModeStartUp, sizeof(_operationModeStartUp)/sizeof(_operationModeStartUp[0]));
		break;
	case BRIZO_CAN::operationMode_normal:
		_setCharData(_wheelStatusDisplay, _wheelRow, _wheelColumns, sizeof(_wheelColumns)/sizeof(_wheelColumns[0]),
			_operationModeNormal, sizeof(_operationModeNormal)/sizeof(_operationModeNormal[0]));
		break;
	case BRIZO_CAN::operationMode_normalAuxPower:
		_setCharData(_wheelStatusDisplay, _wheelRow, _wheelColumns, sizeof(_wheelColumns)/sizeof(_wheelColumns[0]),
			_operationModeNormalAuxPower, sizeof(_operationModeNormalAuxPower)/sizeof(_operationModeNormalAuxPower[0]));
		break;
	case BRIZO_CAN::operationMode_normalRoad:
		_setCharData(_wheelStatusDisplay, _wheelRow, _wheelColumns, sizeof(_wheelColumns)/sizeof(_wheelColumns[0]),
			_operationModeNormalRoad, sizeof(_operationModeNormalRoad)/sizeof(_operationModeNormalRoad[0]));
		break;
	case BRIZO_CAN::operationMode_normalTrack:
		_setCharData(_wheelStatusDisplay, _wheelRow, _wheelColumns, sizeof(_wheelColumns)/sizeof(_wheelColumns[0]),
			_operationModeNormalTrack, sizeof(_operationModeNormalTrack)/sizeof(_operationModeNormalTrack[0]));
		break;
	case BRIZO_CAN::operationMode_normalScrutineering:
		_setCharData(_wheelStatusDisplay, _wheelRow, _wheelColumns, sizeof(_wheelColumns)/sizeof(_wheelColumns[0]),
			_operationModeNormalScrutineering, sizeof(_operationModeNormalScrutineering)/sizeof(_operationModeNormalScrutineering[0]));
		break;
	case BRIZO_CAN::operationMode_dischargeOnly:
		_setCharData(_wheelStatusDisplay, _wheelRow, _wheelColumns, sizeof(_wheelColumns)/sizeof(_wheelColumns[0]),
			_operationModeDischargeOnly, sizeof(_operationModeDischargeOnly)/sizeof(_operationModeDischargeOnly[0]));
		break;
	case BRIZO_CAN::operationMode_chargingMode:
		_setCharData(_wheelStatusDisplay, _wheelRow, _wheelColumns, sizeof(_wheelColumns)/sizeof(_wheelColumns[0]),
			_operationModeChargingMode, sizeof(_operationModeChargingMode)/sizeof(_operationModeChargingMode[0]));
		break;
	case BRIZO_CAN::operationMode_shutdown:
		_setCharData(_wheelStatusDisplay, _wheelRow, _wheelColumns, sizeof(_wheelColumns)/sizeof(_wheelColumns[0]),
				_operationModeShutdown, sizeof(_operationModeShutdown)/sizeof(_operationModeShutdown[0]));
		break;
	}
}

void WheelScreen::setCCSpeed(uint16_t speed) {
	_setNumData(_CCSpeedDisplay, _CCSpeedRow, _CCSpeedColumns, sizeof(_CCSpeedColumns)/sizeof(_CCSpeedColumns[0]), (int)speed);
}

void WheelScreen::setAccelPercentage(uint8_t accelPercent) {
	_setNumData(_accelPercentDisplay, _accelPercentRow, _accelPercentColumns,
			sizeof(_accelPercentColumns)/sizeof(_accelPercentColumns[0]), accelPercent, true);
}

void WheelScreen::setHeadLightStatus(bool on) {
	char status[1];
	status[0] = on ? 0xBB : ' ';
	_setCharData(_headlightStatusDisplay, _headlightStatusRow, _headlightStatusColumns, sizeof(_headlightStatusColumns)/sizeof(_headlightStatusColumns[0]),
					status, sizeof(status)/sizeof(status[0]));
}

void WheelScreen::setRegenStatus(bool on) {
	char status[1];
	status[0] = on ? 'R' : ' ';
	int cols[1] = {18};
	_setCharData(primary, 0, cols, sizeof(cols)/sizeof(cols[0]), status, sizeof(status)/sizeof(status[0]));
}



void WheelScreen::setTotalMPPT()
{
	int16_t totalPower = _mppt1Power + _mppt2Power + _mppt4Power;
	_setNumData(_totalMPPTDisplay, _totalMPPTRow, _totalMPPTColumns,
				sizeof(_totalMPPTColumns)/sizeof(_totalMPPTColumns[0]), totalPower, true);
}

void WheelScreen::setMPPT1Power(int16_t power) {
	//TODO: Finish this method once CAN message is defined
	_mppt1Power = power;
	_setNumData(_leftMPPTDisplay, _leftMPPTRow, _leftMPPTColumns,
				sizeof(_leftMPPTColumns)/sizeof(_leftMPPTColumns[0]), _mppt1Power, true);
	this->setTotalMPPT();
}

void WheelScreen::setMPPT2Power(int16_t power) {
	//TODO: Finish this method once CAN message is defined
	_mppt2Power = power;
	_setNumData(_rightMPPTDisplay, _rightMPPTRow, _rightMPPTColumns,
				sizeof(_rightMPPTColumns)/sizeof(_rightMPPTColumns[0]), _mppt2Power, true);
	this->setTotalMPPT();
}

void WheelScreen::setMPPT4Power(int16_t power) {
	//TODO: Finish this method once CAN message is defined
	_mppt4Power = power;
	_setNumData(_backMPPTDisplay, _backMPPTRow, _backMPPTColumns,
				sizeof(_backMPPTColumns)/sizeof(_backMPPTColumns[0]), _mppt4Power, true);
	this->setTotalMPPT();
}

void WheelScreen::setPDSStatus(BRIZO_CAN::PdsState pdsState) {
	switch (pdsState) {
	case (BRIZO_CAN::pdsState_StartOff):
		_setCharData(_PDSDisplay, _PDSRow, _PDSColumns, sizeof(_PDSColumns)/sizeof(_PDSColumns[0]),
				_PDSOff, sizeof(_PDSOff)/sizeof(_PDSOff[0]));
		break;
	case (BRIZO_CAN::pdsState_Charging):
		_setCharData(_PDSDisplay, _PDSRow, _PDSColumns, sizeof(_PDSColumns)/sizeof(_PDSColumns[0]),
				_PDSCharging, sizeof(_PDSCharging)/sizeof(_PDSCharging[0]));
		break;
	case (BRIZO_CAN::pdsState_Precharge):
		_setCharData(_PDSDisplay, _PDSRow, _PDSColumns, sizeof(_PDSColumns)/sizeof(_PDSColumns[0]),
				_PDSPrecharge, sizeof(_PDSPrecharge)/sizeof(_PDSPrecharge[0]));
		break;
	case (BRIZO_CAN::pdsState_PrechargeSwap):
		_setCharData(_PDSDisplay, _PDSRow, _PDSColumns, sizeof(_PDSColumns)/sizeof(_PDSColumns[0]),
				_PDSPrechargeSwap, sizeof(_PDSPrechargeSwap)/sizeof(_PDSPrechargeSwap[0]));
		break;
	case (BRIZO_CAN::pdsState_DischargeOnly):
		_setCharData(_PDSDisplay, _PDSRow, _PDSColumns, sizeof(_PDSColumns)/sizeof(_PDSColumns[0]),
				_PDSDischargeOnly, sizeof(_PDSDischargeOnly)/sizeof(_PDSDischargeOnly[0]));
		break;
	case (BRIZO_CAN::pdsState_Operational):
		_setCharData(_PDSDisplay, _PDSRow, _PDSColumns, sizeof(_PDSColumns)/sizeof(_PDSColumns[0]),
				_PDSOperational, sizeof(_PDSOperational)/sizeof(_PDSOperational[0]));
		break;
	}
}

void WheelScreen::setBMSStatus(BRIZO_CAN::operationMode mode) {
	if(mode == BRIZO_CAN::operationMode_shutdown){
		_setCharData(_BMSDisplay, _BMSRow, _BMSColumns, sizeof(_BMSColumns)/sizeof(_BMSColumns[0]),
				_BMSShutdown, sizeof(_BMSShutdown)/sizeof(_BMSShutdown[0]));
	}else if(mode >= BRIZO_CAN::operationMode_normal){
		_setCharData(_BMSDisplay, _BMSRow, _BMSColumns, sizeof(_BMSColumns)/sizeof(_BMSColumns[0]),
				_BMSNormal, sizeof(_BMSNormal)/sizeof(_BMSNormal
						[0]));
	}else{
		_setCharData(_BMSDisplay, _BMSRow, _BMSColumns, sizeof(_BMSColumns)/sizeof(_BMSColumns[0]),
				_BMSStartup, sizeof(_BMSStartup)/sizeof(_BMSStartup[0]));
	}
}


void WheelScreen::setClutch(bool active){
	_clutch = active;
}

/* Motor Info */
void WheelScreen::WaveErrors(bool isError, uint32_t now){
	_waveError = isError;
	_lastWaveTime = now;
}

void WheelScreen::setMotorPower(int16_t power) {
	_setNumData(_motorPowerDisplay, _motorPowerRow, _motorPowerColumns,
					sizeof(_motorPowerColumns)/sizeof(_motorPowerColumns[0]), power, true);

}

void WheelScreen::setMCCStatus(uint8_t statusBits, uint32_t now) {
	//check if is wavesculptor:
	_isWave = statusBits & (1 << BRIZO_CAN::MmmMCStatusBits::mccMCStatusBits_isWaveSculptor);

	//check if cruising
	_isCruise = statusBits & (1 << BRIZO_CAN::MmmMCStatusBits::mccMCStatusBits_cruiseActive);

	//check direction
	_isForward = statusBits & (1 << BRIZO_CAN::MmmMCStatusBits::mccMCStatusBits_driveDir);

	if(_clutch){
		_setCharData(_MCCDisplay, _MCCRow, _MCCColumns, sizeof(_MCCColumns)/sizeof(_MCCColumns[0]),
				_MCCClutch, sizeof(_MCCClutch)/sizeof(_MCCClutch[0]));
	}else if(_isWave && timing.threshold(_lastWaveTime, now, _lastWaveTimeout)){
		_setCharData(_MCCDisplay, _MCCRow, _MCCColumns, sizeof(_MCCColumns)/sizeof(_MCCColumns[0]),
				_MCCNoWave, sizeof(_MCCNoWave)/sizeof(_MCCNoWave[0]));
	}else if(_isWave && _waveError){
		_setCharData(_MCCDisplay, _MCCRow, _MCCColumns, sizeof(_MCCColumns)/sizeof(_MCCColumns[0]),
				_MCCWaveError, sizeof(_MCCWaveError)/sizeof(_MCCWaveError[0]));
	}else if(_isCruise){
		_setCharData(_MCCDisplay, _MCCRow, _MCCColumns, sizeof(_MCCColumns)/sizeof(_MCCColumns[0]),
				_MCCCruise, sizeof(_MCCCruise)/sizeof(_MCCCruise[0]));
	}else if(_isForward){
		_setCharData(_MCCDisplay, _MCCRow, _MCCColumns, sizeof(_MCCColumns)/sizeof(_MCCColumns[0]),
						_MCCForward, sizeof(_MCCForward)/sizeof(_MCCForward[0]));
	}else{
		_setCharData(_MCCDisplay, _MCCRow, _MCCColumns, sizeof(_MCCColumns)/sizeof(_MCCColumns[0]),
						_MCCReverse, sizeof(_MCCReverse)/sizeof(_MCCReverse[0]));
	}

}

void WheelScreen::setChaseStatus(uint32_t now) {
	_lastChaseTime = now;
	_setCharData(_ChaseDisplay, _chaseRow, _chaseColumns, sizeof(_chaseColumns)/sizeof(_chaseColumns[0]),
			_chaseConn, sizeof(_chaseConn)/sizeof(_chaseConn[0]));
}

void WheelScreen::clearPopup() {
	_popupType popupType = _popupQueue[_currPopup];
	switch (popupType) {
	case _noPopup:
		break;
	case _wheelError:
		_currWheelError = (_currWheelError + 1 < _numPopups) ? _currWheelError + 1 : 0;
		_wheelErrorAvail = true;
		break;
	case _batteryShutdown:
		_currBatteryShutdown = (_currBatteryShutdown + 1 < _numPopups) ? _currBatteryShutdown + 1 : 0;
		_batteryShutdownAvail = true;
		break;
	}
	_popupQueue[_currPopup] = _noPopup;
	_currPopup = (_currPopup + 1 < _numPopups) ? _currPopup + 1 : 0;
	_popupAvail = true;
	_popupCleared = true;
	clearCalls++;
}

void WheelScreen::batteryShutdownPopup(BRIZO_CAN::BatteryShutdown batteryShutdown) {
	if (_batteryShutdownAvail && _popupAvail && _lastBatteryShutdown != batteryShutdown) {
		_popupQueue[_nextAvailPopup] = _batteryShutdown;
		_batteryShutdownQueue[_nextAvailBatteryShutdown] = batteryShutdown;

		_nextAvailBatteryShutdown = (_nextAvailBatteryShutdown + 1 < _numPopups) ? _nextAvailBatteryShutdown + 1 : 0;
		_nextAvailPopup = (_nextAvailPopup + 1 < _numPopups) ? _nextAvailPopup + 1 : 0;

		if (_nextAvailBatteryShutdown == _currBatteryShutdown) {
			_batteryShutdownAvail = false;
		}
		if (_nextAvailPopup == _currPopup) {
			_popupAvail = false;
		}
		batteryShutdownCalls++;
		_newPopup = true;
		_lastBatteryShutdown = batteryShutdown;
	}
}

void WheelScreen::wheelErrorPopup(BRIZO_CAN::WheelErrors wheelError) {
	if (_wheelErrorAvail && _popupAvail) {
		_popupQueue[_nextAvailPopup] = _wheelError;
		_wheelErrorQueue[_nextAvailWheelError] = wheelError;

		_nextAvailWheelError = (_nextAvailWheelError + 1 < _numPopups) ? _nextAvailWheelError + 1 : 0;
		_nextAvailPopup = (_nextAvailPopup + 1 < _numPopups) ? _nextAvailPopup + 1 : 0;

		if (_nextAvailWheelError == _currWheelError) {
			_wheelErrorAvail = false;
		}
		if (_nextAvailPopup == _currPopup) {
			_popupAvail = false;
		}
		_newPopup = true;
	}
}

void WheelScreen::_setNumData(int display, int row, int columns[], int columnsSize, int data, bool showSign) {
	// make display data always positive so we can properly match to ASCII display values
	int dataAlt = (data >= 0) ? data : data * -1;
	// Extract each digit of "data" argument and put in appropriate slot in _displayData array
	int divider = 1;

	//Clear whatever is currently in the slot
	for (int colIndex = columnsSize - 1; colIndex >= 0; colIndex--) {
		_displayData[display][row][columns[colIndex]] = ' ';
	}

	//Extract and put the actual digit characters in the display data array
	for (int colIndex = columnsSize - 1; colIndex >= 0; colIndex--) {
		// Set the slot in the first column to the sign if showSign is true
		if (showSign && colIndex == 0) {
			_displayData[display][row][columns[colIndex]] = (data >= 0) ? '+' : '-';
		// Otherwise just get the digits, starting with least significant digit
		} else {
			_displayData[display][row][columns[colIndex]] = ((dataAlt / divider) % 10) + 48; // Adding 48 for ASCII
			divider *= 10;
		}
	}

	_writeCheck[row] = 1;
}

void WheelScreen::_setCharData(int display, int row, int columns[], int columnsSize, char data[], int dataSize) {
	// To ensure that we don't have overflow (Ex: can't fit the array ['B','R','I','Z','O'] into 4 slots)
	if (dataSize > columnsSize) {
		return;
	}

	// Clear whatever is currently in the slot
	for (int colIndex = 0; colIndex < dataSize; colIndex++) {
		_displayData[display][row][columns[colIndex]] = ' ';
	}

	// Put the character data in the display data array
	for (int i = 0; i < dataSize; i++) {
		_displayData[display][row][columns[i]] = data[i];
	}

	_writeCheck[row] = 1;
}

void WheelScreen::_setPopupNumData(int row, int columns[], int columnsSize, int data, bool showSign) {
	// make display data always positive so we can properly match to ASCII display values
	int dataAlt = (data >= 0) ? data : data * -1;
	// Extract each digit of "data" argument and put in appropriate slot in _displayData array
	int divider = 1;

	//Clear whatever is currently in the slot
	for (int colIndex = columnsSize - 1; colIndex >= 0; colIndex--) {
		_popupData[row][columns[colIndex]] = ' ';
	}

	//Extract and put the actual digit characters in the display data array
	for (int colIndex = columnsSize - 1; colIndex >= 0; colIndex--) {
		// Set the slot in the first column to the sign if showSign is true
		if (showSign && colIndex == 0) {
			_popupData[row][columns[colIndex]] = (data >= 0) ? '+' : '-';
		// Otherwise just get the digits, starting with least significant digit
		} else {
			_popupData[row][columns[colIndex]] = ((dataAlt / divider) % 10) + 48; // Adding 48 for ASCII
			divider *= 10;
		}
	}
}

void WheelScreen::_setPopupData(int row, int columns[], int columnsSize, char data[], int dataSize) {
	// To ensure that we don't have overflow (Ex: can't fit the array ['B','R','I','Z','O'] into 4 slots)
	if (dataSize > columnsSize) {
		return;
	}

	// Clear whatever is currently in the slot
	for (int colIndex = 0; colIndex < dataSize; colIndex++) {
		_popupData[row][columns[colIndex]] = ' ';
	}

	// Put the character data in the popup data array
	for (int i = 0; i < dataSize; i++) {
		_popupData[row][columns[i]]= data[i];
	}
}

void WheelScreen::_recentDataCheck(uint32_t time) {
	// Check last battery current time
	_recentDataCheckHelper(_lastBattCurrentTime, time, _battCurrentTimeLim, _battCurrentDisplay, _battCurrentRow, _battCurrentColumns,
		1);

	// Check last battery power time
	_recentDataCheckHelper(_battVoltageTimeLim, time, _lastBattVoltageTime, _battPowerDisplay, _battPowerRow, _battPowerColumns,
		1);

	// Check last battery high cell time
	_recentDataCheckHelper(_lastHighCellValTime, time, _highCellValTimeLim, _highCellValDisplay, _highCellValRow, _highCellValColumns,
			1);

	// Check last battery low cell time
	_recentDataCheckHelper(_lastLowCellValTime, time, _lowCellValTimeLim, _lowCellValDisplay, _lowCellValRow, _lowCellValColumns,
			1);

	// Check last high cell temperature time
	_recentDataCheckHelper(_lastHighCellTempTime, time, _highCellTempTimeLim, _highCellTempDisplay, _highCellTempRow, _highCellTempColumns,
			1);

	//check chase heartbeat
	_recentDataCheckHelper(_lastChaseTime, time, _lastChaseTimeOut, _ChaseDisplay, _chaseRow, _chaseColumns, 0);

	//check mcc status
	_recentDataCheckHelper(_lastMCCTime, time, _lastMCCTimeout, _MCCDisplay, _MCCRow, _MCCColumns, 0);
}

void WheelScreen::_recentDataCheckHelper(uint32_t lastTime, uint32_t time, uint32_t timeLimit, int display,
		int row, int columns[], int unitSize) {
	// If last updated time was too long ago, fill the correct character slots with "-" marks
	if (timing.threshold(lastTime, time, timeLimit)) {
		int newCols[columns[(int)sizeof(columns)/sizeof(columns[0]) - 1] - columns[0] + 1 + unitSize];
		char missingData[(int)sizeof(newCols)/sizeof(newCols[0])];
		for (int i = 0; i < sizeof(newCols)/sizeof(newCols[0]); i++) {
			newCols[i] = (i == 0) ? columns[0] : newCols[i - 1] + 1;
			missingData[i] = '-';
		}
		_setCharData(display, row, newCols, sizeof(newCols)/sizeof(newCols[0]), missingData, sizeof(missingData)/sizeof(missingData[0]));
	}
}

void WheelScreen::_setUpPopup() {
	_popupType popupType = _popupQueue[_currPopup];
	switch (popupType) {
	case _batteryShutdown:
		this->_setBatteryShutdownPopup(_batteryShutdownQueue[_currBatteryShutdown]);
		break;
	case _wheelError:
		this->_setWheelErrorPopup(_wheelErrorQueue[_currWheelError]);
		break;
	}

	int numPopups = 0;
	for (int i = 0; i < _numPopups; i++) {
		if (_popupQueue[i] != _noPopup) {
			numPopups++;
		}
	}
	numPopups = (numPopups - 1 < numPopups) ? numPopups - 1 : 0;
	_setPopupNumData(_numMessagesRow, _numMessagesColumns, sizeof(_numMessagesColumns)/sizeof(_numMessagesColumns[0]), numPopups, false);
	_newPopup = false;

	// Used for debugging
//	int numCalls[] = {18, 19};
//	_setPopupNumData(2, numCalls, sizeof(numCalls)/sizeof(numCalls[0]), batteryShutdownCalls, false);
//	int numClears[] = {15, 16};
//	_setPopupNumData(2, numClears, sizeof(numClears)/sizeof(numClears[0]), clearCalls, false);
}

void WheelScreen::_setBatteryShutdownPopup(BRIZO_CAN::BatteryShutdown batteryShutdown) {
	// Set battery shutdown message
	_setPopupData(_batteryShutdownMessageRow, _batteryShutdownColumns, sizeof(_batteryShutdownColumns)/sizeof(_batteryShutdownColumns[0]),
			_batteryShutdownMessage, sizeof(_batteryShutdownMessage)/sizeof(_batteryShutdownMessage[0]));

	switch (batteryShutdown) {
	case BRIZO_CAN::batteryShutdown_off:
		_setPopupData(_batteryShutdownReasonRow, _batteryShutdownColumns, sizeof(_batteryShutdownColumns)/sizeof(_batteryShutdownColumns[0]),
				_batteryShutdownOff, sizeof(_batteryShutdownOff)/sizeof(_batteryShutdownOff[0]));
		break;
	case BRIZO_CAN::batteryShutdown_cellUnderVoltage:
		_setPopupData(_batteryShutdownReasonRow, _batteryShutdownColumns, sizeof(_batteryShutdownColumns)/sizeof(_batteryShutdownColumns[0]),
				_batteryShutdownUnderVolt, sizeof(_batteryShutdownUnderVolt)/sizeof(_batteryShutdownUnderVolt[0]));
		break;
	case BRIZO_CAN::batteryShutdown_cellOverVoltage:
		_setPopupData(_batteryShutdownReasonRow, _batteryShutdownColumns, sizeof(_batteryShutdownColumns)/sizeof(_batteryShutdownColumns[0]),
				_batteryShutdownOverVolt, sizeof(_batteryShutdownOverVolt)/sizeof(_batteryShutdownOverVolt[0]));
		break;
	case BRIZO_CAN::batteryShutdown_overCurrentDischarge:
		_setPopupData(_batteryShutdownReasonRow, _batteryShutdownColumns, sizeof(_batteryShutdownColumns)/sizeof(_batteryShutdownColumns[0]),
				_batteryShutdownCurrDischarge, sizeof(_batteryShutdownCurrDischarge)/sizeof(_batteryShutdownCurrDischarge[0]));
		break;
	case BRIZO_CAN::batteryShutdown_overCurrentCharge:
		_setPopupData(_batteryShutdownReasonRow, _batteryShutdownColumns, sizeof(_batteryShutdownColumns)/sizeof(_batteryShutdownColumns[0]),
				_batteryShutdownCurrCharge, sizeof(_batteryShutdownCurrCharge)/sizeof(_batteryShutdownCurrCharge[0]));
		break;
	case BRIZO_CAN::batteryShutdown_overTemperatureDischarge:
		_setPopupData(_batteryShutdownReasonRow, _batteryShutdownColumns, sizeof(_batteryShutdownColumns)/sizeof(_batteryShutdownColumns[0]),
				_batteryShutdownTempDischarge, sizeof(_batteryShutdownTempDischarge)/sizeof(_batteryShutdownTempDischarge[0]));
		break;
	case BRIZO_CAN::batteryShutdown_overTemperatureCharge:
		_setPopupData(_batteryShutdownReasonRow, _batteryShutdownColumns, sizeof(_batteryShutdownColumns)/sizeof(_batteryShutdownColumns[0]),
				_batteryShutdownTempCharge, sizeof(_batteryShutdownTempCharge)/sizeof(_batteryShutdownTempCharge[0]));
		break;
	case BRIZO_CAN::batteryShutdown_auxPackPowered:
		_setPopupData(_batteryShutdownReasonRow, _batteryShutdownColumns, sizeof(_batteryShutdownColumns)/sizeof(_batteryShutdownColumns[0]),
				_batteryShutdownAuxPack, sizeof(_batteryShutdownAuxPack)/sizeof(_batteryShutdownAuxPack[0]));
		break;
	case BRIZO_CAN::batteryShutdown_LTC6811Unreachable:
		_setPopupData(_batteryShutdownReasonRow, _batteryShutdownColumns, sizeof(_batteryShutdownColumns)/sizeof(_batteryShutdownColumns[0]),
				_batteryShutdownLTC6811, sizeof(_batteryShutdownLTC6811)/sizeof(_batteryShutdownLTC6811[0]));
		break;
	case BRIZO_CAN::batteryShutdown_currentADCUnreachable:
		_setPopupData(_batteryShutdownReasonRow, _batteryShutdownColumns, sizeof(_batteryShutdownColumns)/sizeof(_batteryShutdownColumns[0]),
				_batteryShutdownCurrADC, sizeof(_batteryShutdownCurrADC)/sizeof(_batteryShutdownCurrADC[0]));
		break;
	case BRIZO_CAN::batteryShutdown_emergencyStop:
		_setPopupData(_batteryShutdownReasonRow, _batteryShutdownColumns, sizeof(_batteryShutdownColumns)/sizeof(_batteryShutdownColumns[0]),
				_batteryShutdownEmergencyStop, sizeof(_batteryShutdownEmergencyStop)/sizeof(_batteryShutdownEmergencyStop[0]));
		break;
	}
}

void WheelScreen::_setWheelErrorPopup(BRIZO_CAN::WheelErrors wheelError) {
	// Set wheel error message
	_setPopupData(_wheelErrorMessageRow, _wheelErrorColumns, sizeof(_wheelErrorColumns)/sizeof(_wheelErrorColumns[0]),
			_wheelErrorMessage, sizeof(_wheelErrorMessage)/sizeof(_wheelErrorMessage[0]));

	switch (wheelError) {
	case BRIZO_CAN::wheelError_watchdogReset:
		_setPopupData(_wheelErrorReasonRow, _wheelErrorColumns, sizeof(_wheelErrorColumns)/sizeof(_wheelErrorColumns[0]),
				_wheelErrorWatchDogReset, sizeof(_wheelErrorWatchDogReset)/sizeof(_wheelErrorWatchDogReset[0]));
		break;
	case BRIZO_CAN::wheelError_startOnCapPower:
		_setPopupData(_wheelErrorReasonRow, _wheelErrorColumns, sizeof(_wheelErrorColumns)/sizeof(_wheelErrorColumns[0]),
				_wheelErrorStartCapPower, sizeof(_wheelErrorStartCapPower)/sizeof(_wheelErrorStartCapPower[0]));
		break;
	case BRIZO_CAN::wheelError_superCapPower:
		_setPopupData(_wheelErrorReasonRow, _wheelErrorColumns, sizeof(_wheelErrorColumns)/sizeof(_wheelErrorColumns[0]),
				_wheelErrorSuperCapPower, sizeof(_wheelErrorSuperCapPower)/sizeof(_wheelErrorSuperCapPower[0]));
		break;
	case BRIZO_CAN::wheelError_sevenSegOverTemp:
		_setPopupData(_wheelErrorReasonRow, _wheelErrorColumns, sizeof(_wheelErrorColumns)/sizeof(_wheelErrorColumns[0]),
				_wheelError7SegOverTemp, sizeof(_wheelError7SegOverTemp)/sizeof(_wheelError7SegOverTemp[0]));
		break;
	case BRIZO_CAN::wheelError_sevenSegOutput:
		_setPopupData(_wheelErrorReasonRow, _wheelErrorColumns, sizeof(_wheelErrorColumns)/sizeof(_wheelErrorColumns[0]),
				_wheelError7SegOutput, sizeof(_wheelError7SegOutput)/sizeof(_wheelError7SegOutput[0]));
		break;
	case BRIZO_CAN::wheelError_sevenSegSetup:
		_setPopupData(_wheelErrorReasonRow, _wheelErrorColumns, sizeof(_wheelErrorColumns)/sizeof(_wheelErrorColumns[0]),
				_wheelError7SegSetup, sizeof(_wheelError7SegSetup)/sizeof(_wheelError7SegSetup[0]));
		break;
	case BRIZO_CAN::wheelError_OLEDSetup:
		_setPopupData(_wheelErrorReasonRow, _wheelErrorColumns, sizeof(_wheelErrorColumns)/sizeof(_wheelErrorColumns[0]),
				_wheelErrorOledSetup, sizeof(_wheelErrorOledSetup)/sizeof(_wheelErrorOledSetup[0]));
		break;
	case BRIZO_CAN::wheelError_encoderTimeout:
		_setPopupData(_wheelErrorReasonRow, _wheelErrorColumns, sizeof(_wheelErrorColumns)/sizeof(_wheelErrorColumns[0]),
				_wheelErrorEncoderTimeout, sizeof(_wheelErrorEncoderTimeout)/sizeof(_wheelErrorEncoderTimeout[0]));
		break;
	default:
		break;
	}
}





