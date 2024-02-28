################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_gpio.c \
../drivers/fsl_i3c.c \
../drivers/fsl_inputmux.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_reset.c \
../drivers/fsl_spc.c 

C_DEPS += \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_gpio.d \
./drivers/fsl_i3c.d \
./drivers/fsl_inputmux.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_reset.d \
./drivers/fsl_spc.d 

OBJS += \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_gpio.o \
./drivers/fsl_i3c.o \
./drivers/fsl_inputmux.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_reset.o \
./drivers/fsl_spc.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MCXA153VLH -DCPU_MCXA153VLH_cm33_nodsp -DPRINTF_FLOAT_ENABLE=1 -DPRINTF_ADVANCED_ENABLE=1 -DMCUXPRESSO_SDK -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=0 -I"/Users/tedd/dev/mcuxpresso/mcxa153/mcxa_p3t1755_test/source" -I"/Users/tedd/dev/mcuxpresso/mcxa153/mcxa_p3t1755_test/drivers" -I"/Users/tedd/dev/mcuxpresso/mcxa153/mcxa_p3t1755_test/component/p3t1755" -I"/Users/tedd/dev/mcuxpresso/mcxa153/mcxa_p3t1755_test/device" -I"/Users/tedd/dev/mcuxpresso/mcxa153/mcxa_p3t1755_test/utilities" -I"/Users/tedd/dev/mcuxpresso/mcxa153/mcxa_p3t1755_test/component/uart" -I"/Users/tedd/dev/mcuxpresso/mcxa153/mcxa_p3t1755_test/component/lists" -I"/Users/tedd/dev/mcuxpresso/mcxa153/mcxa_p3t1755_test/CMSIS" -I"/Users/tedd/dev/mcuxpresso/mcxa153/mcxa_p3t1755_test/board" -I"/Users/tedd/dev/mcuxpresso/mcxa153/mcxa_p3t1755_test/frdmmcxa153/driver_examples/i3c/master_read_sensor_p3t1755" -O0 -fno-common -g3 -gdwarf-4 -mcpu=cortex-m33+nodsp -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33+nodsp -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_i3c.d ./drivers/fsl_i3c.o ./drivers/fsl_inputmux.d ./drivers/fsl_inputmux.o ./drivers/fsl_lpuart.d ./drivers/fsl_lpuart.o ./drivers/fsl_reset.d ./drivers/fsl_reset.o ./drivers/fsl_spc.d ./drivers/fsl_spc.o

.PHONY: clean-drivers

