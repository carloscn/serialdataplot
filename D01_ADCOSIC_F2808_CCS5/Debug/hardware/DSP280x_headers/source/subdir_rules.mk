################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
hardware/DSP280x_headers/source/DSP280x_GlobalVariableDefs.obj: ../hardware/DSP280x_headers/source/DSP280x_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/opt/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/bin/cl2000" -v28 -ml -mt --include_path="D:/opt/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" --include_path="../include" --include_path="../hardware/DSP280x_common/include" --include_path="../hardware/DSP280x_headers/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="hardware/DSP280x_headers/source/DSP280x_GlobalVariableDefs.pp" --obj_directory="hardware/DSP280x_headers/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


