################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Application/WindowLifter.c" \

C_SRCS += \
../Sources/Application/WindowLifter.c \

OBJS += \
./Sources/Application/WindowLifter_c.obj \

OBJS_QUOTED += \
"./Sources/Application/WindowLifter_c.obj" \

C_DEPS += \
./Sources/Application/WindowLifter_c.d \

OBJS_OS_FORMAT += \
./Sources/Application/WindowLifter_c.obj \

C_DEPS_QUOTED += \
"./Sources/Application/WindowLifter_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Application/WindowLifter_c.obj: ../Sources/Application/WindowLifter.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/Application/WindowLifter.args" -o "Sources/Application/WindowLifter_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/Application/%.d: ../Sources/Application/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


