################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Buck-test_codegen/%.obj: ../Buck-test_codegen/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2041/ccs/tools/compiler/ti-cgt-c2000_22.6.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 -O0 --fp_mode=relaxed --include_path="C:/Users/Basement/Documents/Plexim/Target Code/280049" --include_path="C:/Users/Basement/Documents/Plexim/Target Code/280049/app" --include_path="C:/Users/Basement/Documents/Plexim/Target Code/280049/pil" --include_path="C:/Users/Basement/Documents/Plexim/Target Code/280049/shrd" --include_path="C:/Users/Basement/Documents/Plexim/Target Code/280049/inc" --include_path="C:/Users/Basement/Documents/Plexim/Target Code/280049/inc_impl" --include_path="C:/Users/Basement/Documents/Plexim/Target Code/280049/tiinc" --include_path="C:/Users/Basement/Documents/Plexim/Target Code/280049/tiinc/driverlib" --include_path="C:/Users/Basement/Documents/Plexim/Target Code/280049/cg" --include_path="C:/ti/ccs2041/ccs/tools/compiler/ti-cgt-c2000_22.6.3.LTS/include" --advice:performance=all --define=_INLINE --define=CPU1 --define=_PLEXIM_ --define=EXTERNAL_MODE=1 --define=_FLASH -g --symdebug:dwarf_version=3 --c11 --float_operations_allowed=all --diag_warning=225 --emit_warnings_as_errors --abi=eabi --preproc_with_compile --preproc_dependency="Buck-test_codegen/$(basename $(<F)).d_raw" --obj_directory="Buck-test_codegen" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Buck-test_codegen/%.obj: ../Buck-test_codegen/%.cla $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2041/ccs/tools/compiler/ti-cgt-c2000_22.6.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 -O0 --fp_mode=relaxed --include_path="C:/Users/Basement/Documents/Plexim/Target Code/280049" --include_path="C:/Users/Basement/Documents/Plexim/Target Code/280049/app" --include_path="C:/Users/Basement/Documents/Plexim/Target Code/280049/pil" --include_path="C:/Users/Basement/Documents/Plexim/Target Code/280049/shrd" --include_path="C:/Users/Basement/Documents/Plexim/Target Code/280049/inc" --include_path="C:/Users/Basement/Documents/Plexim/Target Code/280049/inc_impl" --include_path="C:/Users/Basement/Documents/Plexim/Target Code/280049/tiinc" --include_path="C:/Users/Basement/Documents/Plexim/Target Code/280049/tiinc/driverlib" --include_path="C:/Users/Basement/Documents/Plexim/Target Code/280049/cg" --include_path="C:/ti/ccs2041/ccs/tools/compiler/ti-cgt-c2000_22.6.3.LTS/include" --advice:performance=all --define=_INLINE --define=CPU1 --define=_PLEXIM_ --define=EXTERNAL_MODE=1 --define=_FLASH -g --symdebug:dwarf_version=3 --c11 --float_operations_allowed=all --diag_warning=225 --emit_warnings_as_errors --abi=eabi --preproc_with_compile --preproc_dependency="Buck-test_codegen/$(basename $(<F)).d_raw" --obj_directory="Buck-test_codegen" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


