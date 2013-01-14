################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/shape/PolygonalShape.cpp \
../src/shape/RectangularShape.cpp \
../src/shape/TrapezoidalShape.cpp \
../src/shape/TriangularShape.cpp 

OBJS += \
./src/shape/PolygonalShape.o \
./src/shape/RectangularShape.o \
./src/shape/TrapezoidalShape.o \
./src/shape/TriangularShape.o 

CPP_DEPS += \
./src/shape/PolygonalShape.d \
./src/shape/RectangularShape.d \
./src/shape/TrapezoidalShape.d \
./src/shape/TriangularShape.d 


# Each subdirectory must supply rules for building sources it contributes
src/shape/%.o: ../src/shape/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


