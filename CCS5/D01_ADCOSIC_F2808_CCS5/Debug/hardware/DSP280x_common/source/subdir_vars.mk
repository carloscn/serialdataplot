################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../hardware/DSP280x_common/source/DSP280x_CodeStartBranch.asm \
../hardware/DSP280x_common/source/DSP280x_DBGIER.asm \
../hardware/DSP280x_common/source/DSP280x_DisInt.asm \
../hardware/DSP280x_common/source/DSP280x_usDelay.asm 

C_SRCS += \
../hardware/DSP280x_common/source/DSP280x_Adc.c \
../hardware/DSP280x_common/source/DSP280x_CpuTimers.c \
../hardware/DSP280x_common/source/DSP280x_DefaultIsr.c \
../hardware/DSP280x_common/source/DSP280x_ECan.c \
../hardware/DSP280x_common/source/DSP280x_ECap.c \
../hardware/DSP280x_common/source/DSP280x_EPwm.c \
../hardware/DSP280x_common/source/DSP280x_EQep.c \
../hardware/DSP280x_common/source/DSP280x_Gpio.c \
../hardware/DSP280x_common/source/DSP280x_I2C.c \
../hardware/DSP280x_common/source/DSP280x_MemCopy.c \
../hardware/DSP280x_common/source/DSP280x_PieCtrl.c \
../hardware/DSP280x_common/source/DSP280x_PieVect.c \
../hardware/DSP280x_common/source/DSP280x_Sci.c \
../hardware/DSP280x_common/source/DSP280x_Spi.c \
../hardware/DSP280x_common/source/DSP280x_SysCtrl.c 

C_DEPS += \
./hardware/DSP280x_common/source/DSP280x_Adc.d \
./hardware/DSP280x_common/source/DSP280x_CpuTimers.d \
./hardware/DSP280x_common/source/DSP280x_DefaultIsr.d \
./hardware/DSP280x_common/source/DSP280x_ECan.d \
./hardware/DSP280x_common/source/DSP280x_ECap.d \
./hardware/DSP280x_common/source/DSP280x_EPwm.d \
./hardware/DSP280x_common/source/DSP280x_EQep.d \
./hardware/DSP280x_common/source/DSP280x_Gpio.d \
./hardware/DSP280x_common/source/DSP280x_I2C.d \
./hardware/DSP280x_common/source/DSP280x_MemCopy.d \
./hardware/DSP280x_common/source/DSP280x_PieCtrl.d \
./hardware/DSP280x_common/source/DSP280x_PieVect.d \
./hardware/DSP280x_common/source/DSP280x_Sci.d \
./hardware/DSP280x_common/source/DSP280x_Spi.d \
./hardware/DSP280x_common/source/DSP280x_SysCtrl.d 

OBJS += \
./hardware/DSP280x_common/source/DSP280x_Adc.obj \
./hardware/DSP280x_common/source/DSP280x_CodeStartBranch.obj \
./hardware/DSP280x_common/source/DSP280x_CpuTimers.obj \
./hardware/DSP280x_common/source/DSP280x_DBGIER.obj \
./hardware/DSP280x_common/source/DSP280x_DefaultIsr.obj \
./hardware/DSP280x_common/source/DSP280x_DisInt.obj \
./hardware/DSP280x_common/source/DSP280x_ECan.obj \
./hardware/DSP280x_common/source/DSP280x_ECap.obj \
./hardware/DSP280x_common/source/DSP280x_EPwm.obj \
./hardware/DSP280x_common/source/DSP280x_EQep.obj \
./hardware/DSP280x_common/source/DSP280x_Gpio.obj \
./hardware/DSP280x_common/source/DSP280x_I2C.obj \
./hardware/DSP280x_common/source/DSP280x_MemCopy.obj \
./hardware/DSP280x_common/source/DSP280x_PieCtrl.obj \
./hardware/DSP280x_common/source/DSP280x_PieVect.obj \
./hardware/DSP280x_common/source/DSP280x_Sci.obj \
./hardware/DSP280x_common/source/DSP280x_Spi.obj \
./hardware/DSP280x_common/source/DSP280x_SysCtrl.obj \
./hardware/DSP280x_common/source/DSP280x_usDelay.obj 

ASM_DEPS += \
./hardware/DSP280x_common/source/DSP280x_CodeStartBranch.d \
./hardware/DSP280x_common/source/DSP280x_DBGIER.d \
./hardware/DSP280x_common/source/DSP280x_DisInt.d \
./hardware/DSP280x_common/source/DSP280x_usDelay.d 

OBJS__QUOTED += \
"hardware\DSP280x_common\source\DSP280x_Adc.obj" \
"hardware\DSP280x_common\source\DSP280x_CodeStartBranch.obj" \
"hardware\DSP280x_common\source\DSP280x_CpuTimers.obj" \
"hardware\DSP280x_common\source\DSP280x_DBGIER.obj" \
"hardware\DSP280x_common\source\DSP280x_DefaultIsr.obj" \
"hardware\DSP280x_common\source\DSP280x_DisInt.obj" \
"hardware\DSP280x_common\source\DSP280x_ECan.obj" \
"hardware\DSP280x_common\source\DSP280x_ECap.obj" \
"hardware\DSP280x_common\source\DSP280x_EPwm.obj" \
"hardware\DSP280x_common\source\DSP280x_EQep.obj" \
"hardware\DSP280x_common\source\DSP280x_Gpio.obj" \
"hardware\DSP280x_common\source\DSP280x_I2C.obj" \
"hardware\DSP280x_common\source\DSP280x_MemCopy.obj" \
"hardware\DSP280x_common\source\DSP280x_PieCtrl.obj" \
"hardware\DSP280x_common\source\DSP280x_PieVect.obj" \
"hardware\DSP280x_common\source\DSP280x_Sci.obj" \
"hardware\DSP280x_common\source\DSP280x_Spi.obj" \
"hardware\DSP280x_common\source\DSP280x_SysCtrl.obj" \
"hardware\DSP280x_common\source\DSP280x_usDelay.obj" 

C_DEPS__QUOTED += \
"hardware\DSP280x_common\source\DSP280x_Adc.d" \
"hardware\DSP280x_common\source\DSP280x_CpuTimers.d" \
"hardware\DSP280x_common\source\DSP280x_DefaultIsr.d" \
"hardware\DSP280x_common\source\DSP280x_ECan.d" \
"hardware\DSP280x_common\source\DSP280x_ECap.d" \
"hardware\DSP280x_common\source\DSP280x_EPwm.d" \
"hardware\DSP280x_common\source\DSP280x_EQep.d" \
"hardware\DSP280x_common\source\DSP280x_Gpio.d" \
"hardware\DSP280x_common\source\DSP280x_I2C.d" \
"hardware\DSP280x_common\source\DSP280x_MemCopy.d" \
"hardware\DSP280x_common\source\DSP280x_PieCtrl.d" \
"hardware\DSP280x_common\source\DSP280x_PieVect.d" \
"hardware\DSP280x_common\source\DSP280x_Sci.d" \
"hardware\DSP280x_common\source\DSP280x_Spi.d" \
"hardware\DSP280x_common\source\DSP280x_SysCtrl.d" 

ASM_DEPS__QUOTED += \
"hardware\DSP280x_common\source\DSP280x_CodeStartBranch.d" \
"hardware\DSP280x_common\source\DSP280x_DBGIER.d" \
"hardware\DSP280x_common\source\DSP280x_DisInt.d" \
"hardware\DSP280x_common\source\DSP280x_usDelay.d" 

C_SRCS__QUOTED += \
"../hardware/DSP280x_common/source/DSP280x_Adc.c" \
"../hardware/DSP280x_common/source/DSP280x_CpuTimers.c" \
"../hardware/DSP280x_common/source/DSP280x_DefaultIsr.c" \
"../hardware/DSP280x_common/source/DSP280x_ECan.c" \
"../hardware/DSP280x_common/source/DSP280x_ECap.c" \
"../hardware/DSP280x_common/source/DSP280x_EPwm.c" \
"../hardware/DSP280x_common/source/DSP280x_EQep.c" \
"../hardware/DSP280x_common/source/DSP280x_Gpio.c" \
"../hardware/DSP280x_common/source/DSP280x_I2C.c" \
"../hardware/DSP280x_common/source/DSP280x_MemCopy.c" \
"../hardware/DSP280x_common/source/DSP280x_PieCtrl.c" \
"../hardware/DSP280x_common/source/DSP280x_PieVect.c" \
"../hardware/DSP280x_common/source/DSP280x_Sci.c" \
"../hardware/DSP280x_common/source/DSP280x_Spi.c" \
"../hardware/DSP280x_common/source/DSP280x_SysCtrl.c" 

ASM_SRCS__QUOTED += \
"../hardware/DSP280x_common/source/DSP280x_CodeStartBranch.asm" \
"../hardware/DSP280x_common/source/DSP280x_DBGIER.asm" \
"../hardware/DSP280x_common/source/DSP280x_DisInt.asm" \
"../hardware/DSP280x_common/source/DSP280x_usDelay.asm" 


