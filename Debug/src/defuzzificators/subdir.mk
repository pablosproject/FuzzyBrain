################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/defuzzificators/COSDefuzzificator.cpp \
../src/defuzzificators/CentroidDefuzzificator.cpp \
../src/defuzzificators/Defuzzificator.cpp 

OBJS += \
./src/defuzzificators/COSDefuzzificator.o \
./src/defuzzificators/CentroidDefuzzificator.o \
./src/defuzzificators/Defuzzificator.o 

CPP_DEPS += \
./src/defuzzificators/COSDefuzzificator.d \
./src/defuzzificators/CentroidDefuzzificator.d \
./src/defuzzificators/Defuzzificator.d 


# Each subdirectory must supply rules for building sources it contributes
src/defuzzificators/%.o: ../src/defuzzificators/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


