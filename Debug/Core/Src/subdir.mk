################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/address.c \
../Core/Src/cJSON.c \
../Core/Src/data.c \
../Core/Src/error_handler.c \
../Core/Src/gsm.c \
../Core/Src/main.c \
../Core/Src/modbus.c \
../Core/Src/modbus_crc.c \
../Core/Src/rtc.c \
../Core/Src/sms.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/sys_init.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/uart.c 

OBJS += \
./Core/Src/address.o \
./Core/Src/cJSON.o \
./Core/Src/data.o \
./Core/Src/error_handler.o \
./Core/Src/gsm.o \
./Core/Src/main.o \
./Core/Src/modbus.o \
./Core/Src/modbus_crc.o \
./Core/Src/rtc.o \
./Core/Src/sms.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/sys_init.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/uart.o 

C_DEPS += \
./Core/Src/address.d \
./Core/Src/cJSON.d \
./Core/Src/data.d \
./Core/Src/error_handler.d \
./Core/Src/gsm.d \
./Core/Src/main.d \
./Core/Src/modbus.d \
./Core/Src/modbus_crc.d \
./Core/Src/rtc.d \
./Core/Src/sms.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/sys_init.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/address.cyclo ./Core/Src/address.d ./Core/Src/address.o ./Core/Src/address.su ./Core/Src/cJSON.cyclo ./Core/Src/cJSON.d ./Core/Src/cJSON.o ./Core/Src/cJSON.su ./Core/Src/data.cyclo ./Core/Src/data.d ./Core/Src/data.o ./Core/Src/data.su ./Core/Src/error_handler.cyclo ./Core/Src/error_handler.d ./Core/Src/error_handler.o ./Core/Src/error_handler.su ./Core/Src/gsm.cyclo ./Core/Src/gsm.d ./Core/Src/gsm.o ./Core/Src/gsm.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/modbus.cyclo ./Core/Src/modbus.d ./Core/Src/modbus.o ./Core/Src/modbus.su ./Core/Src/modbus_crc.cyclo ./Core/Src/modbus_crc.d ./Core/Src/modbus_crc.o ./Core/Src/modbus_crc.su ./Core/Src/rtc.cyclo ./Core/Src/rtc.d ./Core/Src/rtc.o ./Core/Src/rtc.su ./Core/Src/sms.cyclo ./Core/Src/sms.d ./Core/Src/sms.o ./Core/Src/sms.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/sys_init.cyclo ./Core/Src/sys_init.d ./Core/Src/sys_init.o ./Core/Src/sys_init.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/uart.cyclo ./Core/Src/uart.d ./Core/Src/uart.o ./Core/Src/uart.su

.PHONY: clean-Core-2f-Src

