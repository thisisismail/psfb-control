################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
PSFB_ISMAIL.obj: ../PSFB_ISMAIL.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1120/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --fp_mode=relaxed --include_path="C:/Users/Muhammad Nur Ismail/Downloads/PSFB2_me/PSFB_Closed_Loop_Control" --include_path="C:/Users/Muhammad Nur Ismail/Downloads/PSFB2_me/PSFB_Closed_Loop_Control/device" --include_path="C:/ti/C2000Ware_5_01_00_00/driverlib/f2837xd/driverlib" --include_path="C:/ti/ccs1120/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=CPU1 --define=FLASH --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/Muhammad Nur Ismail/Downloads/PSFB2_me/PSFB_Closed_Loop_Control/CPU1_RAM/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1226269633: ../epwm_ex8_deadband.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs1120/ccs/utils/sysconfig_cli.bat" -s "C:/ti/C2000Ware_5_01_00_00/.metadata/sdk.json" -d "F2837xD" --script "C:/Users/Muhammad Nur Ismail/Downloads/PSFB2_me/PSFB_Closed_Loop_Control/epwm_ex8_deadband.syscfg" -o "syscfg" --package F2837xD_176PTP --part F2837xD_176PTP --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-1226269633 ../epwm_ex8_deadband.syscfg
syscfg/board.h: build-1226269633
syscfg/board.cmd.genlibs: build-1226269633
syscfg/board.opt: build-1226269633
syscfg/pinmux.csv: build-1226269633
syscfg/epwm.dot: build-1226269633
syscfg/c2000ware_libraries.cmd.genlibs: build-1226269633
syscfg/c2000ware_libraries.opt: build-1226269633
syscfg/c2000ware_libraries.c: build-1226269633
syscfg/c2000ware_libraries.h: build-1226269633
syscfg/clocktree.h: build-1226269633
syscfg/: build-1226269633

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1120/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/Muhammad Nur Ismail/Downloads/PSFB2_me/PSFB_Closed_Loop_Control" --include_path="C:/Users/Muhammad Nur Ismail/Downloads/PSFB2_me/PSFB_Closed_Loop_Control/device" --include_path="C:/ti/C2000Ware_5_01_00_00/driverlib/f2837xd/driverlib" --include_path="C:/ti/ccs1120/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/Muhammad Nur Ismail/Downloads/PSFB2_me/PSFB_Closed_Loop_Control/CPU1_RAM/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


