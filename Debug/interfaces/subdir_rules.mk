################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
interfaces/diskio.obj: ../interfaces/diskio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/third_party/fatfs/src" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/common" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/inc" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/driverlib" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps/json" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/source" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=cc3200 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="interfaces/diskio.d" --obj_directory="interfaces" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

interfaces/local_i2c_if.obj: ../interfaces/local_i2c_if.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/third_party/fatfs/src" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/common" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/inc" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/driverlib" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps/json" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/source" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=cc3200 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="interfaces/local_i2c_if.d" --obj_directory="interfaces" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

interfaces/local_uart_if.obj: ../interfaces/local_uart_if.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/third_party/fatfs/src" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/common" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/inc" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/driverlib" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps/json" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/source" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=cc3200 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="interfaces/local_uart_if.d" --obj_directory="interfaces" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

interfaces/terninal.obj: ../interfaces/terninal.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/third_party/fatfs/src" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/common" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/inc" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/driverlib" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps/json" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/source" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=cc3200 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="interfaces/terninal.d" --obj_directory="interfaces" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


