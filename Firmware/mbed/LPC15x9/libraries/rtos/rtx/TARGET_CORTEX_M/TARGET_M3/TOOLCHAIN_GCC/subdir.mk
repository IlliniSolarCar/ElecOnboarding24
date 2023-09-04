################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../libraries/rtos/rtx/TARGET_CORTEX_M/TARGET_M3/TOOLCHAIN_GCC/HAL_CM3.S \
../libraries/rtos/rtx/TARGET_CORTEX_M/TARGET_M3/TOOLCHAIN_GCC/SVC_Table.S 

OBJS += \
./libraries/rtos/rtx/TARGET_CORTEX_M/TARGET_M3/TOOLCHAIN_GCC/HAL_CM3.o \
./libraries/rtos/rtx/TARGET_CORTEX_M/TARGET_M3/TOOLCHAIN_GCC/SVC_Table.o 


# Each subdirectory must supply rules for building sources it contributes
libraries/rtos/rtx/TARGET_CORTEX_M/TARGET_M3/TOOLCHAIN_GCC/%.o: ../libraries/rtos/rtx/TARGET_CORTEX_M/TARGET_M3/TOOLCHAIN_GCC/%.S libraries/rtos/rtx/TARGET_CORTEX_M/TARGET_M3/TOOLCHAIN_GCC/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -D__NEWLIB__ -DDEBUG -D__CODE_RED -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\hal" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\api" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtos" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtx\TARGET_CORTEX_M" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtx\TARGET_CORTEX_M\TARGET_M3" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtx\TARGET_CORTEX_M\TARGET_M3\TOOLCHAIN_GCC" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\fs\fat" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\fs\fat\ChaN" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\fs\sd" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\cmsis" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\common" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\cmsis\TARGET_NXP\TARGET_LPC15XX" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\cmsis\TARGET_NXP\TARGET_LPC15XX\TOOLCHAIN_GCC_CR" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\hal\TARGET_NXP\TARGET_LPC15XX" -g3 -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-libraries-2f-rtos-2f-rtx-2f-TARGET_CORTEX_M-2f-TARGET_M3-2f-TOOLCHAIN_GCC

clean-libraries-2f-rtos-2f-rtx-2f-TARGET_CORTEX_M-2f-TARGET_M3-2f-TOOLCHAIN_GCC:
	-$(RM) ./libraries/rtos/rtx/TARGET_CORTEX_M/TARGET_M3/TOOLCHAIN_GCC/HAL_CM3.o ./libraries/rtos/rtx/TARGET_CORTEX_M/TARGET_M3/TOOLCHAIN_GCC/SVC_Table.o

.PHONY: clean-libraries-2f-rtos-2f-rtx-2f-TARGET_CORTEX_M-2f-TARGET_M3-2f-TOOLCHAIN_GCC

