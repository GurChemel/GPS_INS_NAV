################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
INS/INS.obj: ../INS/INS.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/third_party/fatfs/src" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/common" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/inc" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/driverlib" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps/json" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/source" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=cc3200 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="INS/INS.d" --obj_directory="INS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

INS/kalman_filter.obj: ../INS/kalman_filter.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/third_party/fatfs/src" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/common" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/inc" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/driverlib" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps/json" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/source" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=cc3200 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="INS/kalman_filter.d" --obj_directory="INS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

INS/matrix_manipulation.obj: ../INS/matrix_manipulation.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/third_party/fatfs/src" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/common" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/inc" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/driverlib" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps/json" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/source" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=cc3200 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="INS/matrix_manipulation.d" --obj_directory="INS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


