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


BUILD_ARTIFACT_NAME := project_1
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: project_1.axf

dependents:
	-cd C:/Users/Yuan\ Quan/ISC/Onboarding/ElecOnboarding24/Firmware/mbed/LPC15x9 && $(MAKE) clean all
	-cd C:/Users/Yuan\ Quan/ISC/Onboarding/ElecOnboarding24/Firmware/common/LPC15x9 && $(MAKE) clean all

# Tool invocations
project_1.axf: $(OBJS) $(USER_OBJS) C:/Users/Yuan\ Quan/ISC/Onboarding/ElecOnboarding24/Firmware/mbed/LPC15x9/libmbed.a C:/Users/Yuan\ Quan/ISC/Onboarding/ElecOnboarding24/Firmware/common/LPC15x9/libcommon.a makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU C++ Linker'
	arm-none-eabi-c++ -nostdlib -L"C:\Users\Yuan Quan\ISC\Onboarding\ElecOnboarding24\Firmware\mbed\LPC15x9" -L"C:\Users\Yuan Quan\ISC\Onboarding\ElecOnboarding24\Firmware\common\LPC15x9" -Xlinker -Map="project_1.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "LPC15x9.ld" -L "../../mbed/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC15XX/TOOLCHAIN_GCC_CR" -o "project_1.axf" $(OBJS) $(USER_OBJS) $(LIBS) -lcommon -lmbed
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) project_1.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "project_1.axf" ; arm-none-eabi-nm -C --size-sort -r "project_1.axf" > project_1.sym ; # arm-none-eabi-objcopy -O binary "project_1.axf" "project_1.bin" ; checksum -p LPC1519 -d "project_1.bin"
	-@echo ' '

.PHONY: all clean dependents main-build post-build
C:/Users/Yuan\ Quan/ISC/Onboarding/ElecOnboarding24/Firmware/mbed/LPC15x9/libmbed.a:
C:/Users/Yuan\ Quan/ISC/Onboarding/ElecOnboarding24/Firmware/common/LPC15x9/libcommon.a:

-include ../makefile.targets
