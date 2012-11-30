/*
 * ZadehianAnd.h
 *
 *  Created on: Oct 24, 2012
 *      Author: igloo
 */

#ifndef ZADEHIANAND_H_
#define ZADEHIANAND_H_

#include "AndOperator.h"

class ZadehianAnd: public AndOperator {
public:

	virtual float andOperation (float f1 , float f2) const;
};

#endif /* ZADEHIANAND_H_ */
