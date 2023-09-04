################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../libraries/rtos/rtos/Mutex.cpp \
../libraries/rtos/rtos/RtosTimer.cpp \
../libraries/rtos/rtos/Semaphore.cpp \
../libraries/rtos/rtos/Thread.cpp 

CPP_DEPS += \
./libraries/rtos/rtos/Mutex.d \
./libraries/rtos/rtos/RtosTimer.d \
./libraries/rtos/rtos/Semaphore.d \
./libraries/rtos/rtos/Thread.d 

OBJS += \
./libraries/rtos/rtos/Mutex.o \
./libraries/rtos/rtos/RtosTimer.o \
./libraries/rtos/rtos/Semaphore.o \
./libraries/rtos/rtos/Thread.o 


# Each subdirectory must supply rules for building sources it contributes
libraries/rtos/rtos/%.o: ../libraries/rtos/rtos/%.cpp libraries/rtos/rtos/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -std=c++0x -D__CODE_RED -DCPP_USE_HEAP -DTARGET_LPC15xx -DTARGET_M3 -DTARGET_CORTEX_M -DTARGET_NXP -DTARGET_LPC15XX -DTOOLCHAIN_GCC_CR -DTOOLCHAIN_GCC -D__CORTEX_M3 -DARM_MATH_CM3 -D__NEWLIB__ -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\hal" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\api" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\cmsis" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\common" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtos" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtx\TARGET_CORTEX_M" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\fs\fat" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\fs\fat\ChaN" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\fs\sd" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\cmsis\TARGET_NXP\TARGET_LPC15XX" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\cmsis\TARGET_NXP\TARGET_LPC15XX\TOOLCHAIN_GCC_CR" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\hal\TARGET_NXP\TARGET_LPC15XX" -O3 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-libraries-2f-rtos-2f-rtos

clean-libraries-2f-rtos-2f-rtos:
	-$(RM) ./libraries/rtos/rtos/Mutex.d ./libraries/rtos/rtos/Mutex.o ./libraries/rtos/rtos/RtosTimer.d ./libraries/rtos/rtos/RtosTimer.o ./libraries/rtos/rtos/Semaphore.d ./libraries/rtos/rtos/Semaphore.o ./libraries/rtos/rtos/Thread.d ./libraries/rtos/rtos/Thread.o

.PHONY: clean-libraries-2f-rtos-2f-rtos

