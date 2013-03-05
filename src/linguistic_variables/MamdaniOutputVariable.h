/*
 * MamdaniOutputVariable.h
 *
 *  Created on: Oct 24, 2012
 *      Author: igloo
 */

#ifndef MAMDANIOUTPUTVARIABLE_H_
#define MAMDANIOUTPUTVARIABLE_H_

#include "LinguisticVariable.h"

/**
 * This class represent the output variable of a Mamdani fuzzy inference
 * system.
 * It handles the aggregation operator, and uses it on all the fuzzy sets that results
 * from the implication.
 * The implication method used for the Mamdani Inference
 */

class MamdaniOutputVariable: public LinguisticVariable {

private:

	vector<int> modulatedSet;	//Save the IDs of modulated fuzzy set i.e. set using for the defuzzification.



public:

	MamdaniOutputVariable(const std::string& name, float min, float max);
	~MamdaniOutputVariable();

	bool modulateOutputSet(int setID, float modulationValue);

	int getNumberOfFinalSet() const;
	const vector<int>& getModulatedSet() const;

	/**
	 * Reset the modulation of the variable. In case that
	 * a fuzzyfication is called more than one time.
	 */
	void resetVariableModulation();

	float membershipForPoint(float point) const;
};

#endif /* MAMDANIOUTPUTVARIABLE_H_ */
