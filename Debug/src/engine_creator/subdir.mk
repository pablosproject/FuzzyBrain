################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/engine_creator/EngineCreator.cpp \
../src/engine_creator/XMLFPCreator.cpp \
../src/engine_creator/XMLFPParser.cpp 

OBJS += \
./src/engine_creator/EngineCreator.o \
./src/engine_creator/XMLFPCreator.o \
./src/engine_creator/XMLFPParser.o 

CPP_DEPS += \
./src/engine_creator/EngineCreator.d \
./src/engine_creator/XMLFPCreator.d \
./src/engine_creator/XMLFPParser.d 


# Each subdirectory must supply rules for building sources it contributes
src/engine_creator/%.o: ../src/engine_creator/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


