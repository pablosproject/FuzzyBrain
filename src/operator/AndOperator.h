/*
 * AndOperator.h
 *
 *  Created on: Oct 24, 2012
 *      Author: igloo
 */
/**
 * Interface that every and operator must implement.
 */

#ifndef ANDOPERATOR_H_
#define ANDOPERATOR_H_

class AndOperator {
public:
	 virtual ~AndOperator() {};

	 virtual float andOperation (float f1 , float f2) const {return -1;}//TODO: segnala che non hai sottoclassato l'operatoreq};
};

#endif /* ANDOPERATOR_H_ */
