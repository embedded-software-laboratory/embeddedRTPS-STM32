################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rtps/thirdparty/Micro-CDR/src/c/common.c 

OBJS += \
./rtps/thirdparty/Micro-CDR/src/c/common.o 

C_DEPS += \
./rtps/thirdparty/Micro-CDR/src/c/common.d 


# Each subdirectory must supply rules for building sources it contributes
rtps/thirdparty/Micro-CDR/src/c/common.o: ../rtps/thirdparty/Micro-CDR/src/c/common.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Inc -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../Drivers/CMSIS/Include -I"/Users/davidk/Documents/Embedded/embedded-rtps/embeddedrtps-stm32/stm32/rtps/include" -I"/Users/davidk/Documents/Embedded/embedded-rtps/embeddedrtps-stm32/stm32/rtps/thirdparty/Micro-CDR/include" -Og -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"rtps/thirdparty/Micro-CDR/src/c/common.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

