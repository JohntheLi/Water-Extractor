################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv5/tools/compiler/msp430_4.2.1/bin/cl430" -vmsp --abi=eabi -g --include_path="C:/ti/ccsv5/ccs_base/msp430/include" --include_path="C:/MSP430_LaunchPad/Workspace/ScienceFairGrace010214" --include_path="C:/ti/ccsv5/tools/compiler/msp430_4.2.1/include" --include_path="C:/ti/ccsv5/ccs_base/msp430/msp430ware_1_40_01_44" --advice:power="all" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: ../main.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_25_03_72/xs" --xdcpath="C:/ti/grace_2_20_01_12/packages;C:/ti/ccsv5/ccs_base/msp430/msp430ware_1_40_01_44/packages;C:/ti/ccsv5/ccs_base;" xdc.tools.configuro -o configPkg -t ti.targets.msp430.elf.MSP430 -p ti.platforms.msp430:MSP430G2553 -r debug -c "C:/ti/ccsv5/tools/compiler/msp430_4.2.1" --compileOptions "--symdebug:dwarf --optimize_with_debug" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: | configPkg/linker.cmd
configPkg/: | configPkg/linker.cmd


