/*
 * FuzzyEngine.h
 *
 *  Created on: Nov 26, 2012
 *      Author: igloo
 */

#ifndef FUZZYENGINE_H_
#define FUZZYENGINE_H_

#include "Utility.h"
#include "FuzzyObject.h"

class FuzzyEngine {

private:

	FuzzyObject *rootObject;
	std::vector<FuzzyObject*> nestedObjects;

	//TODO:mettici l'engine creator

	void resetEngine();

public:
	FuzzyEngine();
	~FuzzyEngine();
};

#endif /* FUZZYENGINE_H_ */
