################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
SYSCFG_SRCS += \
../epwm_ex8_deadband.syscfg 


# Each subdirectory must supply rules for building sources it contributes
PSFB_ISMAIL.null: ../PSFB_ISMAIL.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	225 /device /include DEBUG CPU1 10063  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

syscfg/error.h: ../epwm_ex8_deadband.syscfg subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: SysConfig'
	"" -s "/.metadata/sdk.json" -d "F2837xD" -o "syscfg" --package F2837xD_176PTP --part F2837xD_176PTP --compiler ccs
	@echo 'Finished building: $<'
	@echo ' '


