/*
 * COSDefuzzificator.h
 *
 *  Created on: Nov 22, 2012
 *      Author: igloo
 */

#ifndef COSDEFUZZIFICATOR_H_
#define COSDEFUZZIFICATOR_H_

#include "Defuzzificator.h"

class COSDefuzzificator: public Defuzzificator {

public:

	COSDefuzzificator();
	~COSDefuzzificator();

	float defuzzify(const MamdaniOutputVariable* output) const;
	COSDefuzzificator* clone ();

};

#endif /* COSDEFUZZIFICATOR_H_ */
