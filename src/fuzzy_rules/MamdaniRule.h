/*
 * MamdaniRule.h
 *
 *  Created on: Oct 25, 2012
 *      Author: igloo
 */

#ifndef MAMDANIRULE_H_
#define MAMDANIRULE_H_

/**
 * This class represent a Mamdami rule object. It is made
 * by a series of antecedent and by a consequent.
 *
 * The antecedents are organized as a double list; The first list
 * represent the OR concatenation of token and the inside list is
 * a list that represent AND of different token. In these way is possible
 * to represent the priority between logical operator.
 */

#include "FuzzyRule.h"
#include <list>
#include "../Utility.h"
#include "../linguistic_variables/MamdaniOutputVariable.h"

class MamdaniRule: public FuzzyRule {

private:

	std::list<std::list<Token> > ruleLogic;	 /** A double list. First the OR and then the AND.*/
	std::string consequent_var_name;			/**Name of the consequent variable*/
	int consequent_set;						/**ID of the consequent set*/
	bool consequent_negated;				/**Negation of the consequent*/


	float extractMembership(const std::list<Token>::const_iterator& and_it,
			valueCache& cache) const;

public:

	/**
	 * Blank constructor of a Mamdani Rule. This not initialize the object.
	 * If you create the rule with these method and try to use it, it will give
	 * an error.
	 */
	MamdaniRule();

	/**
	 * Default constructor for a Mamdani Rule. The rule created has to be inserted
	 * in a MamdaniFuzzyObject to be evaluated and used.
	 * @param ruleString	The string that represent the rule.
	 * @note	The string passed has to be a well formatted rule, by expressing
	 * the keyword AND, OR, NOT,  IS, IF and THEN in both upper and lower case case and also IS, IF and THEN.
	 * No brackets are admitted, the rules has to be plain. The consequent of the rule has to be the output
	 * variable of a fuzzy reasoning system.
	 * Example "IF water IS cold AND sea IS blue AND snow IS white OR tree is GREEN THEN consequences  "
	 */
	MamdaniRule(const std::string& ruleString);

	virtual ~MamdaniRule();	//TODO: implementa il distruttore che cancelli tutte le regole

	/**
	 * Add a token to the rule. Does not make any control on the identifiers
	 * of the linguistic variable and set passed.
	 *
	 * @param lingVar	The number that identify the linguistic var. Must be positive and greater or equal 0.
	 * @param set		The number that identify the set in the linguistic var. Must be positive and greater or equal 0.
	 * @param OP		The type of the operator.
	 * @return			A boolean that confirm the operation.
	 */
	bool addAntecedentToken(int _lingVar, int _set, bool _negated, logicalOperator _OP);

	/**
	 * Add the consequent to the fuzzy rule.
	 * @param lingVar	The name of the linguistic variable. Must not be empty.
	 * @param set		The number that identify the set in the linguistic var.
	 * @param negated	Express if the consequent is negated or not
	 * @return			A boolean that confirm the operation.
	 */
	bool addConsequent(const std::string& _lingVarName, int _set, bool _negated);

	/**
	 * This function evaluate all the antecedents of a rule
	 * by combining using and/or the tokens.
	 * @param cache	A reference to the cache of memberships.
	 * @return	An evaluation of the antecedents of the rule. And a negative value if there're some error.
	 *
	 */
	float evaluateAntecedent(valueCache& cache) const;

	/**
	 * Function that modulate the consequent of the rules, based on the value calculated.
	 * @param consequent	The output variable of the system to be modulated.
	 * @param modulationValue	The value of modulation. must be GE than  0 and LE than 1
	 * @return	A boolean that confirm the success of the operation.
	 */
	bool modulateConsequent(MamdaniOutputVariable* consequent, float modulationValue) const;
	/**
	 * Return the token that represent the consequent,
	 * or NULL if the consequent is not set.
	 * @return	The consequent token.
	 */
	const std::string& getConsequentVar() const;

	void setAndOperator(const AndOperator* _and);

	void setOrOperator(const OrOperator* _or);

	/**
	 * Search in the object for a given token of type (Variable IS(NOT) Set).
	 * @param _lingVar	The number that identify the linguistic variable.
	 * @param _set		The number that identify the fuzzy set.
	 * @param negated	Express if the rule to search is negated.
	 * @return			True if find or false otherwise.
	 */
	bool hasAntecedentToken(int _lingVar, int _set, bool _negated) const;

	const std::list<std::list<Token> >& getRuleLogic() const;

	int getConsequentSet() const;

	const std::string& getConsequentVarName() const;

	bool isConsequentNegated() const;

	void resetRule();
};
#endif /* MAMDANIRULE_H_ */
