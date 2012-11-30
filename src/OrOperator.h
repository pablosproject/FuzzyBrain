/*
 * OrOperator.h
 *
 *  Created on: Oct 25, 2012
 *      Author: igloo
 */

#ifndef OROPERATOR_H_
#define OROPERATOR_H_

class OrOperator {
public:
	virtual ~OrOperator(){};

	virtual float orOperation (float f1 , float f2) const{return -1;}//TODO:segnala che non hai sottoclassato la classe};

};

#endif /* OROPERATOR_H_ */
