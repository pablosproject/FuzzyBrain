################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Configurator.cpp \
../src/FuzzyEngine.cpp \
../src/FuzzyLogger.cpp \
../src/MamdaniFuzzyObject.cpp \
../src/Utility.cpp \
../src/main.cpp 

OBJS += \
./src/Configurator.o \
./src/FuzzyEngine.o \
./src/FuzzyLogger.o \
./src/MamdaniFuzzyObject.o \
./src/Utility.o \
./src/main.o 

CPP_DEPS += \
./src/Configurator.d \
./src/FuzzyEngine.d \
./src/FuzzyLogger.d \
./src/MamdaniFuzzyObject.d \
./src/Utility.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


