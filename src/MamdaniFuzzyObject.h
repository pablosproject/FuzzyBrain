/*
 * MamdaniFuzzyObject.h
 *
 *  Created on: Oct 24, 2012
 *      Author: igloo
 */

#ifndef MAMDANIFUZZYOBJECT_H_
#define MAMDANIFUZZYOBJECT_H_

#include "FuzzyObject.h"
#include "linguistic_variables/InputLinguisticVariable.h"
#include "MappedPointersContainer.hpp"
#include "linguistic_variables/MamdaniOutputVariable.h"
#include "fuzzy_rules/FuzzyRule.h"
#include "operator/AndOperator.h"
#include "operator/OrOperator.h"
#include "fuzzy_rules/RulesContainer.h"
#include "operator/ZadehianAnd.h"
#include "operator/ZadehianOr.h"
#include "Utility.h"
#include "fuzzy_rules/RuleAnalyzer.h"
#include "defuzzificators/COSDefuzzificator.h"

struct NestedVar {

	int varID;
	FuzzyObject* nestedVar;

	NestedVar(FuzzyObject* _nestedVar, int _varID) :
		varID(_varID), nestedVar(_nestedVar) {
	}
	NestedVar() :
		varID(-1), nestedVar(NULL) {
	}
};

class MamdaniFuzzyObject: public FuzzyObject {

private:

	MappedPointersContainer<InputLinguisticVariable> inputVars;//Container with all the input variables.
	MamdaniOutputVariable* outputVar;						//Output variable

	vector<NestedVar> nestedVariables;					 //Contain reference to the input nested

	AndOperator* andOP;										//The AND operator
	OrOperator* orOP;										//The OR operator
	Defuzzificator* defuzzificator;							//Defuzzificator set by the fuzzyObject

	RulesContainer rules;					//Container of the rule with a cache
	RuleAnalyzer analyzer;					//FSM that analyze the rule and parse it.


	int getExistentNestedVar(int _varID);
	bool verifyInputVars();

	//ERROR STRING
	const static std::string NOT_INITIALIZED_STRING;

public:

	~MamdaniFuzzyObject();

	/**
	 * Constructor for tha Mamdani Fuzzy Object. It accept as a parameter the output variable,
	 * and the operator of And & Or.
	 * @param _and	The And operator for the selected fuzzy object. Default is ZadehianAnd
	 * @param _or	The Or operator for the selected fuzzy object. Defaul is Zadehian.
	 * @param _out	The output variable for the given fuzzy set. Default value is NULL.
	 * @param _def  The defuzzificator for the selected FuzzyObject.
	 */
	MamdaniFuzzyObject(AndOperator* _and = new ZadehianAnd(), OrOperator* _or =
			new ZadehianOr(), MamdaniOutputVariable* _out = NULL,
			Defuzzificator* _def = new COSDefuzzificator());

	/**
	 *	Insert a linguistic variable inside a fuzzy object.
	 *	In particular the variable to be added:
	 *		- Must not exist in the Object.
	 * @return True if the variable was added correctly or false otherwise.
	 */
	bool addInputVar( InputLinguisticVariable* variable);

	/**
	 * Set the output variable of the fuzzy object. If a variable is already set
	 * for these object it cannot be changhed. When added a output variable,
	 * the object makes a check on all the rule to assure that the consequent
	 * of every rule is the output variable.
	 *
	 * @param _output	Variable to set as output variable of the fuzzy set.
	 * @return			A boolean that express if the insertion was successful.
	 */
	bool setOutputVar(MamdaniOutputVariable* _output);

	/**
	 * Method that add a rule to the fuzzy object.
	 * This method make the parsing of the rule and check the rule
	 * integrity. In case of error in the rule syntax or semantics,
	 * it return false and does not add the rule to the object.
	 * The internal representation of the rule is modified by this method.
	 *
	 * @param rule A pointer to the rule to be added.
	 * @return	A boolean that confirm the operation.
	 */
	bool addRule(MamdaniRule* rule);

	/**
	 * @return The description of the fuzzy object, the name.
	 */
	const std::string& getName() const;

	/**
	 * This function launch the fuzzyfication and defuzzification
	 * process, by using the setted operator of and and or, and
	 * return the result by defuzzifying the output.
	 * @return	The result of the fuzzy inference on the generic fuzzy object. NAN if there's some problem
	 */
	float getOutput();

	const MamdaniOutputVariable* getOutputVar() const;

	/**
	 * Set the value of an input variable. In this case the value is known a-priori,
	 * and it is passed as a float.
	 *
	 * @param varName	The name of the input variable.
	 * @param input_value	The float value used to set the variable.
	 * @return True if the input was properly set, or false if there are some problem, for example
	 * the input variable specified does not exists.
	 */
	bool setInput(const std::string& varName, float input_value);

	/**
	 * Set the value of an input variable. In this case the value is not known, and is
	 * calculated by another fuzzy object.
	 *
	 * @param varName	The name of the input variable.
	 * @param input_value	The float value used to set the variable.
	 * @return True if the input was properly set, or false if there are some problem, for example
	 * the input variable specified does not exists.
	 */
	bool setInput(const std::string& varName, FuzzyObject* object);

	/**
	 * Return the input value for a given variable. If the value is nested, it start the
	 * recursion.
	 * @param varName	The name of the variable.
	 * @return	A float with the value for the input variable. NAN if there's some problem.
	 */
	float getInputValue(const std::string& varName) const;

	/**
	 * Debugging function
	 */
	void printCache() const;

	/**
	 * Return the defuzzificator for the given object
	 * @return
	 */
	const Defuzzificator* getDefuzzificator() const;

	/**
	 * Sets the defuzzificator for the object.
	 * @param defuzzificator
	 */
	void setDefuzzificator(Defuzzificator* defuzzificator);

	//TODO: genera documentazione
	const InputLinguisticVariable* getInputVar(const string& name) const;
};

#endif /* MAMDANIFUZZYOBJECT_H_ */
