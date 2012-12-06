/*
d * InputProvider.h
 *
 *  Created on: Dec 6, 2012
 *      Author: igloo
 */
#include "../FuzzyEngine.h"

#ifndef INPUTPROVIDER_H_
#define INPUTPROVIDER_H_

class InputProvider {
public:
	InputProvider();
	virtual ~InputProvider();

	virtual bool processInput(FuzzyEngine* engine) = 0;
};

#endif /* INPUTPROVIDER_H_ */
