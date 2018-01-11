################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
source/Main.obj: ../source/Main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ProgramSoftware/CodeComposerStudio_v7/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --include_path="C:/ProgramSoftware/CodeComposerStudio_v7/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --include_path="../include" --include_path="../hardware/DSP280x_common/include" --include_path="../hardware/DSP280x_headers/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/Main.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


