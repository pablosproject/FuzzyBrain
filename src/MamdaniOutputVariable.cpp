/*
 * MamdaniOutputVariable.cpp
 *
 *  Created on: Oct 24, 2012
 *      Author: igloo
 */

#include "MamdaniOutputVariable.h"

//log4cplus::Logger MamdaniOutputVariable::logger = logging::getLogger("MamdaniOutputVariable");

MamdaniOutputVariable::~MamdaniOutputVariable() {
	// TODO Auto-generated destructor stub
}

MamdaniOutputVariable::MamdaniOutputVariable(const std::string& name, float min,
		float max): LinguisticVariable(name,min,max) {
}

bool MamdaniOutputVariable::modulateOutputSet(int setID,
		float modulationValue) {

	if(!hasSetID(setID)){
		LOG4CPLUS_ERROR(this->logger, this->name + ": set does not exists in output variable.");
		return false;
	}

	if(modulationValue == 0) //if 0 not added to the output var, no contribution
		return true;

	vector<int>::iterator modulated_it = std::find(this->modulatedSet.begin(), this->modulatedSet.end(), setID);

	if(modulated_it != this->modulatedSet.end()){
		return getMutableSet(setID)->scale(modulationValue);
	}
	else{
		if(getMutableSet(setID)->scale(modulationValue)){
			this->modulatedSet.push_back(setID);
			return true;
		}
		else
			return false;
	}
}

int MamdaniOutputVariable::getNumberOfModulatedSet() const{
	return this->modulatedSet.size();
}

const vector<int>& MamdaniOutputVariable::getModulatedSet() const {
	return modulatedSet;
}

void MamdaniOutputVariable::resetVariableModulation() {
	this->modulatedSet.clear();

	//MappedContainer
}
