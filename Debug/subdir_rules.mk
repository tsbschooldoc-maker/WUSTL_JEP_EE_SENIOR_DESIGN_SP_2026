################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'C2000 Compiler - building file: "$<"'
	"C:/ti/ccs2050/ccs/tools/compiler/ti-cgt-c2000_25.11.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 -O4 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/Users/David/Downloads/280049-Final/280049" --include_path="C:/Users/David/Downloads/280049-Final/280049/app" --include_path="C:/Users/David/Downloads/280049-Final/280049/pil" --include_path="C:/Users/David/Downloads/280049-Final/280049/shrd" --include_path="C:/Users/David/Downloads/280049-Final/280049/inc" --include_path="C:/Users/David/Downloads/280049-Final/280049/inc_impl" --include_path="C:/Users/David/Downloads/280049-Final/280049/tiinc" --include_path="C:/Users/David/Downloads/280049-Final/280049/tiinc/driverlib" --include_path="C:/Users/David/Downloads/280049-Final/280049/cg" --include_path="C:/ti/ccs2050/ccs/tools/compiler/ti-cgt-c2000_25.11.0.LTS/include" --advice:performance=all --define=_INLINE --define=CPU1 --define=_PLEXIM_ --define=EXTERNAL_MODE=1 --define=_FLASH -g --symdebug:dwarf_version=3 --c11 --float_operations_allowed=all --diag_warning=225 --emit_warnings_as_errors --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.cla $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'C2000 Compiler - building file: "$<"'
	"C:/ti/ccs2050/ccs/tools/compiler/ti-cgt-c2000_25.11.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 -O4 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/Users/David/Downloads/280049-Final/280049" --include_path="C:/Users/David/Downloads/280049-Final/280049/app" --include_path="C:/Users/David/Downloads/280049-Final/280049/pil" --include_path="C:/Users/David/Downloads/280049-Final/280049/shrd" --include_path="C:/Users/David/Downloads/280049-Final/280049/inc" --include_path="C:/Users/David/Downloads/280049-Final/280049/inc_impl" --include_path="C:/Users/David/Downloads/280049-Final/280049/tiinc" --include_path="C:/Users/David/Downloads/280049-Final/280049/tiinc/driverlib" --include_path="C:/Users/David/Downloads/280049-Final/280049/cg" --include_path="C:/ti/ccs2050/ccs/tools/compiler/ti-cgt-c2000_25.11.0.LTS/include" --advice:performance=all --define=_INLINE --define=CPU1 --define=_PLEXIM_ --define=EXTERNAL_MODE=1 --define=_FLASH -g --symdebug:dwarf_version=3 --c11 --float_operations_allowed=all --diag_warning=225 --emit_warnings_as_errors --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


