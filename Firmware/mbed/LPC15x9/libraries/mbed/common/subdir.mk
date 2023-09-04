################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../libraries/mbed/common/BusIn.cpp \
../libraries/mbed/common/BusInOut.cpp \
../libraries/mbed/common/BusOut.cpp \
../libraries/mbed/common/CAN.cpp \
../libraries/mbed/common/CallChain.cpp \
../libraries/mbed/common/Ethernet.cpp \
../libraries/mbed/common/FileBase.cpp \
../libraries/mbed/common/FileLike.cpp \
../libraries/mbed/common/FilePath.cpp \
../libraries/mbed/common/FileSystemLike.cpp \
../libraries/mbed/common/I2C.cpp \
../libraries/mbed/common/I2CSlave.cpp \
../libraries/mbed/common/InterruptIn.cpp \
../libraries/mbed/common/InterruptManager.cpp \
../libraries/mbed/common/LocalFileSystem.cpp \
../libraries/mbed/common/RawSerial.cpp \
../libraries/mbed/common/SPI.cpp \
../libraries/mbed/common/SPISlave.cpp \
../libraries/mbed/common/Serial.cpp \
../libraries/mbed/common/SerialBase.cpp \
../libraries/mbed/common/Stream.cpp \
../libraries/mbed/common/Ticker.cpp \
../libraries/mbed/common/Timeout.cpp \
../libraries/mbed/common/Timer.cpp \
../libraries/mbed/common/TimerEvent.cpp \
../libraries/mbed/common/retarget.cpp 

C_SRCS += \
../libraries/mbed/common/assert.c \
../libraries/mbed/common/board.c \
../libraries/mbed/common/error.c \
../libraries/mbed/common/gpio.c \
../libraries/mbed/common/lp_ticker_api.c \
../libraries/mbed/common/mbed_interface.c \
../libraries/mbed/common/pinmap_common.c \
../libraries/mbed/common/rtc_time.c \
../libraries/mbed/common/semihost_api.c \
../libraries/mbed/common/ticker_api.c \
../libraries/mbed/common/us_ticker_api.c \
../libraries/mbed/common/wait_api.c 

CPP_DEPS += \
./libraries/mbed/common/BusIn.d \
./libraries/mbed/common/BusInOut.d \
./libraries/mbed/common/BusOut.d \
./libraries/mbed/common/CAN.d \
./libraries/mbed/common/CallChain.d \
./libraries/mbed/common/Ethernet.d \
./libraries/mbed/common/FileBase.d \
./libraries/mbed/common/FileLike.d \
./libraries/mbed/common/FilePath.d \
./libraries/mbed/common/FileSystemLike.d \
./libraries/mbed/common/I2C.d \
./libraries/mbed/common/I2CSlave.d \
./libraries/mbed/common/InterruptIn.d \
./libraries/mbed/common/InterruptManager.d \
./libraries/mbed/common/LocalFileSystem.d \
./libraries/mbed/common/RawSerial.d \
./libraries/mbed/common/SPI.d \
./libraries/mbed/common/SPISlave.d \
./libraries/mbed/common/Serial.d \
./libraries/mbed/common/SerialBase.d \
./libraries/mbed/common/Stream.d \
./libraries/mbed/common/Ticker.d \
./libraries/mbed/common/Timeout.d \
./libraries/mbed/common/Timer.d \
./libraries/mbed/common/TimerEvent.d \
./libraries/mbed/common/retarget.d 

C_DEPS += \
./libraries/mbed/common/assert.d \
./libraries/mbed/common/board.d \
./libraries/mbed/common/error.d \
./libraries/mbed/common/gpio.d \
./libraries/mbed/common/lp_ticker_api.d \
./libraries/mbed/common/mbed_interface.d \
./libraries/mbed/common/pinmap_common.d \
./libraries/mbed/common/rtc_time.d \
./libraries/mbed/common/semihost_api.d \
./libraries/mbed/common/ticker_api.d \
./libraries/mbed/common/us_ticker_api.d \
./libraries/mbed/common/wait_api.d 

OBJS += \
./libraries/mbed/common/BusIn.o \
./libraries/mbed/common/BusInOut.o \
./libraries/mbed/common/BusOut.o \
./libraries/mbed/common/CAN.o \
./libraries/mbed/common/CallChain.o \
./libraries/mbed/common/Ethernet.o \
./libraries/mbed/common/FileBase.o \
./libraries/mbed/common/FileLike.o \
./libraries/mbed/common/FilePath.o \
./libraries/mbed/common/FileSystemLike.o \
./libraries/mbed/common/I2C.o \
./libraries/mbed/common/I2CSlave.o \
./libraries/mbed/common/InterruptIn.o \
./libraries/mbed/common/InterruptManager.o \
./libraries/mbed/common/LocalFileSystem.o \
./libraries/mbed/common/RawSerial.o \
./libraries/mbed/common/SPI.o \
./libraries/mbed/common/SPISlave.o \
./libraries/mbed/common/Serial.o \
./libraries/mbed/common/SerialBase.o \
./libraries/mbed/common/Stream.o \
./libraries/mbed/common/Ticker.o \
./libraries/mbed/common/Timeout.o \
./libraries/mbed/common/Timer.o \
./libraries/mbed/common/TimerEvent.o \
./libraries/mbed/common/assert.o \
./libraries/mbed/common/board.o \
./libraries/mbed/common/error.o \
./libraries/mbed/common/gpio.o \
./libraries/mbed/common/lp_ticker_api.o \
./libraries/mbed/common/mbed_interface.o \
./libraries/mbed/common/pinmap_common.o \
./libraries/mbed/common/retarget.o \
./libraries/mbed/common/rtc_time.o \
./libraries/mbed/common/semihost_api.o \
./libraries/mbed/common/ticker_api.o \
./libraries/mbed/common/us_ticker_api.o \
./libraries/mbed/common/wait_api.o 


# Each subdirectory must supply rules for building sources it contributes
libraries/mbed/common/%.o: ../libraries/mbed/common/%.cpp libraries/mbed/common/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -std=c++0x -D__CODE_RED -DCPP_USE_HEAP -DTARGET_LPC15xx -DTARGET_M3 -DTARGET_CORTEX_M -DTARGET_NXP -DTARGET_LPC15XX -DTOOLCHAIN_GCC_CR -DTOOLCHAIN_GCC -D__CORTEX_M3 -DARM_MATH_CM3 -D__NEWLIB__ -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\hal" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\api" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\cmsis" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\common" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtos" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtx\TARGET_CORTEX_M" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\fs\fat" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\fs\fat\ChaN" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\fs\sd" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\cmsis\TARGET_NXP\TARGET_LPC15XX" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\cmsis\TARGET_NXP\TARGET_LPC15XX\TOOLCHAIN_GCC_CR" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\hal\TARGET_NXP\TARGET_LPC15XX" -O3 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libraries/mbed/common/%.o: ../libraries/mbed/common/%.c libraries/mbed/common/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -D__CODE_RED -DCPP_USE_HEAP -DTARGET_LPC1549 -DTARGET_M3 -DTARGET_CORTEX_M -DTARGET_NXP -DTARGET_LPC15XX -DTOOLCHAIN_GCC_CR -DTOOLCHAIN_GCC -D__CORTEX_M3 -DARM_MATH_CM3 -D__NEWLIB__ -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\hal" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\api" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\cmsis" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\common" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtos" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtx\TARGET_CORTEX_M" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtx\TARGET_CORTEX_M\TARGET_M3" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtx\TARGET_CORTEX_M\TARGET_M3\TOOLCHAIN_GCC" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\fs\fat" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\fs\fat\ChaN" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\fs\sd" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\cmsis\TARGET_NXP\TARGET_LPC15XX" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\cmsis\TARGET_NXP\TARGET_LPC15XX\TOOLCHAIN_GCC_CR" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\hal\TARGET_NXP\TARGET_LPC15XX" -O3 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-libraries-2f-mbed-2f-common

clean-libraries-2f-mbed-2f-common:
	-$(RM) ./libraries/mbed/common/BusIn.d ./libraries/mbed/common/BusIn.o ./libraries/mbed/common/BusInOut.d ./libraries/mbed/common/BusInOut.o ./libraries/mbed/common/BusOut.d ./libraries/mbed/common/BusOut.o ./libraries/mbed/common/CAN.d ./libraries/mbed/common/CAN.o ./libraries/mbed/common/CallChain.d ./libraries/mbed/common/CallChain.o ./libraries/mbed/common/Ethernet.d ./libraries/mbed/common/Ethernet.o ./libraries/mbed/common/FileBase.d ./libraries/mbed/common/FileBase.o ./libraries/mbed/common/FileLike.d ./libraries/mbed/common/FileLike.o ./libraries/mbed/common/FilePath.d ./libraries/mbed/common/FilePath.o ./libraries/mbed/common/FileSystemLike.d ./libraries/mbed/common/FileSystemLike.o ./libraries/mbed/common/I2C.d ./libraries/mbed/common/I2C.o ./libraries/mbed/common/I2CSlave.d ./libraries/mbed/common/I2CSlave.o ./libraries/mbed/common/InterruptIn.d ./libraries/mbed/common/InterruptIn.o ./libraries/mbed/common/InterruptManager.d ./libraries/mbed/common/InterruptManager.o ./libraries/mbed/common/LocalFileSystem.d ./libraries/mbed/common/LocalFileSystem.o ./libraries/mbed/common/RawSerial.d ./libraries/mbed/common/RawSerial.o ./libraries/mbed/common/SPI.d ./libraries/mbed/common/SPI.o ./libraries/mbed/common/SPISlave.d ./libraries/mbed/common/SPISlave.o ./libraries/mbed/common/Serial.d ./libraries/mbed/common/Serial.o ./libraries/mbed/common/SerialBase.d ./libraries/mbed/common/SerialBase.o ./libraries/mbed/common/Stream.d ./libraries/mbed/common/Stream.o ./libraries/mbed/common/Ticker.d ./libraries/mbed/common/Ticker.o ./libraries/mbed/common/Timeout.d ./libraries/mbed/common/Timeout.o ./libraries/mbed/common/Timer.d ./libraries/mbed/common/Timer.o ./libraries/mbed/common/TimerEvent.d ./libraries/mbed/common/TimerEvent.o ./libraries/mbed/common/assert.d ./libraries/mbed/common/assert.o ./libraries/mbed/common/board.d ./libraries/mbed/common/board.o ./libraries/mbed/common/error.d ./libraries/mbed/common/error.o ./libraries/mbed/common/gpio.d ./libraries/mbed/common/gpio.o ./libraries/mbed/common/lp_ticker_api.d ./libraries/mbed/common/lp_ticker_api.o ./libraries/mbed/common/mbed_interface.d ./libraries/mbed/common/mbed_interface.o ./libraries/mbed/common/pinmap_common.d ./libraries/mbed/common/pinmap_common.o ./libraries/mbed/common/retarget.d ./libraries/mbed/common/retarget.o ./libraries/mbed/common/rtc_time.d ./libraries/mbed/common/rtc_time.o ./libraries/mbed/common/semihost_api.d ./libraries/mbed/common/semihost_api.o ./libraries/mbed/common/ticker_api.d ./libraries/mbed/common/ticker_api.o ./libraries/mbed/common/us_ticker_api.d ./libraries/mbed/common/us_ticker_api.o ./libraries/mbed/common/wait_api.d ./libraries/mbed/common/wait_api.o

.PHONY: clean-libraries-2f-mbed-2f-common

