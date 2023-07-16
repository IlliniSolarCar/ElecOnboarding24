################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/PCA9745b.cpp \
../src/US2066.cpp \
../src/WheelIndicators.cpp \
../src/WheelScreen.cpp \
../src/blinky.cpp \
../src/common.cpp \
../src/cr_cpp_config.cpp \
../src/cr_startup_lpc175x_6x.cpp \
../src/peripherals.cpp \
../src/pins.cpp 

C_SRCS += \
../src/crp.c 

CPP_DEPS += \
./src/PCA9745b.d \
./src/US2066.d \
./src/WheelIndicators.d \
./src/WheelScreen.d \
./src/blinky.d \
./src/common.d \
./src/cr_cpp_config.d \
./src/cr_startup_lpc175x_6x.d \
./src/peripherals.d \
./src/pins.d 

C_DEPS += \
./src/crp.d 

OBJS += \
./src/PCA9745b.o \
./src/US2066.o \
./src/WheelIndicators.o \
./src/WheelScreen.o \
./src/blinky.o \
./src/common.o \
./src/cr_cpp_config.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/peripherals.o \
./src/pins.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -std=c++11 -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -DCPP_USE_HEAP -D__LPC17XX__ -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/blinky/inc" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/common/api" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/common" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/mbed/targets/cmsis" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC176X" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/mbed/hal" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/mbed/api" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/mbed/targets/cmsis" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/mbed/common" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/rtos" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/rtos/rtos" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/rtos/rtx/TARGET_CORTEX_M" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/rtos/rtx/TARGET_CORTEX_M/TARGET_M3" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/rtos/rtx/TARGET_CORTEX_M/TARGET_M3/TOOLCHAIN_GCC" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/fs/fat" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/fs/fat/ChaN" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/fs/sd" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC176X" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/TARGET_MBED_LPC1768" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -DCPP_USE_HEAP -D__LPC17XX__ -D__NEWLIB__ -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/blinky/inc" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/common/api" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/common" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/mbed/hal" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/mbed/api" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/mbed/targets/cmsis" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/mbed/common" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/rtos" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/rtos/rtos" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/rtos/rtx/TARGET_CORTEX_M" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/rtos/rtx/TARGET_CORTEX_M/TARGET_M3" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/rtos/rtx/TARGET_CORTEX_M/TARGET_M3/TOOLCHAIN_GCC" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/fs/fat" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/fs/fat/ChaN" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/fs/sd" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC176X" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC176X/TARGET_MBED_LPC1768" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/mbed/targets/cmsis" -I"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC176X" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/PCA9745b.d ./src/PCA9745b.o ./src/US2066.d ./src/US2066.o ./src/WheelIndicators.d ./src/WheelIndicators.o ./src/WheelScreen.d ./src/WheelScreen.o ./src/blinky.d ./src/blinky.o ./src/common.d ./src/common.o ./src/cr_cpp_config.d ./src/cr_cpp_config.o ./src/cr_startup_lpc175x_6x.d ./src/cr_startup_lpc175x_6x.o ./src/crp.d ./src/crp.o ./src/peripherals.d ./src/peripherals.o ./src/pins.d ./src/pins.o

.PHONY: clean-src

