################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../rtps/src/entities/Domain.cpp \
../rtps/src/entities/Participant.cpp \
../rtps/src/entities/StatelessReader.cpp 

OBJS += \
./rtps/src/entities/Domain.o \
./rtps/src/entities/Participant.o \
./rtps/src/entities/StatelessReader.o 

CPP_DEPS += \
./rtps/src/entities/Domain.d \
./rtps/src/entities/Participant.d \
./rtps/src/entities/StatelessReader.d 


# Each subdirectory must supply rules for building sources it contributes
rtps/src/entities/Domain.o: ../rtps/src/entities/Domain.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Inc -I../Middlewares/Third_Party/LwIP/system -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ertps/include -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/ertps/thirdparty/Micro-CDR/include -I../Middlewares/Third_Party/LwIP/src/include/lwip -I/Users/davidk/Documents/Embedded/embedded-rtps-stm32/rtps/include -I"/Users/davidk/Documents/Embedded/embedded-rtps-stm32/rtps/include" -O3 -ffunction-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fexceptions  -fstack-usage -std=gnu++11 -fstack-usage -MMD -MP -MF"rtps/src/entities/Domain.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
rtps/src/entities/Participant.o: ../rtps/src/entities/Participant.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Inc -I../Middlewares/Third_Party/LwIP/system -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ertps/include -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/ertps/thirdparty/Micro-CDR/include -I../Middlewares/Third_Party/LwIP/src/include/lwip -I/Users/davidk/Documents/Embedded/embedded-rtps-stm32/rtps/include -I"/Users/davidk/Documents/Embedded/embedded-rtps-stm32/rtps/include" -O3 -ffunction-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fexceptions  -fstack-usage -std=gnu++11 -fstack-usage -MMD -MP -MF"rtps/src/entities/Participant.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
rtps/src/entities/StatelessReader.o: ../rtps/src/entities/StatelessReader.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Inc -I../Middlewares/Third_Party/LwIP/system -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ertps/include -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/ertps/thirdparty/Micro-CDR/include -I../Middlewares/Third_Party/LwIP/src/include/lwip -I/Users/davidk/Documents/Embedded/embedded-rtps-stm32/rtps/include -I"/Users/davidk/Documents/Embedded/embedded-rtps-stm32/rtps/include" -O3 -ffunction-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fexceptions  -fstack-usage -std=gnu++11 -fstack-usage -MMD -MP -MF"rtps/src/entities/StatelessReader.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

