################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Administrator/Workspace/ELEC5620M-Resources/Drivers/VFP_Enable/VFP_Enable.c 

C_DEPS += \
./Drivers/VFP_Enable/VFP_Enable.d 

OBJS += \
./Drivers/VFP_Enable/VFP_Enable.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/VFP_Enable/VFP_Enable.o: C:/Users/Administrator/Workspace/ELEC5620M-Resources/Drivers/VFP_Enable/VFP_Enable.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc --cpu=Cortex-A9.no_neon --apcs=/hardfp --arm -DHARDWARE_OPTIMISED -I"C:\Users\Administrator\Workspace\ELEC5620M-Resources\Drivers" -I"C:\Users\Administrator\Workspace\ELEC5620M-Mini-Project-evanso931\Pong\LCDEngine" -O0 -g --md --depend_format=unix_escaped --no_depend_system_headers --depend_dir="Drivers/VFP_Enable" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


