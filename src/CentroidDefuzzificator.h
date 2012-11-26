/*
 * CentroidDefuzzificator.h
 *
 *  Created on: Nov 14, 2012
 *      Author: igloo
 */

#ifndef CENTROIDDEFUZZIFICATOR_H_
#define CENTROIDDEFUZZIFICATOR_H_

#include "Defuzzificator.h"

class CentroidDefuzzificator: public Defuzzificator {
public:
	CentroidDefuzzificator();
	virtual ~CentroidDefuzzificator();

	virtual float defuzzify(const LinguisticVariable* output);

};

#endif /* CENTROIDDEFUZZIFICATOR_H_ */
