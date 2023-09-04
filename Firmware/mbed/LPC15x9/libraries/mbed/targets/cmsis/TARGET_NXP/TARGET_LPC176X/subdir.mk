################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC176X/cmsis_nvic.c \
../libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC176X/system_LPC17xx.c 

C_DEPS += \
./libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC176X/cmsis_nvic.d \
./libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC176X/system_LPC17xx.d 

OBJS += \
./libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC176X/cmsis_nvic.o \
./libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC176X/system_LPC17xx.o 


# Each subdirectory must supply rules for building sources it contributes
libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC176X/%.o: ../libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC176X/%.c libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC176X/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -D__CODE_RED -DCPP_USE_HEAP -DTARGET_M3 -DTARGET_CORTEX_M -DTARGET_NXP -DTOOLCHAIN_GCC_CR -DTOOLCHAIN_GCC -D__CORTEX_M3 -DARM_MATH_CM3 -D__NEWLIB__ -DTARGET_LPC1768 -DTARGET_LPC176X -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\hal" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\api" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\cmsis" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\common" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtos" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtx\TARGET_CORTEX_M" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtx\TARGET_CORTEX_M\TARGET_M3" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtx\TARGET_CORTEX_M\TARGET_M3\TOOLCHAIN_GCC" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\fs\fat" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\fs\fat\ChaN" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\fs\sd" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\cmsis\TARGET_NXP\TARGET_LPC176X" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\cmsis\TARGET_NXP\TARGET_LPC176X\TOOLCHAIN_GCC_CR" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\hal\TARGET_NXP\TARGET_LPC176X" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\hal\TARGET_NXP\TARGET_LPC176X\TARGET_MBED_LPC1768" -O3 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-libraries-2f-mbed-2f-targets-2f-cmsis-2f-TARGET_NXP-2f-TARGET_LPC176X

clean-libraries-2f-mbed-2f-targets-2f-cmsis-2f-TARGET_NXP-2f-TARGET_LPC176X:
	-$(RM) ./libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC176X/cmsis_nvic.d ./libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC176X/cmsis_nvic.o ./libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC176X/system_LPC17xx.d ./libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC176X/system_LPC17xx.o

.PHONY: clean-libraries-2f-mbed-2f-targets-2f-cmsis-2f-TARGET_NXP-2f-TARGET_LPC176X

