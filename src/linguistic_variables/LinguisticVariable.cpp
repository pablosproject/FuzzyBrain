/*
 * LinguisticVariable.cpp
 *
 *  Created on: Oct 10, 2012
 *      Author: igloo
 */

#include "LinguisticVariable.h"


LinguisticVariable::LinguisticVariable(const LinguisticVariable& toCopy): name(toCopy.name), min_range(toCopy.min_range), max_range(toCopy.max_range), sets_data(toCopy.sets_data), initialized(toCopy.initialized) {}

LinguisticVariable::LinguisticVariable(const std::string& _name,
		float _min_range, float _max_range): name(_name){
	if(_min_range > _max_range){
		LERROR << this->getName() << ": range not correct in the linguistic variable.";
		this->min_range = NAN;
		this->max_range = NAN;
		this->initialized = false;
	}
	else{
		this->min_range = _min_range;
		this->max_range = _max_range;
		this->initialized = true;
	}
}

LinguisticVariable::~LinguisticVariable() {}

const float LinguisticVariable::membershipToASet(const std::string& setName,
		float inputValue) const {

	int ID = sets_data.getID(setName);
	return membershipToASet(ID, inputValue);

}

const float LinguisticVariable::membershipToASet(int set_ID,
		float inputValue) const {

	if(!checkConsistence())
		return -1;

	if(!sets_data.hasID(set_ID)){
		LWARNING << "The set which you request membership does not exists in this linguistic variable.";
		return -1;
	}

	if (inputValue < this->min_range || inputValue >max_range){
		LERROR << "The input for these variable is out of range.";
		return -1;
	}

	const FuzzySet* set = sets_data.getElement(set_ID);
	return set->CalculateMembership(inputValue);
}

bool LinguisticVariable::addSet(FuzzySet* setToAdd) {

	if(!checkConsistence())
		return false;
	float set_min = setToAdd->getLowBoundary();
	float set_max = setToAdd->getUpBoundary();

	if(set_min < this->min_range || set_max > this->max_range){
		LERROR << "The set is out of linguistic variable boundary. Set not added";
		return false;
	}

	if(sets_data.hasElement(setToAdd->getName())){
		LERROR << "A set with given name already exists. Linguistic variable does not allow duplication.";
		return false;
	}

	bool insertion = sets_data.insert(setToAdd->getName(), setToAdd);
	if(!insertion){
		LERROR << "Could not add set the linguistic variable. Unknow error.";
		return false;
	}

	return true;
}

bool LinguisticVariable::hasSet(const std::string& name) const {
	if(!checkConsistence())
		return false;
	return sets_data.hasElement(name);
}

bool LinguisticVariable::hasSetID(int id) const {
	if(!checkConsistence())
		return false;
	return sets_data.hasID(id);
}

int LinguisticVariable::getSetID(const std::string& name) const {
	if(!checkConsistence())
		return -1;
	return sets_data.getID(name);
}

float LinguisticVariable::getMaxRange() const {
	checkConsistence();
	return max_range;
}

float LinguisticVariable::getMinRange() const {
	checkConsistence();
	return min_range;
}

const std::string& LinguisticVariable::getName() const {
	return this->name;
}

bool LinguisticVariable::checkConsistence() const{

	bool result = true;

	if(this->name == ""){
		LWARNING << "Warning, exist a linguistic variable with no name, revision needed.";
		result = false;
	}

	if(notNumber::checkNaN(this->max_range) || notNumber::checkNaN(this->min_range)){
		LERROR << "Error: variable " << this->name + "have the minimum and maximum range not correct.";
		result = false;
	}

	return result;
}

const FuzzySet* LinguisticVariable::getSet(int id) const {
	if(!checkConsistence())
		return NULL;
	return this->sets_data.getElement(id);
}

int LinguisticVariable::getNumberOfSet() const {
	return this->sets_data.getLength();
}

FuzzySet* LinguisticVariable::getMutableSet(int id) {
	return this->sets_data.getElement(id);
}

const FuzzySet* LinguisticVariable::getSet(const std::string& name) const {
	return this->sets_data.getElement(name);
}
