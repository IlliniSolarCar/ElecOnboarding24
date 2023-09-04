################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/analogin_api.c \
../libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/analogout_api.c \
../libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/can_api.c \
../libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/ethernet_api.c \
../libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/gpio_api.c \
../libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/gpio_irq_api.c \
../libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/i2c_api.c \
../libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/pinmap.c \
../libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/port_api.c \
../libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/pwmout_api.c \
../libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/rtc_api.c \
../libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/serial_api.c \
../libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/sleep.c \
../libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/spi_api.c \
../libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/us_ticker.c 

C_DEPS += \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/analogin_api.d \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/analogout_api.d \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/can_api.d \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/ethernet_api.d \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/gpio_api.d \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/gpio_irq_api.d \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/i2c_api.d \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/pinmap.d \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/port_api.d \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/pwmout_api.d \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/rtc_api.d \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/serial_api.d \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/sleep.d \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/spi_api.d \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/us_ticker.d 

OBJS += \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/analogin_api.o \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/analogout_api.o \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/can_api.o \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/ethernet_api.o \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/gpio_api.o \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/gpio_irq_api.o \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/i2c_api.o \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/pinmap.o \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/port_api.o \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/pwmout_api.o \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/rtc_api.o \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/serial_api.o \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/sleep.o \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/spi_api.o \
./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/us_ticker.o 


# Each subdirectory must supply rules for building sources it contributes
libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/%.o: ../libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/%.c libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -D__CODE_RED -DCPP_USE_HEAP -DTARGET_M3 -DTARGET_CORTEX_M -DTARGET_NXP -DTOOLCHAIN_GCC_CR -DTOOLCHAIN_GCC -D__CORTEX_M3 -DARM_MATH_CM3 -D__NEWLIB__ -DTARGET_LPC1768 -DTARGET_LPC176X -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\hal" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\api" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\cmsis" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\common" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtos" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtx\TARGET_CORTEX_M" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtx\TARGET_CORTEX_M\TARGET_M3" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtx\TARGET_CORTEX_M\TARGET_M3\TOOLCHAIN_GCC" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\fs\fat" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\fs\fat\ChaN" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\fs\sd" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\cmsis\TARGET_NXP\TARGET_LPC176X" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\cmsis\TARGET_NXP\TARGET_LPC176X\TOOLCHAIN_GCC_CR" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\hal\TARGET_NXP\TARGET_LPC176X" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\hal\TARGET_NXP\TARGET_LPC176X\TARGET_MBED_LPC1768" -O3 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-libraries-2f-mbed-2f-targets-2f-hal-2f-TARGET_NXP-2f-TARGET_LPC176X

clean-libraries-2f-mbed-2f-targets-2f-hal-2f-TARGET_NXP-2f-TARGET_LPC176X:
	-$(RM) ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/analogin_api.d ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/analogin_api.o ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/analogout_api.d ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/analogout_api.o ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/can_api.d ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/can_api.o ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/ethernet_api.d ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/ethernet_api.o ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/gpio_api.d ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/gpio_api.o ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/gpio_irq_api.d ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/gpio_irq_api.o ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/i2c_api.d ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/i2c_api.o ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/pinmap.d ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/pinmap.o ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/port_api.d ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/port_api.o ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/pwmout_api.d ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/pwmout_api.o ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/rtc_api.d ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/rtc_api.o ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/serial_api.d ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/serial_api.o ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/sleep.d ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/sleep.o ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/spi_api.d ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/spi_api.o ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/us_ticker.d ./libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/us_ticker.o

.PHONY: clean-libraries-2f-mbed-2f-targets-2f-hal-2f-TARGET_NXP-2f-TARGET_LPC176X

