/*
 * InputLinguisticVariable.h
 *
 *  Created on: Nov 22, 2012
 *      Author: igloo
 */

#ifndef INPUTLINGUISTICVARIABLE_H_
#define INPUTLINGUISTICVARIABLE_H_

#include "LinguisticVariable.h"

class InputLinguisticVariable: public LinguisticVariable {

private:

	float input;	//Handle the input for a given variable

public:
	InputLinguisticVariable(const std::string& _name, float _min_range,
			float _max_range);

	InputLinguisticVariable(const std::string& _name, float _min_range,
			float _max_range, float input);

	InputLinguisticVariable(const LinguisticVariable& toCopy);

	~InputLinguisticVariable();

	bool isSetInput() const;

	/**
	 * Extract the input value of a given input variable.
	 * @return	The input value for the given variable or
	 * NAN if there's some error.
	 */
	float getInput() const;

	bool setInput(float input);

	void replaceSets();
};

#endif /* INPUTLINGUISTICVARIABLE_H_ */
