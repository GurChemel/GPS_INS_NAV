################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
board/DS2401.obj: ../board/DS2401.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/third_party/fatfs/src" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/inc" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/driverlib" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps/json" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/source" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=cc3200 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="board/DS2401.d" --obj_directory="board" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

board/SD_card.obj: ../board/SD_card.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/third_party/fatfs/src" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/inc" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/driverlib" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps/json" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/source" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=cc3200 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="board/SD_card.d" --obj_directory="board" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

board/board.obj: ../board/board.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/third_party/fatfs/src" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/inc" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/driverlib" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps/json" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/source" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=cc3200 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="board/board.d" --obj_directory="board" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

board/pinmux.obj: ../board/pinmux.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/TI/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/third_party/fatfs/src" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/inc" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/driverlib" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/netapps/json" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/include" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink/source" --include_path="C:/TI/CC3200SDK_1.2.0/cc3200-sdk/simplelink_extlib/provisioninglib" -g --define=cc3200 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="board/pinmux.d" --obj_directory="board" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


