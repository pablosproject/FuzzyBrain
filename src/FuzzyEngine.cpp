/*
 * FuzzyEngine.cpp
 *
 *  Created on: Nov 26, 2012
 *      Author: igloo
 */

#include "FuzzyEngine.h"

log4cplus::Logger FuzzyEngine::logger = logging::getLogger("FuzzyEngine	");

FuzzyEngine::FuzzyEngine():rootObject(NULL), result(NAN){}

FuzzyEngine::~FuzzyEngine() {
	// TODO: assicurati di deallocare quello che  si deve deallocare
	delete (rootObject);
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

void FuzzyEngine::run() {
	this->rootObject->getOutput();
}

bool FuzzyEngine::setinput(const std::string& object,
		const std::string& variable, float value) {

	if(object == this->rootObject->getName()){
		return this->rootObject->setInput(variable, value);
	}
	else{
		MamdaniFuzzyObject *obj = this->nestedObjects.getElement(object);
		if(obj)
			return obj->setInput(variable, value);
		else{
			LOG4CPLUS_ERROR(this->logger, "Error, does not exist the object in the engine: " + object);
			return false;
		}
	}
}

bool FuzzyEngine::populateEngine() {

}

const MamdaniFuzzyObject* FuzzyEngine::getObject(const string& objName) {

	if (objName == rootObject->getName())
		return this->rootObject;
	else
		return this->nestedObjects.getElement(objName);

}
