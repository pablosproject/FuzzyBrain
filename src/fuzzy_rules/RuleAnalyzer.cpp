/*
 * RuleAnalyzer.cpp
 *
 *  Created on: 01/nov/2012
 *      Author: pablosproject
 */

#include "RuleAnalyzer.h"

log4cplus::Logger RuleAnalyzer::logger = logging::getLogger("RuleAnalyzer");

const std::string RuleAnalyzer::IF_KEYWORD = "if";
const std::string RuleAnalyzer::IS_KEYWORD = "is";
const std::string RuleAnalyzer::AND_KEYWORD = "and";
const std::string RuleAnalyzer::OR_KEYWORD = "or";
const std::string RuleAnalyzer::THEN_KEYWORD = "then";
const std::string RuleAnalyzer::NOT_KEYWORD = "not";

RuleAnalyzer::RuleAnalyzer() :temp_consVar_name(""),
		temp_antLingVar(0), temp_set(0), temp_negated(false), temp_OP(
				FuzzyRule::AND), state(ERROR), objectInputPtr(
				NULL), outputPtr(NULL) {
}

RuleAnalyzer::RuleAnalyzer(
		 MappedPointersContainer< InputLinguisticVariable>* _input,
		 MamdaniOutputVariable* _output) :
		temp_antLingVar(0), temp_set(0), temp_negated(false), temp_OP(
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
		LOG4CPLUS_ERROR(logger, "Rule parser not initialized properly.");
		return false;
	}

	if(rule->getRuleDescription().empty()){
		LOG4CPLUS_ERROR(logger, "Cannot parse an empty string.");
		return false;
	}
	istringstream iss(rule->getRuleDescription());
	std::string token;

	//Parse the string until there are words
	while (iss >> token) {
		nextState(token);

		if (this->state == ERROR) {
			LOG4CPLUS_ERROR(logger, "Error in parsing rule: "+ rule->getRuleDescription());
			rule->resetRule();
			return false;
		}
		else if (this->state == SET_RECOGNIZED){
			if (!rule->addAntecedentToken(temp_antLingVar, temp_set,
					temp_negated, temp_OP))
				return false;
			resetTempVariables();
		}
		else if (this->state == SET_CONS_RECOGN_END)
				if (!rule->addConsequent(temp_consVar_name, temp_set,
						temp_negated))
					return false;
	}

	return true;
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

void RuleAnalyzer::nextState(std::string& input) {
	switch (this->state) {

	case (INITIAL):
		recognizeIf(input);
		break;
	case (START_RULE):
		recognizeVariable(input, false);
		break;
	case (VARIABLE_RECOGNIZED):
		recognizeIs(input, false);
		break;
	case (IS_RECOGNIZED):
		recognizeSet(input, false);
		break;
	case (SET_RECOGNIZED):
		postSetRecognition(input);
		break;
	case (START_CONSEQUENT):
		recognizeVariable(input, true);
		break;
	case (VAR_CONS_RECOGNIZED):
		recognizeIs(input, true);
		break;
	case (IS_CONS_RECOGNIZED):
		recognizeSet(input, true);
		break;
	case (SET_CONS_RECOGN_END):{
		/*
		 * If I enter here the rule is too long, or there's
		 * some error at the end of the string.
		 */
		this->state =ERROR;
		LOG4CPLUS_ERROR(logger, "unexpected end of the rule.");
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
		LOG4CPLUS_ERROR(logger,"Expected If, but found other thing: " + input);
	}
}

void RuleAnalyzer::recognizeVariable(std::string& input, bool isConsequent) {

	if (!isConsequent) {
		int temp = verifyInputVar(input);
		if (temp >= 0) {
			this->temp_antLingVar = temp;
			this->state = VARIABLE_RECOGNIZED;
		} else {
			this->state = ERROR;
			LOG4CPLUS_ERROR(logger, "Input variable not recognized. Found: "+ input);
		}
	} else {
		if (verifyOutputVar(input)) {
			this->temp_consVar_name = input;
			this->state = VAR_CONS_RECOGNIZED;
		}
		else{
			this->state = ERROR;
			LOG4CPLUS_ERROR(logger, "Output variable not recognized. Found: "+ input);
		}
	}
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
		LOG4CPLUS_ERROR(logger, "Expected IS keyword, but found other :" + input);
	}
}

void RuleAnalyzer::recognizeSet(std::string& input, bool isConsequent) {

	std::string input_copy = input;
	toLowerCaseSTD(input_copy);

	if (input_copy == NOT_KEYWORD)//I search for the not keyword. If found stay in these state and then search the set.
		temp_negated = true;		//no change of state

	else {		// If i do not find the not keyword, I search for the set

		int temp;
		if (isConsequent)
			temp = verifyConsequentSet(input);
		else
			temp = verifyAntecedentSet(this->temp_antLingVar, input);

		if (temp >= 0) {
			this->temp_set = temp;
			if (isConsequent)
				this->state = SET_CONS_RECOGN_END;
			else
				this->state = SET_RECOGNIZED;
		} else{
			this->state = ERROR;
			LOG4CPLUS_ERROR(logger, "Set not recognized. Found: "+ input);
		}
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
		LOG4CPLUS_ERROR(logger, "unrecognized input.");
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

	if (!success)
		LOG4CPLUS_TRACE(logger, "Error in print rule");
	else
		LOG4CPLUS_TRACE(logger, description);
}

void RuleAnalyzer::resetTempVariables(){

	this->temp_antLingVar = 0;
	this->temp_consVar_name = "";
	this->temp_negated = false;
	this->temp_set = 0;
}

void RuleAnalyzer::resetMachineState(){
	resetTempVariables();
	this->state = INITIAL;
	this->temp_OP = FuzzyRule::AND;
}

void RuleAnalyzer::setOutputVar(MamdaniOutputVariable* var){
	this->outputPtr = var;
}
