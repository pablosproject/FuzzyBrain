/*
 * ManualInputProvider.h
 *
 *  Created on: Dec 6, 2012
 *      Author: igloo
 */

#ifndef MANUALINPUTPROVIDER_H_
#define MANUALINPUTPROVIDER_H_
#include "InputProvider.h"

class ManualInputProvider : public InputProvider {

private:
	string input;

public:

	ManualInputProvider();
	ManualInputProvider(const char *in);
	virtual ~ManualInputProvider();

	virtual bool processInput(FuzzyEngine* engine);

};

#endif /* MANUALINPUTPROVIDER_H_ */
