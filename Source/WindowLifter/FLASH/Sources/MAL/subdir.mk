################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/MAL/Exceptions.c" \
"../Sources/MAL/IntcInterrupts.c" \
"../Sources/MAL/MainConfig.c" \
"../Sources/MAL/ivor_branch_table.c" \

C_SRCS += \
../Sources/MAL/Exceptions.c \
../Sources/MAL/IntcInterrupts.c \
../Sources/MAL/MainConfig.c \
../Sources/MAL/ivor_branch_table.c \

OBJS += \
./Sources/MAL/Exceptions_c.obj \
./Sources/MAL/IntcInterrupts_c.obj \
./Sources/MAL/MainConfig_c.obj \
./Sources/MAL/ivor_branch_table_c.obj \

OBJS_QUOTED += \
"./Sources/MAL/Exceptions_c.obj" \
"./Sources/MAL/IntcInterrupts_c.obj" \
"./Sources/MAL/MainConfig_c.obj" \
"./Sources/MAL/ivor_branch_table_c.obj" \

C_DEPS += \
./Sources/MAL/Exceptions_c.d \
./Sources/MAL/IntcInterrupts_c.d \
./Sources/MAL/MainConfig_c.d \
./Sources/MAL/ivor_branch_table_c.d \

OBJS_OS_FORMAT += \
./Sources/MAL/Exceptions_c.obj \
./Sources/MAL/IntcInterrupts_c.obj \
./Sources/MAL/MainConfig_c.obj \
./Sources/MAL/ivor_branch_table_c.obj \

C_DEPS_QUOTED += \
"./Sources/MAL/Exceptions_c.d" \
"./Sources/MAL/IntcInterrupts_c.d" \
"./Sources/MAL/MainConfig_c.d" \
"./Sources/MAL/ivor_branch_table_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/MAL/Exceptions_c.obj: ../Sources/MAL/Exceptions.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/MAL/Exceptions.args" -o "Sources/MAL/Exceptions_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/MAL/%.d: ../Sources/MAL/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/MAL/IntcInterrupts_c.obj: ../Sources/MAL/IntcInterrupts.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/MAL/IntcInterrupts.args" -o "Sources/MAL/IntcInterrupts_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/MAL/MainConfig_c.obj: ../Sources/MAL/MainConfig.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/MAL/MainConfig.args" -o "Sources/MAL/MainConfig_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/MAL/ivor_branch_table_c.obj: ../Sources/MAL/ivor_branch_table.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/MAL/ivor_branch_table.args" -o "Sources/MAL/ivor_branch_table_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


