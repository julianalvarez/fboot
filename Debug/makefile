################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include xip/subdir.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include j1939/subdir.mk
-include drivers/mtd/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include component/serial_manager/subdir.mk
-include component/lists/subdir.mk
-include board/subdir.mk
-include arch/arm/rt1064/mach-cansteer_v3/subdir.mk
-include arch/arm/rt1064/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := fboot
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: fboot.axf

# Tool invocations
fboot.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\CSP_rt1064\Debug" -Xlinker -Map="fboot.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -T fboot_Debug.ld -o "fboot.axf" $(OBJS) $(USER_OBJS) $(LIBS) -lCSP_rt1064
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) fboot.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "fboot.axf"; # arm-none-eabi-objcopy -v -O binary "fboot.axf" "fboot.bin" ; # checksum -p MIMXRT1064xxxxA -d "fboot.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
