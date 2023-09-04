################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include libraries/rtos/rtx/TARGET_CORTEX_M/TARGET_M3/TOOLCHAIN_GCC/subdir.mk
-include libraries/rtos/rtx/TARGET_CORTEX_M/subdir.mk
-include libraries/rtos/rtos/subdir.mk
-include libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC15XX/subdir.mk
-include libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC15XX/TOOLCHAIN_GCC_CR/subdir.mk
-include libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC15XX/subdir.mk
-include libraries/mbed/common/subdir.mk
-include libraries/fs/sd/subdir.mk
-include libraries/fs/fat/ChaN/subdir.mk
-include libraries/fs/fat/subdir.mk
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


BUILD_ARTIFACT_NAME := mbed
BUILD_ARTIFACT_EXTENSION := a
BUILD_ARTIFACT_PREFIX := lib
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: libmbed.a

# Tool invocations
libmbed.a: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Archiver'
	arm-none-eabi-ar -r  "libmbed.a" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) libmbed.a
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "libmbed.a" ; # arm-none-eabi-objdump -h -S "libmbed.a" >"libmbed.lss"
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
