################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/rtos/rtx/TARGET_CORTEX_M/HAL_CM.c \
../libraries/rtos/rtx/TARGET_CORTEX_M/RTX_Conf_CM.c \
../libraries/rtos/rtx/TARGET_CORTEX_M/rt_CMSIS.c \
../libraries/rtos/rtx/TARGET_CORTEX_M/rt_Event.c \
../libraries/rtos/rtx/TARGET_CORTEX_M/rt_List.c \
../libraries/rtos/rtx/TARGET_CORTEX_M/rt_Mailbox.c \
../libraries/rtos/rtx/TARGET_CORTEX_M/rt_MemBox.c \
../libraries/rtos/rtx/TARGET_CORTEX_M/rt_Mutex.c \
../libraries/rtos/rtx/TARGET_CORTEX_M/rt_Robin.c \
../libraries/rtos/rtx/TARGET_CORTEX_M/rt_Semaphore.c \
../libraries/rtos/rtx/TARGET_CORTEX_M/rt_System.c \
../libraries/rtos/rtx/TARGET_CORTEX_M/rt_Task.c \
../libraries/rtos/rtx/TARGET_CORTEX_M/rt_Time.c 

C_DEPS += \
./libraries/rtos/rtx/TARGET_CORTEX_M/HAL_CM.d \
./libraries/rtos/rtx/TARGET_CORTEX_M/RTX_Conf_CM.d \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_CMSIS.d \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Event.d \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_List.d \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Mailbox.d \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_MemBox.d \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Mutex.d \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Robin.d \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Semaphore.d \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_System.d \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Task.d \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Time.d 

OBJS += \
./libraries/rtos/rtx/TARGET_CORTEX_M/HAL_CM.o \
./libraries/rtos/rtx/TARGET_CORTEX_M/RTX_Conf_CM.o \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_CMSIS.o \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Event.o \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_List.o \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Mailbox.o \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_MemBox.o \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Mutex.o \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Robin.o \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Semaphore.o \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_System.o \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Task.o \
./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Time.o 


# Each subdirectory must supply rules for building sources it contributes
libraries/rtos/rtx/TARGET_CORTEX_M/%.o: ../libraries/rtos/rtx/TARGET_CORTEX_M/%.c libraries/rtos/rtx/TARGET_CORTEX_M/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -D__CODE_RED -DCPP_USE_HEAP -DTARGET_LPC1549 -DTARGET_M3 -DTARGET_CORTEX_M -DTARGET_NXP -DTARGET_LPC15XX -DTOOLCHAIN_GCC_CR -DTOOLCHAIN_GCC -D__CORTEX_M3 -DARM_MATH_CM3 -D__NEWLIB__ -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\hal" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\api" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\cmsis" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\common" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtos" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtx\TARGET_CORTEX_M" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtx\TARGET_CORTEX_M\TARGET_M3" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\rtos\rtx\TARGET_CORTEX_M\TARGET_M3\TOOLCHAIN_GCC" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\fs\fat" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\fs\fat\ChaN" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\fs\sd" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\cmsis\TARGET_NXP\TARGET_LPC15XX" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\cmsis\TARGET_NXP\TARGET_LPC15XX\TOOLCHAIN_GCC_CR" -I"C:\Users\aarsh\Desktop\isc\ElecOnboarding23\Firmware\mbed\libraries\mbed\targets\hal\TARGET_NXP\TARGET_LPC15XX" -O3 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-libraries-2f-rtos-2f-rtx-2f-TARGET_CORTEX_M

clean-libraries-2f-rtos-2f-rtx-2f-TARGET_CORTEX_M:
	-$(RM) ./libraries/rtos/rtx/TARGET_CORTEX_M/HAL_CM.d ./libraries/rtos/rtx/TARGET_CORTEX_M/HAL_CM.o ./libraries/rtos/rtx/TARGET_CORTEX_M/RTX_Conf_CM.d ./libraries/rtos/rtx/TARGET_CORTEX_M/RTX_Conf_CM.o ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_CMSIS.d ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_CMSIS.o ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Event.d ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Event.o ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_List.d ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_List.o ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Mailbox.d ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Mailbox.o ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_MemBox.d ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_MemBox.o ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Mutex.d ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Mutex.o ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Robin.d ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Robin.o ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Semaphore.d ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Semaphore.o ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_System.d ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_System.o ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Task.d ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Task.o ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Time.d ./libraries/rtos/rtx/TARGET_CORTEX_M/rt_Time.o

.PHONY: clean-libraries-2f-rtos-2f-rtx-2f-TARGET_CORTEX_M

