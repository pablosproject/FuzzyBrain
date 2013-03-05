/*
 * RulesContainer.cpp
 *
 *  Created on: Oct 25, 2012
 *      Author: igloo
 */

#include "RulesContainer.h"


RulesContainer::~RulesContainer() {
	//free all the rule's memory
	for (unsigned int i=0 ; i<rules.size(); i++){
		delete(rules[i]);
		rules[i]=0;
	}
}

RulesContainer::RulesContainer(){}

void RulesContainer::addRule(MamdaniRule* rule) {
	this->rules.push_back(rule);
}

bool RulesContainer::createCache(const MappedPointersContainer <InputLinguisticVariable>& input) {

	//Create a new cache
	this->values = std::vector<std::vector<float> >(input.getMaxID());
	MappedPointersContainerConstIt it;

	//calculate the value for every variable and set with the given input
	for (it = input.begin(); it != input.end(); it++) {
		int idVar = it->second;
		int numSet = input.getElement(idVar)->getNumberOfSet();

		values[idVar] = vector<float>(numSet);
		for ( int j = 0 ; j < numSet; j++){
			float inputValue = input.getElement(idVar)->getInput();
			if(!notNumber::checkNaN(inputValue))				//check consistence of the input value
				values[idVar][j] = input.getElement(idVar)->membershipToASet(j,input.getElement(idVar)->getInput());
			else
			{
				LERROR << "Cannot find inputValue for variable " << it->first ;
				return false;
			}
		}
	}
	return true;
}



void RulesContainer::printCache() const{

	for (unsigned int i = 0; i< values.size(); i++){
		std::cout << "variable"<<i<< ":";
		for (unsigned int j = 0 ; j < values[i].size(); j++){
			std::cout   << " - " << values[i][j];
		}
		std::cout << "\n";
	}
}

bool RulesContainer::evaluateRules(const MappedPointersContainer <InputLinguisticVariable>& input, MamdaniOutputVariable *out){

	if(!createCache(input)){
		LERROR << "Error in creating the cache of input value.";
		return false;
	}

	for (int i = 0 ; i<rules.size() ; i++){

		float rule_res = rules[i]->evaluateAntecedent(this->values);
		if(rule_res < 0)
			return false; // error in an evaluatino of antecedent

		if(!rules[i]->modulateConsequent(out,rule_res))
			return false; //error in the modulation
	}

	return true;
}
