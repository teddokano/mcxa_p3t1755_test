################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/i3c_master_read_sensor_p3t1755.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/i3c_master_read_sensor_p3t1755.d \
./source/semihost_hardfault.d 

OBJS += \
./source/i3c_master_read_sensor_p3t1755.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MCXA153VLH -DCPU_MCXA153VLH_cm33_nodsp -DPRINTF_FLOAT_ENABLE=1 -DPRINTF_ADVANCED_ENABLE=1 -DMCUXPRESSO_SDK -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=0 -I"/Users/tedd/dev/mcuxpresso/mcxa153/mcxa_p3t1755_test/source" -I"/Users/tedd/dev/mcuxpresso/mcxa153/mcxa_p3t1755_test/drivers" -I"/Users/tedd/dev/mcuxpresso/mcxa153/mcxa_p3t1755_test/component/p3t1755" -I"/Users/tedd/dev/mcuxpresso/mcxa153/mcxa_p3t1755_test/device" -I"/Users/tedd/dev/mcuxpresso/mcxa153/mcxa_p3t1755_test/utilities" -I"/Users/tedd/dev/mcuxpresso/mcxa153/mcxa_p3t1755_test/component/uart" -I"/Users/tedd/dev/mcuxpresso/mcxa153/mcxa_p3t1755_test/component/lists" -I"/Users/tedd/dev/mcuxpresso/mcxa153/mcxa_p3t1755_test/CMSIS" -I"/Users/tedd/dev/mcuxpresso/mcxa153/mcxa_p3t1755_test/board" -I"/Users/tedd/dev/mcuxpresso/mcxa153/mcxa_p3t1755_test/frdmmcxa153/driver_examples/i3c/master_read_sensor_p3t1755" -O0 -fno-common -g3 -gdwarf-4 -mcpu=cortex-m33+nodsp -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33+nodsp -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/i3c_master_read_sensor_p3t1755.d ./source/i3c_master_read_sensor_p3t1755.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

