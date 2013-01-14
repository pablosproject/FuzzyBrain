################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/operator/ZadehianAnd.cpp \
../src/operator/ZadehianOr.cpp 

OBJS += \
./src/operator/ZadehianAnd.o \
./src/operator/ZadehianOr.o 

CPP_DEPS += \
./src/operator/ZadehianAnd.d \
./src/operator/ZadehianOr.d 


# Each subdirectory must supply rules for building sources it contributes
src/operator/%.o: ../src/operator/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


