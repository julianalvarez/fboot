################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../arch/arm/rt1064/mach-cansteer_v3/cansteer_v3.c 

C_DEPS += \
./arch/arm/rt1064/mach-cansteer_v3/cansteer_v3.d 

OBJS += \
./arch/arm/rt1064/mach-cansteer_v3/cansteer_v3.o 


# Each subdirectory must supply rules for building sources it contributes
arch/arm/rt1064/mach-cansteer_v3/%.o: ../arch/arm/rt1064/mach-cansteer_v3/%.c arch/arm/rt1064/mach-cansteer_v3/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MIMXRT1064DVL6A -DCPU_MIMXRT1064DVL6A_cm7 -DSDK_OS_BAREMETAL -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DMACH_IOHUB_SPIFI=1 -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\fboot\board" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\fboot\arch\arm\common_package\include" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\fboot\include" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\fboot\source" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\fboot\drivers" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\fboot\xip" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\fboot\device" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\fboot\CMSIS" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\fboot\component\serial_manager" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\fboot\component\uart" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\fboot\utilities" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\fboot\component\lists" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\CSP_rt1064\CMSIS" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\CSP_rt1064\source" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\CSP_rt1064\utilities" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\CSP_rt1064\drivers" -I"C:\Users\PLANTIUM\Documents\MCUXpressoIDE_11.8.0_1165\workspace\CSP_rt1064\board" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-arch-2f-arm-2f-rt1064-2f-mach-2d-cansteer_v3

clean-arch-2f-arm-2f-rt1064-2f-mach-2d-cansteer_v3:
	-$(RM) ./arch/arm/rt1064/mach-cansteer_v3/cansteer_v3.d ./arch/arm/rt1064/mach-cansteer_v3/cansteer_v3.o

.PHONY: clean-arch-2f-arm-2f-rt1064-2f-mach-2d-cansteer_v3

