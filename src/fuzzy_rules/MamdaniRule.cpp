/*
 * MamdaniRule.cpp
 *
 *  Created on: Oct 25, 2012
 *      Author: igloo
 */

#include "MamdaniRule.h"


MamdaniRule::MamdaniRule(): FuzzyRule(), consequent_set(-1), consequent_negated(false){}


MamdaniRule::MamdaniRule(const std::string& ruleString):FuzzyRule(ruleString), consequent_set(-1), consequent_negated(false){

	if(ruleString == "")
		LWARNING <<  "Attention: the inserted string is empty. Possible problems in parsing the rule.";
}

MamdaniRule::~MamdaniRule() {}

bool MamdaniRule::addAntecedentToken(int _lingVar, int _set, bool _negated, logicalOperator _OP) {

	if (_lingVar < 0 || _set < 0 ){
		LERROR << "Incorrect value of the linguistic variable or fuzzy set.";
		return false;
	}

	Token toAdd;
	toAdd.set = _set;
	toAdd.variable = _lingVar;
	toAdd.negated = _negated;

	//Add an element to the list if it's empty
	if(this->ruleLogic.empty()){
		std::list<Token> first;
		this->ruleLogic.push_front(first);
	}

	switch(_OP){

	case FuzzyRule::OR:{	//In the case of OR adding a new list of and
		std::list<Token> newlyCreated;
		newlyCreated.push_front(toAdd);
		this->ruleLogic.push_front(newlyCreated);
	}
		break;

	case FuzzyRule::AND:
		this->ruleLogic.front().push_front(toAdd);
		break;

	default:
		LERROR <<"Unexpected operator.";
		break;
	}

	return true;
}

bool MamdaniRule::addConsequent(const std::string& _lingVarName, int _set, bool _negated) {

	if (_lingVarName == "" || _set < 0 ){
		LERROR << "Incorrect value of the linguistic variable or fuzzy set.";
		return false;
	}

	this->consequent_var_name = _lingVarName;
	this->consequent_set = _set;
	this->consequent_negated = _negated;

	return true;

}

void MamdaniRule::setAndOperator(const AndOperator* _and) {
	this->andOperator = _and;
}

void MamdaniRule::setOrOperator(const OrOperator* _or) {
	this->orOperator = _or;
}

const std::string& MamdaniRule::getConsequentVar() const {
	return this->consequent_var_name;
}

bool MamdaniRule::hasAntecedentToken(int _lingVar, int _set, bool _negated) const{


	for(std::list<std::list<Token> >::const_iterator it = ruleLogic.begin(); it != ruleLogic.end(); it++){

		for(std::list<Token>::const_iterator internalIt = it->begin() ; internalIt!= it->end(); internalIt++){
			if (internalIt->set == _set && internalIt->variable == _lingVar && internalIt->negated == _negated )
				return true;
		}
	}

	return false;
}

const std::list<std::list<Token> >& MamdaniRule::getRuleLogic() const {
	return ruleLogic;
}

int MamdaniRule::getConsequentSet() const {
	return consequent_set;
}

const std::string& MamdaniRule::getConsequentVarName() const {
	return consequent_var_name;
}

bool MamdaniRule::isConsequentNegated() const {
	return consequent_negated;
}

void MamdaniRule::resetRule(){

	ruleLogic.erase(ruleLogic.begin(), ruleLogic.end());
	consequent_var_name = "";
	consequent_set = 0;
	consequent_negated = false;

}

float MamdaniRule::extractMembership(
		const std::list<Token>::const_iterator& and_it,
		valueCache& cache) const {
	float membership = cache[and_it->variable][and_it->set];
	if (and_it->negated)
		membership = 1 - membership;

	return membership;
}

float MamdaniRule::evaluateAntecedent(valueCache& cache)  const{

	if(!andOperator || !orOperator){
		LERROR << "And/or operator not set for rule";
		return -1;
	}

	float result = 0;
	float and_result = 0;

	std::list<std::list<Token> >::const_iterator or_it = ruleLogic.begin(); //iterator on the external list
	std::list<Token>::const_iterator and_it;//iterator on the and list

	do{
		and_result = extractMembership(or_it->begin(),cache); // the first hand has to be initialized to the first element

		for(and_it = or_it->begin(); and_it != or_it->end(); and_it++){
			float membership = extractMembership(and_it, cache);
			and_result = this->andOperator->andOperation(and_result,membership);
		}

		if(or_it == ruleLogic.begin())	//the first time initialize it to the first value
			result = and_result;
		result = this->orOperator->orOperation(result,and_result);
		or_it++;
	}while(or_it != ruleLogic.end());

	return result;
}

bool MamdaniRule::modulateConsequent(MamdaniOutputVariable* consequent,
		float modulationValue) const {

	if(modulationValue < 0 || modulationValue > 1){
		LERROR << "Error: cannot modulate with an invalid modulation value";
		return false;
	}
	if(consequent->getName() != this->consequent_var_name){
		LERROR << "Error: output variable and consequent are not equal";
		return false;
	}

	if (this->consequent_negated)
		return consequent->modulateOutputSet(this->consequent_set,1-modulationValue);
	else
		return consequent->modulateOutputSet(this->consequent_set,modulationValue);

}
