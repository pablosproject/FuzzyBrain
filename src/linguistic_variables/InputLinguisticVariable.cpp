/*
 * InputLinguisticVariable.cpp
 *
 *  Created on: Nov 22, 2012
 *      Author: igloo
 */

#include "InputLinguisticVariable.h"

InputLinguisticVariable::InputLinguisticVariable(const std::string& _name,
		float _min_range, float _max_range): LinguisticVariable(_name, _min_range, _max_range), input(NAN) {}

InputLinguisticVariable::InputLinguisticVariable(const std::string& _name,
		float _min_range, float _max_range, float input):LinguisticVariable(_name, _min_range, _max_range){
	if (checkConsistence()){
		if(input <= this->max_range && input >= this->min_range)
			this->input = input;
		else{
			LERROR << this->getName() << ": Cannot set input for a linguistic variable. Input out of range.";
			this->input = NAN;
		}
	}
}

InputLinguisticVariable::InputLinguisticVariable(
		const LinguisticVariable& toCopy): LinguisticVariable(toCopy), input(NAN) {}

InputLinguisticVariable::~InputLinguisticVariable() {
	// TODO Auto-generated destructor stub
}

bool InputLinguisticVariable::isSetInput() const {
	if(notNumber::checkNaN(this->input))
		return false;
	else
		return true;
}

float InputLinguisticVariable::getInput() const {
	return this->input;
}

bool InputLinguisticVariable::setInput(float input) {

	if(isSetInput() && input!=this->input)
		LWARNING << this->getName() << ": The value of the input already exist";

	if (input > this->max_range || input < this->min_range){
		LERROR << this->getName() << "Input cannot be set because it's out of range.";
		return false;
	}
	else{
		this->input = input;
		return true;
	}

}


