################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ADXL372/adxl372_example.c \
../src/ADXL372/adxl372_spi_drv.c 

SRC_OBJS += \
./src/ADXL372/adxl372_example.o \
./src/ADXL372/adxl372_spi_drv.o 

C_DEPS += \
./src/ADXL372/adxl372_example.d \
./src/ADXL372/adxl372_spi_drv.d 


# Each subdirectory must supply rules for building sources it contributes
src/ADXL372/%.o: ../src/ADXL372/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore GCC ARM Embedded C Compiler'
	arm-none-eabi-gcc -O2 -ffunction-sections -fdata-sections -DCORE0 -DNDEBUG -D__ADUCM302x__ -D_RTE_ -D__ADUCM3029__ -D__SILICON_REVISION__=0x100 -I"C:\CCES\ADuCM3029_Asset_Health\system" -I"C:/CCES/ADuCM3029_Asset_Health/src/BLE/transport" -I"C:/CCES/ADuCM3029_Asset_Health/src/BLE/radio" -I"C:/CCES/ADuCM3029_Asset_Health/src/Application" -I"C:/CCES/ADuCM3029_Asset_Health/src/ADXL372" -I"C:/Analog Devices/CrossCore Embedded Studio 2.6.0/ARM/packs/ARM/CMSIS/5.0.1/CMSIS/Include" -I"C:/Analog Devices/CrossCore Embedded Studio 2.6.0/ARM/packs/AnalogDevices/ADuCM302x_DFP/2.0.0/Include" -I"C:/Analog Devices/CrossCore Embedded Studio 2.6.0/ARM/packs/AnalogDevices/EVAL-ADICUP3029_BSP/1.0.0/Include" -I"C:/Analog Devices/CrossCore Embedded Studio 2.6.0/ARM/packs/AnalogDevices/EVAL-ADICUP3029_BSP/1.0.0/Include/ble" -I"C:\CCES\ADuCM3029_Asset_Health/RTE" -I"C:\CCES\ADuCM3029_Asset_Health/RTE/Board_Support" -I"C:\CCES\ADuCM3029_Asset_Health/RTE/Device/ADuCM3029" -Wall -c -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


