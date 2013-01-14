################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/fuzzy_sets/FuzzySet.cpp \
../src/fuzzy_sets/RectangularFuzzySet.cpp \
../src/fuzzy_sets/SimplePolygonalFuzzySet.cpp \
../src/fuzzy_sets/SingletonFuzzySet.cpp \
../src/fuzzy_sets/TrapezoidalFuzzySet.cpp \
../src/fuzzy_sets/TriangularFuzzySet.cpp 

OBJS += \
./src/fuzzy_sets/FuzzySet.o \
./src/fuzzy_sets/RectangularFuzzySet.o \
./src/fuzzy_sets/SimplePolygonalFuzzySet.o \
./src/fuzzy_sets/SingletonFuzzySet.o \
./src/fuzzy_sets/TrapezoidalFuzzySet.o \
./src/fuzzy_sets/TriangularFuzzySet.o 

CPP_DEPS += \
./src/fuzzy_sets/FuzzySet.d \
./src/fuzzy_sets/RectangularFuzzySet.d \
./src/fuzzy_sets/SimplePolygonalFuzzySet.d \
./src/fuzzy_sets/SingletonFuzzySet.d \
./src/fuzzy_sets/TrapezoidalFuzzySet.d \
./src/fuzzy_sets/TriangularFuzzySet.d 


# Each subdirectory must supply rules for building sources it contributes
src/fuzzy_sets/%.o: ../src/fuzzy_sets/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


