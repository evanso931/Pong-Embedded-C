################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Image/Pong.c 

C_DEPS += \
./Image/Pong.d 

OBJS += \
./Image/Pong.o 


# Each subdirectory must supply rules for building sources it contributes
Image/%.o: ../Image/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc --cpu=Cortex-A9.no_neon --apcs=/hardfp --arm -DHARDWARE_OPTIMISED -I"C:\Users\Administrator\Workspace\ELEC5620M-Resources\Drivers" -I"C:\Users\Administrator\Workspace\ELEC5620M-Mini-Project-evanso931\Pong\LCDEngine" -O0 -g --md --depend_format=unix_escaped --no_depend_system_headers --depend_dir="Image" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


