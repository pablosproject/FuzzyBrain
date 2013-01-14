################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/fuzzy_rules/FuzzyRule.cpp \
../src/fuzzy_rules/MamdaniRule.cpp \
../src/fuzzy_rules/RuleAnalyzer.cpp \
../src/fuzzy_rules/RulesContainer.cpp 

OBJS += \
./src/fuzzy_rules/FuzzyRule.o \
./src/fuzzy_rules/MamdaniRule.o \
./src/fuzzy_rules/RuleAnalyzer.o \
./src/fuzzy_rules/RulesContainer.o 

CPP_DEPS += \
./src/fuzzy_rules/FuzzyRule.d \
./src/fuzzy_rules/MamdaniRule.d \
./src/fuzzy_rules/RuleAnalyzer.d \
./src/fuzzy_rules/RulesContainer.d 


# Each subdirectory must supply rules for building sources it contributes
src/fuzzy_rules/%.o: ../src/fuzzy_rules/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


