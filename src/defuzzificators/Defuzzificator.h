/*
 * Defuzzificator.h
 *
 *  Created on: Oct 24, 2012
 *      Author: igloo
 */

/**
 * Base class for every defuzzificator class. Based on
 * the different system engine, every defuzzificator method
 * behave different, based on the aggregation method that
 * every fuzzy inference engine has.
 */
#ifndef DEFUZZIFICATOR_H_
#define DEFUZZIFICATOR_H_

#include "../linguistic_variables/MamdaniOutputVariable.h"
#include "../Utility.h"

class Defuzzificator {

public:

	virtual ~Defuzzificator();
	/**
	 *	Method that makes the defuzzification of a Mamdani fuzzy inference
	 *	output variable.
	 * @param output	Linguistic variable that is the result of the output.
	 * @return	The defuzzificated output value. In case of error retur NAN.
	 */
	virtual float defuzzify(const MamdaniOutputVariable* output) const = 0;

	virtual Defuzzificator* clone() = 0;
};

#endif /* DEFUZZIFICATOR_H_ */
