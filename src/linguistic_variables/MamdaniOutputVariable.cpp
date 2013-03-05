/*
 * MamdaniOutputVariable.cpp
 *
 *  Created on: Oct 24, 2012
 *      Author: igloo
 */

#include "MamdaniOutputVariable.h"


MamdaniOutputVariable::~MamdaniOutputVariable() {
	// TODO Auto-generated destructor stub
}

MamdaniOutputVariable::MamdaniOutputVariable(const std::string& name, float min,
		float max): LinguisticVariable(name,min,max) {
}

bool MamdaniOutputVariable::modulateOutputSet(int setID,
		float modulationValue) {

	if(!hasSetID(setID)){
		LERROR << this->name << ": set does not exists in output variable.";
		return false;
	}

	if(modulationValue == 0) //if 0 not added to the output var, no contribution
		return true;

	vector<int>::iterator modulated_it = std::find(this->modulatedSet.begin(), this->modulatedSet.end(), setID);

	if(modulated_it != this->modulatedSet.end()){	//set already modulated
		if(getMutableSet(setID)->getScale() < modulationValue)			//Modulate it only if the new modulation is greater (aggregation with MAX)
			return getMutableSet(setID)->mamdaniScale(modulationValue);
		else
			return true;
	}
	else{
		if(getMutableSet(setID)->mamdaniScale(modulationValue)){
			this->modulatedSet.push_back(setID);
			return true;
		}
		else
			return false;
	}
}

int MamdaniOutputVariable::getNumberOfFinalSet() const{
	return this->modulatedSet.size();
}

const vector<int>& MamdaniOutputVariable::getModulatedSet() const {
	return modulatedSet;
}

void MamdaniOutputVariable::resetVariableModulation() {
	this->modulatedSet.clear();

	//MappedContainer
}

float MamdaniOutputVariable::membershipForPoint(float point) const {

	float maximum = 0;
	for (int i = 0; i < modulatedSet.size(); i++){
		maximum = max(maximum, getSet(modulatedSet[i])->CalculateMembership(point));
	}

	return maximum;
}
