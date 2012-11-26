/*
 * MamdaniOutputVariable.h
 *
 *  Created on: Oct 24, 2012
 *      Author: igloo
 */

#ifndef MAMDANIOUTPUTVARIABLE_H_
#define MAMDANIOUTPUTVARIABLE_H_

#include "LinguisticVariable.h"

class MamdaniOutputVariable: public LinguisticVariable {

private:

	vector<int> modulatedSet;	//Save the IDs of modulated fuzzy set i.e. set using for the defuzzification.

	//logger
	//static log4cplus::Logger logger;

public:

	MamdaniOutputVariable(const std::string& name, float min, float max);
	~MamdaniOutputVariable();

	bool modulateOutputSet(int setID, float modulationValue);

	int getNumberOfModulatedSet() const;
	const vector<int>& getModulatedSet() const;

	/**
	 * Reset the modulation of the variable. In case that
	 * a fuzzyfication is called more than one time.
	 */
	void resetVariableModulation();
};

#endif /* MAMDANIOUTPUTVARIABLE_H_ */
