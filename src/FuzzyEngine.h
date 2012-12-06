/*
 * FuzzyEngine.h
 *
 *  Created on: Nov 26, 2012
 *      Author: igloo
 */

#ifndef FUZZYENGINE_H_
#define FUZZYENGINE_H_

#include "Utility.h"
#include "MamdaniFuzzyObject.h"
#include "MappedPointersContainer.hpp"

class FuzzyEngine {

private:

	MamdaniFuzzyObject *rootObject;
	MappedPointersContainer<MamdaniFuzzyObject> nestedObjects;

	//TODO:mettici l'engine creator

	void resetEngine();

	float result;

	//Logger
	static log4cplus::Logger logger;

public:

	FuzzyEngine();
	~FuzzyEngine();//TODO: l'engine si occupa di disallocare tutti gli object che contiene

	void addRootFuzzyObject( MamdaniFuzzyObject* root);
	void addFuzzyObject( MamdaniFuzzyObject* object);

	void run();

	bool setinput(const std::string& object, const std::string& variable, float value);
};

#endif /* FUZZYENGINE_H_ */
