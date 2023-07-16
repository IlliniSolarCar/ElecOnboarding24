################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := blinky
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: blinky.axf

# Tool invocations
blinky.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU C++ Linker'
	arm-none-eabi-c++ -nostdlib -L"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/CMSIS_CORE_LPC17xx/Debug" -L"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/common/LPC1768" -L"/home/zonedbro/Code/solarcar/firmware/FW-WHEEL/mbed/LPC1768" -Xlinker -Map="blinky.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T blinky_Debug.ld -o "blinky.axf" $(OBJS) $(USER_OBJS) $(LIBS) -lCMSIS_CORE_LPC17xx -lcommon -lmbed
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) blinky.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "blinky.axf"; # arm-none-eabi-objcopy -v -O binary "blinky.axf" "blinky.bin" ; # checksum -p LPC1768 -d "blinky.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
