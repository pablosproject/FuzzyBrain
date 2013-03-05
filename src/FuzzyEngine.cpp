/*
 * FuzzyEngine.cpp
 *
 *  Created on: Nov 26, 2012
 *      Author: igloo
 */

#include "FuzzyEngine.h"
#include "input_providers/InputProvider.h"
#include "engine_creator/EngineCreator.h"
#include "ErrorDefinition.h"

FuzzyEngine::FuzzyEngine() :
		rootObject(NULL), creator(NULL), input(NULL), populated(false), result(
				NAN) {
}

FuzzyEngine::~FuzzyEngine() {
	// TODO: assicurati di deallocare quello che  si deve deallocare
	delete (rootObject);
	delete (input);
	delete (creator);
	nestedObjects.freeContainer();
}

void FuzzyEngine::resetEngine() {
	//TODO:devi resettare tutti gli oggetti
}

void FuzzyEngine::addRootFuzzyObject(MamdaniFuzzyObject* root) {
	this->rootObject = root;
	//TODO:Se ce n' giˆ uno devi toglierlo e deallocarlo
}

void FuzzyEngine::addFuzzyObject(MamdaniFuzzyObject* object) {
	this->nestedObjects.insert(object->getName(), object);
}

bool FuzzyEngine::setinput(const std::string& object,
		const std::string& variable, float value) {

	if (object == this->rootObject->getName()) {
		return this->rootObject->setInput(variable, value);
	} else {
		MamdaniFuzzyObject *obj = this->nestedObjects.getElement(object);
		if (obj)
			return obj->setInput(variable, value);
		else {
			LERROR <<
					"Error, does not exist the object in the engine: " << object;
			return false;
		}
	}
}

bool FuzzyEngine::populateEngine() {
	//TODO: correggi in modo che non possa essere null il creator
	if (creator->createEngine(this)) {
		this->populated = true;
		return true;
	} else
		//TODO: logga l'errore
		return false;
}

const MamdaniFuzzyObject* FuzzyEngine::getObject(const string& objName) {

	if (objName == rootObject->getName())
		return this->rootObject;
	else
		return this->nestedObjects.getElement(objName);

}

void FuzzyEngine::setEngineCreator(EngineCreator* creator) {
	if (this->creator)
		delete (creator);
	this->creator = creator;
}

void FuzzyEngine::setInputProvider(InputProvider* input) {
	if (this->input)
		delete (input);
	this->input = input;
}

bool FuzzyEngine::populateInput() {
	if (input->processInput(this))
		return true;
	else
		//TODO:logga l'informazione
		return false;
}

float FuzzyEngine::run() {

	//POPULATING ENGINE
	if (!populated)
		if (!populateEngine())
			return LOADING_AND_CREATING_ENGINE_ERROR;

	//POPULATING THE INPUT FOR THE RUN
	if (populateInput()) {
		float result = rootObject->getOutput();

		if (notNumber::checkNaN(result))
			return FUZZY_INFERENCE_ERROR;

		return result;
	} else
		return INPUT_SETUP_ERROR;
}

void FuzzyEngine::setAllDefuzzificator(Defuzzificator* defuzz) {

	MappedPointersContainerIt it;


	for (it = nestedObjects.begin(); it != nestedObjects.end(); it ++){
		nestedObjects.getElement(it->first)->setDefuzzificator(defuzz->clone());
	}

	rootObject->setDefuzzificator(defuzz->clone());
}

