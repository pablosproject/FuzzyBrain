################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/linguistic_variables/InputLinguisticVariable.cpp \
../src/linguistic_variables/LinguisticVariable.cpp \
../src/linguistic_variables/MamdaniOutputVariable.cpp 

OBJS += \
./src/linguistic_variables/InputLinguisticVariable.o \
./src/linguistic_variables/LinguisticVariable.o \
./src/linguistic_variables/MamdaniOutputVariable.o 

CPP_DEPS += \
./src/linguistic_variables/InputLinguisticVariable.d \
./src/linguistic_variables/LinguisticVariable.d \
./src/linguistic_variables/MamdaniOutputVariable.d 


# Each subdirectory must supply rules for building sources it contributes
src/linguistic_variables/%.o: ../src/linguistic_variables/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


