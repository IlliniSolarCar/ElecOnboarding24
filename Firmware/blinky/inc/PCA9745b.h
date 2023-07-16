#ifndef WHEEL_PCA9745B_H_
#define WHEEL_PCA9745B_H_

/*
 * This is a basic driver for a daisy chain of PCA9745b SPI 16 output LED Drivers
 * It will allow control of output to and brightness of up to 4 in daisy chain configuration
 * Error checking does not take any actions!
 * 			- Jonathan      Apr 2019, refactored Apr 2020
 */

#include <mbed.h>

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

/*
 * Offset between updates of outputs to reduce peak EMI and current draw
 * value 0 - 255, offset time will be value * 125us
 */
constexpr uint8_t _offset = 0xFF;


template <typename T_uint>
class PCA9745b{
public:
	/*
	 * Construct a daisy chain of PCA9745b's (up to 4)
	 * Template type should hold min of 16 bits per PCA9745b
	 * @param cs - chip select Object for the ICs
	 * @param reset - reset object for the ICs
	 * @param enable - enable object for the ICs
	 * @param spi - object for the spi bus
	 * @param count - optional count of PCA9745b. Leave blank for auto count based on template type
	 * @param exponentialDim - sets the dimMode (True: Exponential, False: Linear)
	 */
	PCA9745b(DigitalOut& cs, DigitalOut& reset, DigitalOut& enable, SPI& spi, uint8_t count = 0, bool exponentialDim = true);

	/*
	 * Initialize the PCA9745b
	 * Includes a 2ms wait due to reset time of the device
	 *
	 * @return 0 - success; 1 - invalid count; 2 - unable to connect
	 */
	uint8_t init(uint8_t brightness);

	/*
	 * Set the brightness of all outputs with current limit
	 * @param brightness - 256 increments from 0 - 255
	 * Output current will be: (brightness) * (900mV/Rest) * 0.25
	 */
	void setBrightness(uint8_t brightness);

	/*
	 * Set the Dimming mode of PCA9745b
	 * @param setDimMode - True -> exponential dim, False-> Linear dim
	 */
	void setDimmingMode(bool setDimMode);

	/*
	 * Set the output of the devices.
	 * @param output - bitmap output. LSB is output 0 of device 0
	 * Device 0 is PCA9745b furthest from the MCU
	 * @return 0xFF if not initalized, otherwise returns _checkIfError()
	 */
	uint8_t setOutput(T_uint output);

	/*
	 * Check for an open circuit for each LED and disable output to those with open circuits
	 * Will only return open-circuited LEDs when LEDs are on
	 * @return bitmap specifying the LEDs with open circuits (1 = open circuit, 0 = normal)
	 */
	T_uint checkOpenCkt();

	/*
	 * Check for a short circuit for each LED and disable output to those with short circuits
	 * Will only return short-circuited LEDs when LEDs are on
	 * @return bitmap specifying the LEDs with short circuits (1 = short circuit, 0 = normal)
	 */
	T_uint checkShortCkt();

	/*
	 * Enable or disable the device
	 * @param enable - whether it should enabled or not
	 */
	void enable(bool enable);

	/*
	 * Reset the devices. Will reinitialized to previously initialized states.
	 * Will not write output
	 * Includes required 2ms wait time.
	 */
	void reset();

	/*
	 * Enable/disable low-power mode on the device
	 * @param lp - true if enabling low-power mode, false if disabling
	 */
	void lowPower(bool lp);

	/*
	 * Check if device is in low power mode
	 * @return true if in low power mode, false else
	 */
	bool isLowPower();

private:
	DigitalOut& _cs;
	DigitalOut& _reset;
	DigitalOut& _enable;
	SPI& _spi;
	uint8_t _deviceCount;
	bool _lowPower = false;
	bool _exponentialDim;


	enum _portMap : uint8_t {
		mode1 		= 0x00,
		mode2		= 0x01,
		ledout0		= 0x02,
		ledout1		= 0x03,
		ledout2		= 0x04,
		ledout3		= 0x05,
		grpPWM		= 0x06,
		grpFreq		= 0x07,

		offset		= 0x3F,
		PWMAll		= 0x40,
		IRefAll		= 0x41,
		error0		= 0x42,
		error1		= 0x43,
		error2		= 0x44,
		error3		= 0x45
	};

	/*
	 * Status Data
	 */
	bool _initialized = false;


	/*
	 * Saved data for reset
	 */
	uint8_t _brightness = 0x00;
	T_uint _output = 0;
	T_uint _outputDisable = -1;


	/*
	 * Helper to set SPI format and frequency
	 */
	void _setupSPI();

	/*
	 * Check data throughput
	 * @return true if success, false else;
	 */
	bool _checkConnection();

	/*
	 * Initializes the PCA9745b for basic usage
	 * @param brightness - optional, can be set or loaded from default
	 */
	void _init();
	void _init(uint8_t brightness);

	/*
	 * Resets the PCBA9745b
	 */
	void _resetDevice();

	/*
	 * Checks mode 2 register for overtemp error or existence of output error
	 * Note - does not get specific output error or do anything about it
	 * @return 0: no error; bitmap of errors: 0x01 = overtemp device 0, 0x02 = output error device 0
	 * 											0x04 = overtemp deice 1, so on.
	 */
	uint8_t _checkIfErrors();

	/*
	 * Check if a short/open circuit exists for each LED, disable any LED with a short circuit
	 * Will only return open/short-circuited LEDs when LEDs are on
	 * @param errorType - 0 if checking for short circuit, 1 if checking for open circuit
	 * @return a bitmap indicating which LEDs have short/open circuits (1 = short/open circuit, 0 = normal)
	 * The bitmap mapping is identical to the mapping for the bitmap argument to setOutput(...)
	 */
	T_uint _checkCktErrors(bool errorType);

	/*
	 * Write the same data to all.
	 * @param port - port to write to (7 lower bits)
	 * @param data - data to write
	 */
	void _writePortAll(_portMap port, uint8_t data);

	/*
	 * Write to one port of one the devices
	 * @param port - port to write to
	 * @param data - data to write
	 * @param deviceIndex -  device to write to. 0 indexed, 0 is the furthest device on the bus
	 */
	void _writePort(_portMap port, uint8_t data, uint8_t deviceIndex);

	/*
	 * Read the same data from all devices
	 * @param port - port to read from
	 * @return the data from each device (1 byte each). The lowest byte is device 0
	 */
	T_uint _readPortAll(_portMap port);

	/*
	 * Read data from one port on one device
	 * @param port - port to read from
	 * @param deviceIndex -  device to read from
	 * @return the data read from that port
	 */
	uint8_t _readPort(_portMap port, uint8_t deviceIndex);

	/*
	 * format the data to send to the device
	 * @param write - if this is write operation
	 * @param port - port to write to (lower 7 bits)
	 * @param data - the data to use (optional for read)
	 */
	uint16_t _formatData(bool write, _portMap port, uint8_t data = 0x00);

	/*
	 * Write outputs for all devices.
	 * @param output the input as a bit map. LSB is device 0 output 0
	 */
	void _writeOutputsAll(T_uint output);
};


/*
 * This explicit instantiation required if this will be instantiated within another class
 * Comment out ones not needed, otherwise they also get built.
 * Literally pulled some of my hair out because of this -- Jonathan
 */
//template class PCA9745b<uint16_t>;
template class PCA9745b<uint32_t>;
//template class PCA9745b<uint64_t>;

#endif /* WHEEL_PCA9745B_H_ */




