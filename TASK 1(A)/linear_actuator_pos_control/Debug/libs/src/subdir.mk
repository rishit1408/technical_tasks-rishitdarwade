################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libs/src/adc.c \
../libs/src/pid.c \
../libs/src/system_init.c \
../libs/src/timer.c 

OBJS += \
./libs/src/adc.o \
./libs/src/pid.o \
./libs/src/system_init.o \
./libs/src/timer.o 

C_DEPS += \
./libs/src/adc.d \
./libs/src/pid.d \
./libs/src/system_init.d \
./libs/src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
libs/src/%.o libs/src/%.su libs/src/%.cyclo: ../libs/src/%.c libs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"C:/Users/rishi/STM32CubeIDE/workspace_1.16.0/linear_actuator_pos_control/libs/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/rishi/STM32CubeIDE/workspace_1.16.0/linear_actuator_pos_control/libs" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-libs-2f-src

clean-libs-2f-src:
	-$(RM) ./libs/src/adc.cyclo ./libs/src/adc.d ./libs/src/adc.o ./libs/src/adc.su ./libs/src/pid.cyclo ./libs/src/pid.d ./libs/src/pid.o ./libs/src/pid.su ./libs/src/system_init.cyclo ./libs/src/system_init.d ./libs/src/system_init.o ./libs/src/system_init.su ./libs/src/timer.cyclo ./libs/src/timer.d ./libs/src/timer.o ./libs/src/timer.su

.PHONY: clean-libs-2f-src

