/*
 * ZadehianOr.h
 *
 *  Created on: Oct 31, 2012
 *      Author: igloo
 */

#ifndef ZADEHIANOR_H_
#define ZADEHIANOR_H_

#include "OrOperator.h"

class ZadehianOr: public OrOperator {

public:

	virtual float orOperation (float f1 , float f2) const;
};

#endif /* ZADEHIANOR_H_ */
