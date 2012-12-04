/*
 * Defuzzificator.h
 *
 *  Created on: Oct 24, 2012
 *      Author: igloo
 */

/**
 * Interface that every defuzzificator object has to implement.
 * Basically it only has to implement the defuzzification of
 * a linguistic variable.
 */
#ifndef DEFUZZIFICATOR_H_
#define DEFUZZIFICATOR_H_

#include "../linguistic_variables/MamdaniOutputVariable.h"
#include "../Utility.h"

class Defuzzificator {
public:
	virtual ~Defuzzificator();

	/**
	 *	Method that makes the defuzzification.
	 * @param output	Linguistic variable that is the result of the output.
	 * @return	The defuzzificated output value. In case of error retur NAN.
	 */
	virtual float defuzzify(const MamdaniOutputVariable* output) const;
};

#endif /* DEFUZZIFICATOR_H_ */
