/*
 * RuleAnalyzer.h
 *
 *  Created on: 01/nov/2012
 *      Author: pablosproject
 */

/**
 * Class that contain s Finite State Machine, that
 * make the parsing of a given rule passed as a parameter,
 * and modify the internal structure of the rule by adding token
 * to the antecedents and consequent.
 */
#ifndef RULEANALYZER_H_
#define RULEANALYZER_H_

#include "MamdaniRule.h"
#include "../MappedPointersContainer.hpp"
#include "../linguistic_variables/MamdaniOutputVariable.h"
#include "../linguistic_variables/InputLinguisticVariable.h"
#include "../Utility.h"
#include <algorithm>
#include <string>
#include <sstream>

class RuleAnalyzer {

private:

	/**
	 * Magic keywords
	 */
	static const std::string IF_KEYWORD;
	static const std::string IS_KEYWORD;
	static const std::string AND_KEYWORD;
	static const std::string OR_KEYWORD;
	static const std::string THEN_KEYWORD;
	static const std::string NOT_KEYWORD;

	/**
	 * Stores the temporal value of the rule
	 */
	std::string temp_varName;
	std::string temp_setName;

	int temp_LingVarID;
	int temp_set;
	bool temp_negated;
	FuzzyRule::logicalOperator temp_OP;

	enum {
		INITIAL,               //!< INITIAL
		START_RULE,            //!< START_RULE
		VARIABLE_RECOGNIZED,   //!< VARIABLE_RECOGNIZED
		IS_RECOGNIZED,		   //!< IS_RECOGNIZED
		SET_RECOGNIZED,        //!< SET_RECOGNIZED
		START_CONSEQUENT,      //!< START_CONSEQUENT
		VAR_CONS_RECOGNIZED,
		IS_CONS_RECOGNIZED,
		SET_CONS_RECOGN_END,					   //!< END
		ERROR
	}state;

	 MappedPointersContainer< InputLinguisticVariable>* objectInputPtr;	/**Reference of a container's input variables.*/
	 MamdaniOutputVariable* outputPtr;	/**Reference of a container's output variable.*/

	/**
	 * Reset the state machine before a new parsing.
	 */
	void reset();

	void toLowerCaseSTD(std::string &str);

	/**
	 * Verify that an input variable exists in the container
	 * @param varName	the name of the variavble
	 * @return The ID of the variable or a negative value in case of error
	 */

	/**
	 * Verify that an output variable is in the rule
	 * @param outputVar	the name of the variable
	 * @return	The ID of the variable or a negative value in case of error
	 */
	bool verifyOutputVar(const std::string& outputVar) const;

	/**
	 * Verify if a set is inside an input variable.
	 * @param varID	The id of the variable
	 * @param name	the name of the set
	 * @return	The ID of the set or a negative value in case of error
	 */

	int verifyConsequentSet(const std::string& name);

	void recognizeIf(std::string& input);

	void recognizeVariable(std::string& input, bool isConsequent, istringstream& stream);

	void recognizeIs(std::string& input, bool isConsequent);

	void recognizeSet(std::string& input, bool isConsequent, istringstream& stream);

	void nextState(std::string& input, istringstream& stream);

	int verifyInputVar(const std::string& varName) const;

	int verifyAntecedentSet(int varID, std::string& name) const;

	void postSetRecognition(std::string& input);

	void resetTempVariables();

	void resetMachineState();

	void validateVariable(bool isConsequent, const std::string& inputVarName);

	/**
	 * Implement a simple lookahead function that search ahead
	 * for a giuven string
	 * @param stream	The streram to which find the string
	 * @param toSearch	The string to search
	 * @param lowerCase Convert the string to search in lowercase
	 * @return	True if the string is found or false otherwise
	 */
	bool lookAhead(istringstream& stream, const std::string& toSearch,  bool lowerCase);

	bool hasAhead(istringstream& stream);

	void validateSetName(std::string& name, bool isConsequent);


public:

	RuleAnalyzer();
	RuleAnalyzer( MappedPointersContainer<InputLinguisticVariable>* _input,  MamdaniOutputVariable* _output);
	virtual ~RuleAnalyzer();

	/**
	 * Method that parse the rule passed as pointed parameter. It analyze
	 * all the rule and modify the internal representation of the rule.
	 * @param rule	A pointer to the rule to be parsed.
	 * @return		A boolean that confirm the good exit of the operation.
	 */
	bool parseRule(MamdaniRule* rule);

	void printRule(MamdaniRule* rule);

	void setOutputVar(MamdaniOutputVariable* var);
};

#endif /* RULEANALYZER_H_ */
