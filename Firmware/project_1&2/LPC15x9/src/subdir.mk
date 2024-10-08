################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/main.cpp \
../src/peripherals.cpp \
../src/pins.cpp 

CPP_DEPS += \
./src/main.d \
./src/peripherals.d \
./src/pins.d 

OBJS += \
./src/main.o \
./src/peripherals.o \
./src/pins.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -std=c++0x -D__CODE_RED -DCPP_USE_HEAP -DTARGET_LPC1549 -DTARGET_M3 -DTARGET_CORTEX_M -DTARGET_NXP -DTARGET_LPC15XX -DTOOLCHAIN_GCC_CR -DTOOLCHAIN_GCC -D__CORTEX_M3 -DARM_MATH_CM3 -D__NEWLIB__ -I"C:\Users\Yuan Quan\ISC\Onboarding\ElecOnboarding24\Firmware\common" -I"C:\Users\Yuan Quan\ISC\Onboarding\ElecOnboarding24\Firmware\mbed" -I"C:\Users\Yuan Quan\ISC\Onboarding\ElecOnboarding24\Firmware\project_1\inc" -I"C:\Users\Yuan Quan\ISC\Onboarding\ElecOnboarding24\Firmware\common\api" -I"C:\Users\Yuan Quan\ISC\Onboarding\ElecOnboarding24\Firmware\common\hal" -I"C:\Users\Yuan Quan\ISC\Onboarding\ElecOnboarding24\Firmware\mbed\libraries\mbed\hal" -I"C:\Users\Yuan Quan\ISC\Onboarding\ElecOnboarding24\Firmware\mbed\libraries\mbed\api" -I"C:\Users\Yuan Quan\ISC\Onboarding\ElecOnboarding24\Firmware\mbed\libraries\mbed\targets\cmsis" -I"C:\Users\Yuan Quan\ISC\Onboarding\ElecOnboarding24\Firmware\mbed\libraries\mbed\targets\cmsis\TARGET_NXP\TARGET_LPC15XX" -I"C:\Users\Yuan Quan\ISC\Onboarding\ElecOnboarding24\Firmware\mbed\libraries\mbed\targets\cmsis\TARGET_NXP\TARGET_LPC15XX\TOOLCHAIN_GCC_CR" -I"C:\Users\Yuan Quan\ISC\Onboarding\ElecOnboarding24\Firmware\mbed\libraries\mbed\targets\hal\TARGET_NXP\TARGET_LPC15XX" -Os -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/main.d ./src/main.o ./src/peripherals.d ./src/peripherals.o ./src/pins.d ./src/pins.o

.PHONY: clean-src

