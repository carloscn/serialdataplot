################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
source/Main.obj: ../source/Main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/opt/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/bin/cl2000" -v28 -ml -mt --include_path="D:/opt/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" --include_path="../include" --include_path="../hardware/DSP280x_common/include" --include_path="../hardware/DSP280x_headers/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="source/Main.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


