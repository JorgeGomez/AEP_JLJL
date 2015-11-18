################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/MAL/Kernel.c" \
"../Sources/MAL/Tasks.c" \

C_SRCS += \
../Sources/MAL/Kernel.c \
../Sources/MAL/Tasks.c \

OBJS += \
./Sources/MAL/Kernel_c.obj \
./Sources/MAL/Tasks_c.obj \

OBJS_QUOTED += \
"./Sources/MAL/Kernel_c.obj" \
"./Sources/MAL/Tasks_c.obj" \

C_DEPS += \
./Sources/MAL/Kernel_c.d \
./Sources/MAL/Tasks_c.d \

OBJS_OS_FORMAT += \
./Sources/MAL/Kernel_c.obj \
./Sources/MAL/Tasks_c.obj \

C_DEPS_QUOTED += \
"./Sources/MAL/Kernel_c.d" \
"./Sources/MAL/Tasks_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/MAL/Kernel_c.obj: ../Sources/MAL/Kernel.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/MAL/Kernel.args" -o "Sources/MAL/Kernel_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/MAL/%.d: ../Sources/MAL/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/MAL/Tasks_c.obj: ../Sources/MAL/Tasks.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/MAL/Tasks.args" -o "Sources/MAL/Tasks_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


