/*
 * RuleAnalyzer.cpp
 *
 *  Created on: 01/nov/2012
 *      Author: pablosproject
 */

#include "RuleAnalyzer.h"


const std::string RuleAnalyzer::IF_KEYWORD = "if";
const std::string RuleAnalyzer::IS_KEYWORD = "is";
const std::string RuleAnalyzer::AND_KEYWORD = "and";
const std::string RuleAnalyzer::OR_KEYWORD = "or";
const std::string RuleAnalyzer::THEN_KEYWORD = "then";
const std::string RuleAnalyzer::NOT_KEYWORD = "not";

RuleAnalyzer::RuleAnalyzer() :
		temp_varName(""),temp_setName(""),temp_LingVarID(0), temp_set(0), temp_negated(false), temp_OP(
				FuzzyRule::AND), state(ERROR), objectInputPtr(
				NULL), outputPtr(NULL) {
}

RuleAnalyzer::RuleAnalyzer(
		 MappedPointersContainer< InputLinguisticVariable>* _input,
		 MamdaniOutputVariable* _output) :
					temp_varName(""),temp_setName(""),
		temp_LingVarID(0), temp_set(0), temp_negated(false), temp_OP(
				FuzzyRule::AND), state(INITIAL), objectInputPtr(_input), outputPtr(
				_output) {
}

RuleAnalyzer::~RuleAnalyzer() {
}

void RuleAnalyzer::reset() {
}

bool RuleAnalyzer::parseRule(MamdaniRule* rule) {

	resetMachineState();
	//remember to reset it before every operation
	if (!this->objectInputPtr || !this->outputPtr){
		LERROR <<  "Rule parser not initialized properly.";
		return false;
	}

	if(rule->getRuleDescription().empty()){
		LERROR <<  "Cannot parse an empty string.";
		return false;
	}
	istringstream iss(rule->getRuleDescription());
	std::string token;

	//Parse the string until there are words
	while (iss >> token) {
		nextState(token, iss);

		if (this->state == ERROR) {
			LERROR <<  "Error in parsing rule: "+ rule->getRuleDescription();
			rule->resetRule();
			return false;
		}
		else if (this->state == SET_RECOGNIZED){
			if (!rule->addAntecedentToken(temp_LingVarID, temp_set,
					temp_negated, temp_OP))
				return false;
			resetTempVariables();
		}
		else if (this->state == SET_CONS_RECOGN_END)
				if (!rule->addConsequent(temp_varName, temp_set,
						temp_negated))
					return false;
	}

	if (this->state == SET_CONS_RECOGN_END)
		return true; // if I reach the final state all correct
	else{
		LERROR << "Error in parsing the rule: " << rule->getRuleDescription();
		return false;
	}

}

void RuleAnalyzer::toLowerCaseSTD(std::string &str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

int RuleAnalyzer::verifyInputVar(const std::string& varName) const {
	return objectInputPtr->getID(varName);
}

bool RuleAnalyzer::verifyOutputVar(const std::string& outputVar) const {
	return outputPtr->getName() == outputVar;
}

int RuleAnalyzer::verifyAntecedentSet(int varID, std::string& name) const {
	return objectInputPtr->getElement(varID)->getSetID(name);
}

int RuleAnalyzer::verifyConsequentSet(const std::string& name) {
	return this->outputPtr->getSetID(name);
}

void RuleAnalyzer::nextState(std::string& input, istringstream& stream) {
	switch (this->state) {

	case (INITIAL):
		recognizeIf(input);
		break;
	case (START_RULE):
		recognizeVariable(input, false, stream);
		break;
	case (VARIABLE_RECOGNIZED):
		recognizeIs(input, false);
		break;
	case (IS_RECOGNIZED):
		recognizeSet(input, false, stream);
		break;
	case (SET_RECOGNIZED):
		postSetRecognition(input);
		break;
	case (START_CONSEQUENT):
		recognizeVariable(input, true, stream);
		break;
	case (VAR_CONS_RECOGNIZED):
		recognizeIs(input, true);
		break;
	case (IS_CONS_RECOGNIZED):
		recognizeSet(input, true, stream);
		break;
	case (SET_CONS_RECOGN_END):{
		/*
		 * If I enter here the rule is too long, or there's
		 * some error at the end of the string.
		 */
		this->state =ERROR;
		LERROR <<  "unexpected end of the rule.";
	}
		break;
	case (ERROR):
		//I never have to enter here!
		break;

	}

	//implementa default
}

void RuleAnalyzer::recognizeIf(std::string& input) {
	toLowerCaseSTD(input);
	if (input == IF_KEYWORD)
		this->state = START_RULE ;
	else{
		this->state = ERROR;
		LERROR << "Expected If, but found other thing: " + input;
	}
}

void RuleAnalyzer::validateVariable(bool isConsequent, const std::string& inputVarName) {
	if (!isConsequent) {
		int temp = verifyInputVar(inputVarName);
		if (temp >= 0) {
			this->temp_LingVarID = temp;
			this->state = VARIABLE_RECOGNIZED;
			this->temp_varName = "";
		} else {
			this->state = ERROR;
			LERROR <<
					"Input variable not recognized. Found: "+ inputVarName;
		}
	} else {
		if (verifyOutputVar(inputVarName)) {
			this->state = VAR_CONS_RECOGNIZED;
		} else {
			this->state = ERROR;
			LERROR <<
					"Output variable not recognized. Found: "+ inputVarName;
		}
	}
}

void RuleAnalyzer::recognizeVariable(std::string& input, bool isConsequent, istringstream& stream) {

	this->temp_varName =this->temp_varName + input;
	if(!lookAhead(stream, IS_KEYWORD, true)){
		this->temp_varName = this->temp_varName + " "; // Add a space at end of name beacuse the name is long
	}
	else
		validateVariable(isConsequent, this->temp_varName);

}

void RuleAnalyzer::recognizeIs(std::string& input, bool isConsequent) {
	toLowerCaseSTD(input);
	if (input == IS_KEYWORD){
		if(isConsequent)
			this->state = IS_CONS_RECOGNIZED;
		else
			this->state = IS_RECOGNIZED;
	}
	else{
		this->state = ERROR;
		LERROR <<  "Expected IS keyword, but found other :" + input;
	}
}

void RuleAnalyzer::recognizeSet(std::string& input, bool isConsequent,
		istringstream& stream) {

	std::string input_copy = input;
	toLowerCaseSTD(input_copy);

	if (input_copy == NOT_KEYWORD) //I search for the not keyword. If found stay in these state and then search the set.
		temp_negated = true;		//no change of state
	else {		// If i do not find the not keyword, I search for the set name

		if (isConsequent) {
			this->temp_setName = this->temp_setName + input;
			if (!hasAhead(stream))
			{
				validateSetName(this->temp_setName, isConsequent);
			}
			else
				this->temp_setName = this->temp_setName + " ";
		}
		else {
			this->temp_setName = this->temp_setName + input;

			if (lookAhead(stream, OR_KEYWORD, true)
					|| lookAhead(stream, AND_KEYWORD, true)
					|| lookAhead(stream, THEN_KEYWORD, true)) {
				validateSetName(this->temp_setName, isConsequent);
			} else
				this->temp_setName = this->temp_setName + " ";
		}
	}

}


void RuleAnalyzer::validateSetName(std::string& name, bool isConsequent){
	int temp;
	if (isConsequent)
		temp = verifyConsequentSet(name);
	else
		temp = verifyAntecedentSet(this->temp_LingVarID, name);

	if (temp >= 0) {
		this->temp_set = temp;
		this->temp_setName = "";
		if (isConsequent)
			this->state = SET_CONS_RECOGN_END;
		else
			this->state = SET_RECOGNIZED;
	} else{
		this->state = ERROR;
		LERROR <<  "Set not recognized. Found: "+ name;
	}
}

void RuleAnalyzer::postSetRecognition(std::string& input){
	toLowerCaseSTD(input);
	if (input == THEN_KEYWORD) {
		this->state = START_CONSEQUENT;
	} else if (input == AND_KEYWORD) {
		this->temp_OP = FuzzyRule::AND;
		this->state = START_RULE;
	} else if (input == OR_KEYWORD) {
		this->temp_OP = FuzzyRule::OR;
		this->state = START_RULE;
	}
	else{
		this->state = ERROR;
		LERROR <<  "unrecognized input.";
	}
}


void RuleAnalyzer::printRule(MamdaniRule* rule) {

	std::string description="If ";

	bool success = true;

	for(std::list<std::list<Token> >::const_iterator it = rule->getRuleLogic().begin(); it != rule->getRuleLogic().end(); it++){

		if(it != rule->getRuleLogic().begin())
			description += "or ";

		for(std::list<Token>::const_iterator internalIt = it->begin() ; internalIt!= it->end(); internalIt++){

			if(internalIt != it->begin())
				description += "and ";

			int var = internalIt->variable;
			int set = internalIt->set;
			bool negat = internalIt->negated;

			if(!this->objectInputPtr->getElement(var)->hasSetID(set))
				success = false;

			description += this->objectInputPtr->getElement(var)->getName()+" is ";
			if (negat)
				description +="not ";

			description += this->objectInputPtr->getElement(var)->getSet(set)->getName() + " ";
		}
	}

	description += "then "+ rule->getConsequentVarName() + " is ";
	if(rule->isConsequentNegated())
		description += "not ";
	description += this->outputPtr->getSet(rule->getConsequentSet())->getName();

}

void RuleAnalyzer::resetTempVariables(){

	this->temp_LingVarID = 0;
	this->temp_negated = false;
	this->temp_set = 0;
	this->temp_setName = "";
	this-> temp_varName = "";
}

void RuleAnalyzer::resetMachineState(){
	resetTempVariables();
	this->state = INITIAL;
	this->temp_OP = FuzzyRule::AND;
}

void RuleAnalyzer::setOutputVar(MamdaniOutputVariable* var){
	this->outputPtr = var;
}

bool RuleAnalyzer::lookAhead(istringstream& stream,
		const std::string& toSearch, bool lowerCase) {
	//save the last position

	int position = stream.tellg();
	string ahead;
	stream >> ahead;
	stream.seekg(position);
	if (lowerCase)
		toLowerCaseSTD(ahead);
	return ahead == toSearch;
}

bool RuleAnalyzer::hasAhead(istringstream& stream){
	int position = stream.tellg();
	string ahead;
	bool hasAhead = false;
	if (stream >> ahead)
		hasAhead = true;
	stream.seekg(position);
	stream.clear(); // reset the IOstate if not, it think to be at the end of stream
	return hasAhead;
}

