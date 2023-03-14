################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libs/Src/DS3231.c \
../Libs/Src/Display.c \
../Libs/Src/Menu.c \
../Libs/Src/Rotary_Encoder.c \
../Libs/Src/button.c 

OBJS += \
./Libs/Src/DS3231.o \
./Libs/Src/Display.o \
./Libs/Src/Menu.o \
./Libs/Src/Rotary_Encoder.o \
./Libs/Src/button.o 

C_DEPS += \
./Libs/Src/DS3231.d \
./Libs/Src/Display.d \
./Libs/Src/Menu.d \
./Libs/Src/Rotary_Encoder.d \
./Libs/Src/button.d 


# Each subdirectory must supply rules for building sources it contributes
Libs/Src/%.o Libs/Src/%.su: ../Libs/Src/%.c Libs/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Data/Projects/HPBD/Software/Libs/Inc" -I"C:/Data/Projects/HPBD/Software/Libs/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Libs-2f-Src

clean-Libs-2f-Src:
	-$(RM) ./Libs/Src/DS3231.d ./Libs/Src/DS3231.o ./Libs/Src/DS3231.su ./Libs/Src/Display.d ./Libs/Src/Display.o ./Libs/Src/Display.su ./Libs/Src/Menu.d ./Libs/Src/Menu.o ./Libs/Src/Menu.su ./Libs/Src/Rotary_Encoder.d ./Libs/Src/Rotary_Encoder.o ./Libs/Src/Rotary_Encoder.su ./Libs/Src/button.d ./Libs/Src/button.o ./Libs/Src/button.su

.PHONY: clean-Libs-2f-Src

