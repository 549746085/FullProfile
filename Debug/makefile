################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := ${ComSpec}

-include ../makefile.init

RM := clean

# All of the sources participating in the build are defined here
-include sources.mk
-include system/pinmux/GeneratedSources/subdir.mk
-include system/subdir.mk
-include src/Application/subdir.mk
-include src/ADXL372/subdir.mk
-include src/subdir.mk
-include RTE/Device/ADuCM3029/subdir.mk
-include RTE/Board_Support/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
OBJS := $(SRC_OBJS)
# Quote makefile variable : OBJS 
OBJS := $(subst \ ,@, $(OBJS))
OBJS := $(foreach var, $(OBJS), "$(subst @, ,$(var))")
# Quote makefile variable : C_DEPS 
C_DEPS := $(subst \ ,@, $(C_DEPS))
C_DEPS := $(foreach var, $(C_DEPS), "$(subst @, ,$(var))")

# All Target
all: ADXL372_Instant_On_Mode

# Tool invocations
ADXL372_Instant_On_Mode: $(USER_OBJS) $(SRC_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: CrossCore GCC ARM Embedded C Linker'
	arm-none-eabi-gcc -T"C:\Users\jwang2\OneDrive - Analog Devices, Inc\Documents\GitHub\ADXL372_Instant_On_Mode\ADXL372_Instant_On_Mode/RTE/Device/ADuCM3029/ADuCM3029.ld" -Wl,--gc-sections -mcpu=cortex-m3 -mthumb -specs=nosys.specs -o  "ADXL372_Instant_On_Mode" @input-file.txt -lm
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) ADXL372_Instant_On_Mode
	-@echo ' '

post-build:
	-arm-none-eabi-objcopy -O ihex ADXL372_Instant_On_Mode ADXL372_Instant_On_Mode.hex
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
