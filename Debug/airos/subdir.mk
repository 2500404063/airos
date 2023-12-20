################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../airos/airos_queue.c \
../airos/airos_task.c 

OBJS += \
./airos/airos_queue.o \
./airos/airos_task.o 

C_DEPS += \
./airos/airos_queue.d \
./airos/airos_task.d 


# Each subdirectory must supply rules for building sources it contributes
airos/%.o airos/%.su airos/%.cyclo: ../airos/%.c airos/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/25004/Desktop/airos_main/airos_main/airos" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-airos

clean-airos:
	-$(RM) ./airos/airos_queue.cyclo ./airos/airos_queue.d ./airos/airos_queue.o ./airos/airos_queue.su ./airos/airos_task.cyclo ./airos/airos_task.d ./airos/airos_task.o ./airos/airos_task.su

.PHONY: clean-airos

