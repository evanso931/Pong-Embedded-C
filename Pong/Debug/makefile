################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := clean

# All of the sources participating in the build are defined here
-include sources.mk
-include Sound/subdir.mk
-include SevenSegDisplay/subdir.mk
-include PrivateTimer/subdir.mk
-include LCDEngine/subdir.mk
-include Interrupts/subdir.mk
-include Image/subdir.mk
-include GameEngine/subdir.mk
-include Drivers/VFP_Enable/subdir.mk
-include Drivers/HPS_usleep/subdir.mk
-include Drivers/HPS_IRQ/subdir.mk
-include Drivers/HPS_I2C/subdir.mk
-include Drivers/FatFS/hwlib/subdir.mk
-include Drivers/FatFS/subdir.mk
-include Drivers/DE1SoC_WM8731/subdir.mk
-include Drivers/DE1SoC_Servo/subdir.mk
-include Drivers/DE1SoC_Mandelbrot/subdir.mk
-include Drivers/DE1SoC_LT24/subdir.mk
-include Drivers/BasicFont/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(SX_UPPER_DEPS)),)
-include $(SX_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Pong.axf

# Tool invocations
Pong.axf: $(OBJS) C:\Users\Administrator\Workspace\ELEC5620M-Resources\ScatterFiles\DDRRomRamIRQ.scat $(USER_OBJS) $(LIBS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker 5'
	armlink --cpu=Cortex-A9.no_neon --entry=__main --scatter="C:\Users\Administrator\Workspace\ELEC5620M-Resources\ScatterFiles\DDRRomRamIRQ.scat" --info=sizes -o "Pong.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS) $(S_DEPS) $(C_DEPS) $(CC_DEPS) $(SX_DEPS) $(ASM_UPPER_DEPS) $(C++_DEPS) $(EXECUTABLES) $(CXX_DEPS) $(OBJS) $(SX_UPPER_DEPS) $(ASM_DEPS) $(S_UPPER_DEPS) $(CPP_DEPS) Pong.axf 
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
