################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Application/adsap_intf_api.c \
../src/Application/adsap_main.c 

SRC_OBJS += \
./src/Application/adsap_intf_api.o \
./src/Application/adsap_main.o 

C_DEPS += \
./src/Application/adsap_intf_api.d \
./src/Application/adsap_main.d 


# Each subdirectory must supply rules for building sources it contributes
src/Application/%.o: ../src/Application/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore GCC ARM Embedded C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -ffunction-sections -fdata-sections -DCORE0 -D_DEBUG -D__ADUCM302x__ -DEVAL_ADICUP3029 -D_RTE_ -D__ADUCM3029__ -D__SILICON_REVISION__=0x100 @includes-f3c16c2f1835f0fe1601a2bf6aadaf10.txt -Wall -c -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


