################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/uart.c 

OBJS += \
./Inc/uart.o 

C_DEPS += \
./Inc/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/%.o Inc/%.su Inc/%.cyclo: ../Inc/%.c Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F415RGTx -DSTM32F4 -DSTM32F415xx -c -I../Inc -I"C:/Users/DELL/Desktop/stm32/stm32f4 bear metal/Chip_headers/CMSIS/Include" -I"C:/Users/DELL/Desktop/stm32/stm32f4 bear metal/Chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc

clean-Inc:
	-$(RM) ./Inc/uart.cyclo ./Inc/uart.d ./Inc/uart.o ./Inc/uart.su

.PHONY: clean-Inc

