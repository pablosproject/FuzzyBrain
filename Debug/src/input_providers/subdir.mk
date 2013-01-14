################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/input_providers/InputProvider.cpp \
../src/input_providers/InputStreamProvider.cpp \
../src/input_providers/ManualInputProvider.cpp 

OBJS += \
./src/input_providers/InputProvider.o \
./src/input_providers/InputStreamProvider.o \
./src/input_providers/ManualInputProvider.o 

CPP_DEPS += \
./src/input_providers/InputProvider.d \
./src/input_providers/InputStreamProvider.d \
./src/input_providers/ManualInputProvider.d 


# Each subdirectory must supply rules for building sources it contributes
src/input_providers/%.o: ../src/input_providers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


