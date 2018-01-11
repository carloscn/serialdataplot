################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/opt/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./source/Main.obj" \
"./hardware/DSP280x_headers/source/DSP280x_GlobalVariableDefs.obj" \
"./hardware/DSP280x_common/source/DSP280x_Adc.obj" \
"./hardware/DSP280x_common/source/DSP280x_CodeStartBranch.obj" \
"./hardware/DSP280x_common/source/DSP280x_CpuTimers.obj" \
"./hardware/DSP280x_common/source/DSP280x_DBGIER.obj" \
"./hardware/DSP280x_common/source/DSP280x_DefaultIsr.obj" \
"./hardware/DSP280x_common/source/DSP280x_DisInt.obj" \
"./hardware/DSP280x_common/source/DSP280x_ECan.obj" \
"./hardware/DSP280x_common/source/DSP280x_ECap.obj" \
"./hardware/DSP280x_common/source/DSP280x_EPwm.obj" \
"./hardware/DSP280x_common/source/DSP280x_EQep.obj" \
"./hardware/DSP280x_common/source/DSP280x_Gpio.obj" \
"./hardware/DSP280x_common/source/DSP280x_I2C.obj" \
"./hardware/DSP280x_common/source/DSP280x_MemCopy.obj" \
"./hardware/DSP280x_common/source/DSP280x_PieCtrl.obj" \
"./hardware/DSP280x_common/source/DSP280x_PieVect.obj" \
"./hardware/DSP280x_common/source/DSP280x_Sci.obj" \
"./hardware/DSP280x_common/source/DSP280x_Spi.obj" \
"./hardware/DSP280x_common/source/DSP280x_SysCtrl.obj" \
"./hardware/DSP280x_common/source/DSP280x_usDelay.obj" \
"../2808_RAM_lnk.cmd" \
"../DSP280x_Headers_nonBIOS.cmd" \
"../hardware/DSP280x_common/lib/IQmath.lib" \
"../hardware/DSP280x_common/lib/SFO_TI_Build.lib" \
"../hardware/DSP280x_common/lib/SFO_TI_Build_V5.lib" \
"../hardware/DSP280x_common/lib/SFO_TI_Build_V5B.lib" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include source/subdir_vars.mk
-include hardware/DSP280x_headers/source/subdir_vars.mk
-include hardware/DSP280x_common/source/subdir_vars.mk
-include hardware/DSP280x_common/lib/subdir_vars.mk
-include subdir_rules.mk
-include source/subdir_rules.mk
-include hardware/DSP280x_headers/source/subdir_rules.mk
-include hardware/DSP280x_common/source/subdir_rules.mk
-include hardware/DSP280x_common/lib/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
D01_ADCOSIC_F2808_CCS5.out \

EXE_OUTPUTS__QUOTED += \
"D01_ADCOSIC_F2808_CCS5.out" \


# All Target
all: D01_ADCOSIC_F2808_CCS5.out

# Tool invocations
D01_ADCOSIC_F2808_CCS5.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"D:/opt/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/bin/cl2000" -v28 -ml -mt -g --diag_warning=225 --display_error_number --diag_wrap=off -z -m"D01_ADCOSIC_F2808_CCS5.map" --stack_size=0x300 --warn_sections -i"D:/opt/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/lib" -i"D:/opt/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="D01_ADCOSIC_F2808_CCS5_linkInfo.xml" --rom_model -o "D01_ADCOSIC_F2808_CCS5.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "source\Main.pp" "hardware\DSP280x_headers\source\DSP280x_GlobalVariableDefs.pp" "hardware\DSP280x_common\source\DSP280x_Adc.pp" "hardware\DSP280x_common\source\DSP280x_CpuTimers.pp" "hardware\DSP280x_common\source\DSP280x_DefaultIsr.pp" "hardware\DSP280x_common\source\DSP280x_ECan.pp" "hardware\DSP280x_common\source\DSP280x_ECap.pp" "hardware\DSP280x_common\source\DSP280x_EPwm.pp" "hardware\DSP280x_common\source\DSP280x_EQep.pp" "hardware\DSP280x_common\source\DSP280x_Gpio.pp" "hardware\DSP280x_common\source\DSP280x_I2C.pp" "hardware\DSP280x_common\source\DSP280x_MemCopy.pp" "hardware\DSP280x_common\source\DSP280x_PieCtrl.pp" "hardware\DSP280x_common\source\DSP280x_PieVect.pp" "hardware\DSP280x_common\source\DSP280x_Sci.pp" "hardware\DSP280x_common\source\DSP280x_Spi.pp" "hardware\DSP280x_common\source\DSP280x_SysCtrl.pp" 
	-$(RM) "source\Main.obj" "hardware\DSP280x_headers\source\DSP280x_GlobalVariableDefs.obj" "hardware\DSP280x_common\source\DSP280x_Adc.obj" "hardware\DSP280x_common\source\DSP280x_CodeStartBranch.obj" "hardware\DSP280x_common\source\DSP280x_CpuTimers.obj" "hardware\DSP280x_common\source\DSP280x_DBGIER.obj" "hardware\DSP280x_common\source\DSP280x_DefaultIsr.obj" "hardware\DSP280x_common\source\DSP280x_DisInt.obj" "hardware\DSP280x_common\source\DSP280x_ECan.obj" "hardware\DSP280x_common\source\DSP280x_ECap.obj" "hardware\DSP280x_common\source\DSP280x_EPwm.obj" "hardware\DSP280x_common\source\DSP280x_EQep.obj" "hardware\DSP280x_common\source\DSP280x_Gpio.obj" "hardware\DSP280x_common\source\DSP280x_I2C.obj" "hardware\DSP280x_common\source\DSP280x_MemCopy.obj" "hardware\DSP280x_common\source\DSP280x_PieCtrl.obj" "hardware\DSP280x_common\source\DSP280x_PieVect.obj" "hardware\DSP280x_common\source\DSP280x_Sci.obj" "hardware\DSP280x_common\source\DSP280x_Spi.obj" "hardware\DSP280x_common\source\DSP280x_SysCtrl.obj" 
	-$(RM) "hardware\DSP280x_common\source\DSP280x_usDelay.obj" 
	-$(RM) "hardware\DSP280x_common\source\DSP280x_CodeStartBranch.pp" "hardware\DSP280x_common\source\DSP280x_DBGIER.pp" "hardware\DSP280x_common\source\DSP280x_DisInt.pp" "hardware\DSP280x_common\source\DSP280x_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

