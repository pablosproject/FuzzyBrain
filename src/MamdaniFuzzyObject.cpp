/*
 * MamdaniFuzzyObject.cpp
 *
 *  Created on: Oct 24, 2012
 *      Author: igloo
 */

#include "MamdaniFuzzyObject.h"


const std::string MamdaniFuzzyObject::NOT_INITIALIZED_STRING =
		"Not initialized.";

MamdaniFuzzyObject::~MamdaniFuzzyObject() {

	delete (this->outputVar);
	delete (andOP);
	delete (orOP);
	delete (defuzzificator);
}

MamdaniFuzzyObject::MamdaniFuzzyObject(AndOperator* _and, OrOperator* _or,
		MamdaniOutputVariable* _out, Defuzzificator* _def) :
		 outputVar(_out), andOP(_and), orOP(_or), defuzzificator(_def) {
	this->analyzer = RuleAnalyzer(&this->inputVars, this->outputVar);
}

bool MamdaniFuzzyObject::addInputVar( InputLinguisticVariable* variable) {

	if (!variable->checkConsistence()) {	//Inconsistent variable
		LERROR <<
				this->getName() << " Error: the variable passed is not consistent.";
		return false;
	}

	else if (this->inputVars.hasElement(variable->getName())) {	//Duplicated variable
		LERROR <<
				this->getName() << " Error: an input variable with these name already exist.";
		return false;
	}

	return this->inputVars.insert(variable->getName(), variable);

}

bool MamdaniFuzzyObject::setOutputVar(MamdaniOutputVariable* _output) {

	if (this->outputVar == NULL) {
		this->outputVar = _output;
		this->analyzer.setOutputVar(_output);
		return true;
	} else
		return false;
}

bool MamdaniFuzzyObject::addRule(MamdaniRule* rule) {

	if (analyzer.parseRule(rule)) {
		rule->setAndOperator(this->andOP);
		rule->setOrOperator(this->orOP);

		this->rules.addRule(rule);
		return true;
	} else {
		LERROR << "Error in parsing the rule.";
		return false;
	}
}

const std::string& MamdaniFuzzyObject::getName() const {
	if (this->outputVar)
		return this->outputVar->getName();
	else
		return NOT_INITIALIZED_STRING;
}

float MamdaniFuzzyObject::getOutput() {

	if(!verifyInputVars())
	{
		LERROR << this->getName() << ": Error in obtaining the values of nested input  variable. Inference not valid.";
		return NAN;
	}
	this->outputVar->resetVariableModulation();

	this->rules.evaluateRules(this->inputVars, this->outputVar);
	float defuzif = this->defuzzificator->defuzzify(this->outputVar);

	if(notNumber::checkNaN(defuzif))
		LERROR <<this->getName() << ": Error in defuzzifying the output. Check the setup of the object.";

	return defuzif;
}

const MamdaniOutputVariable* MamdaniFuzzyObject::getOutputVar() const {
	return outputVar;
}

bool MamdaniFuzzyObject::setInput(const std::string& varName,
		float input_value) {

	int id = this->inputVars.getID(varName);
	if (id >= 0)
		return this->inputVars.getElement(id)->setInput(input_value);
	else {
		LERROR <<
				this->getName() << ": The variable " << varName+" specified does not exist in this fuzzy object.";
		return false;
	}
}

bool MamdaniFuzzyObject::setInput(const std::string& varName,
		FuzzyObject* object) {

	if (object == this) {
		LERROR <<
				this->getName() << ": A fuzzy object cannot point an input to itself.";
		return false;
	}

	int id = this->inputVars.getID(varName);

	if (id >= 0) {
		int search = getExistentNestedVar(id);
		if (search >= 0)
			this->nestedVariables[search].nestedVar = object;
		else
			this->nestedVariables.push_back(NestedVar(object, id));
		return true;
	} else {
		LERROR <<
				this->getName() << ": The variable " << varName << " specified does not exist in this fuzzy object.";
		return false;
	}
}

float MamdaniFuzzyObject::getInputValue(const std::string& varName) const{

	int id = this->inputVars.getID(varName);

	if (id >= 0)
		return this->inputVars.getElement(id)->getInput();
	else {
		LERROR <<
				this->getName() <<": The variable " << varName << " specified does not exist in this fuzzy object.";
		return NAN;
	}
}

int MamdaniFuzzyObject::getExistentNestedVar(int _varID) {

	for (unsigned i = 0; i < this->nestedVariables.size(); i++) {
		if (this->nestedVariables[i].varID == _varID) {
			return i;
		}
	}
	return -1;	//if not found return a negative id
}

void MamdaniFuzzyObject::printCache() const{
	this->rules.printCache();
}

const Defuzzificator* MamdaniFuzzyObject::getDefuzzificator() const {
	return defuzzificator;
}

void MamdaniFuzzyObject::setDefuzzificator(
		 Defuzzificator* defuzzificator) {
	delete(this->defuzzificator);
	this->defuzzificator = defuzzificator;
}

bool MamdaniFuzzyObject::verifyInputVars() {

	//Check that all the nested variables has a value

	for (unsigned int i = 0; i < this->nestedVariables.size(); i++){
		float result_obj= nestedVariables[i].nestedVar->getOutput();
		if (!notNumber::checkNaN(result_obj)){
			if(!this->inputVars.getElement(nestedVariables[i].varID)->setInput(result_obj)){
				LERROR << this->getName() << ": the input obtained for the variable " << nestedVariables[i].nestedVar->getName() << "is out of range";
				return false;
			}
		}
		else{
			LERROR << this->getName() << ": error in evaluating the nested variables " << nestedVariables[i].nestedVar->getName();
			return false;
		}
	}

	return true;	//at the end I must not have nested variables
}

const InputLinguisticVariable* MamdaniFuzzyObject::getInputVar(
		const string& name) const {

	return inputVars.getElement(name);
}
