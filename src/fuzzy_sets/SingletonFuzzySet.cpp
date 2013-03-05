/*
 * SingletonFuzzySet.cpp
 *
 *  Created on: 08/ott/2012
 *      Author: pablosproject
 */

#include "SingletonFuzzySet.h"


SingletonFuzzySet::SingletonFuzzySet():FuzzySet(""),A(NAN),initialized(false) {}

SingletonFuzzySet::SingletonFuzzySet(const std::string& _name, float APoint):FuzzySet(_name),A(APoint) {
	this->initialized = checkConsistence();
}
SingletonFuzzySet::SingletonFuzzySet(const std::string& _name): FuzzySet(_name),A(NAN),initialized(false){}


bool SingletonFuzzySet::setPoint(float APoint){

	this->A = APoint;
	this-> initialized = checkConsistence();

	return true;
}

float SingletonFuzzySet::CalculateMembership (float point) const{

	if (!initialized){
		LERROR << "Set is not initialized properly. Impossible calculate membership.";
		return -1;
	}
	if (point == this->A) return 1;
	else
	return 0;
}

SingletonFuzzySet::~SingletonFuzzySet() {
	// TODO Auto-generated destructor stub
}

float SingletonFuzzySet::getUpBoundary() const {
	if (initialized)
		return this->A;
	else
		return NAN;
}

float SingletonFuzzySet::getLowBoundary() const {
	if (initialized)
		return this->A;
	else
		return NAN;
}

void SingletonFuzzySet::setName(const std::string& _name){

	if(_name == "")
		LWARNING << "Name cannot be an empty string. Possible inconsistences.";
	this->name = _name;
	this->initialized = checkConsistence();
}


bool SingletonFuzzySet::configureSet(std::string& _name, float Apoint) {

	if (_name == "")
		LWARNING << "Name cannot be an empty string. Possible inconsistences.";

	if (setPoint(Apoint)){
			this->name = _name;
			this->initialized = checkConsistence();
			return true;
		}
	else
		LERROR << "Set cannot be configured. Point error";
	return false;
}

bool SingletonFuzzySet::checkConsistence(){
	if(this->name == "" || notNumber::checkNaN(A))
		return false;
	else
		return true;
}

bool SingletonFuzzySet::mamdaniScale(float value) {
	LERROR << "Cannot scale a singleton fuzzy set. It can't be in a consequent.";
	return false;
}

float SingletonFuzzySet::getScale() const {
	return NAN;
}

float SingletonFuzzySet::getArea() const {
	return 0;
}

float SingletonFuzzySet::getCentroid() const {
	return this->A;
}

bool SingletonFuzzySet::isScaled() const {
	return false;
}

void SingletonFuzzySet::resetScale() {
	//TODO: revise implementation
}

SingletonFuzzySet* SingletonFuzzySet::clone() const {
	return new SingletonFuzzySet(*this);
}
