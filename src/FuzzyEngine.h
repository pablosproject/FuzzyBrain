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

class EngineCreator;
class InputProvider;

class FuzzyEngine {

private:

	MamdaniFuzzyObject *rootObject;
	MappedPointersContainer<MamdaniFuzzyObject> nestedObjects;

	EngineCreator *creator;
	InputProvider* input;

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

	//Provider of creation and input in the engine
	//void setEngineCreator(const EngineCreator* creator);
//	void setInputProvider(const InputProvider* input);

	//Create the engine based on the input
	bool populateEngine();
	//set the input for the all the input variables of the engine
	bool populateInput();

	//Utility method for getting and setting fuzzy object
	//TODO:digli che torna null
	const MamdaniFuzzyObject* getObject(const string& objName);

};

#endif /* FUZZYENGINE_H_ */
