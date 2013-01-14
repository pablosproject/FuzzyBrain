/*
 * FuzzyRule.h
 *
 *  Created on: Oct 25, 2012
 *      Author: igloo
 */


/**
 * This class represent a single rule in the fuzzy expert system.
 * A rule is made by a series of antecedents and a consequent.
 * This is a generic base class, since there are different type of rule, for example
 * the consequent are different using Mamdami and Tagaki-Sugeno inference.
 * This class contain only a pointer to the and and or operator, that is defined
 * and stored in the conatiner of the rules.
 */
#ifndef FUZZYRULE_H_
#define FUZZYRULE_H_
#include "../operator/AndOperator.h"
#include "../operator/OrOperator.h"
#include <string>

	/**
	 * This represent a single token in the rule.A token represent the
	 * preposition "if LINGUISTIC_VARIABLE is FUZZY_SET"
	 */
	struct Token{
		int variable;	/** Is the linguistic variable to be evaluated.*/
		int set;		/** Is the set.*/
		bool negated;

		Token():variable(-1),set(-1), negated(false){} /**Constructor. By default the value are negative.*/
	};

class FuzzyRule {

protected:

	std::string ruleDescription;			//The string representation of the rule.
	const AndOperator* andOperator;			//definition of AND and OR function for the rule.
	const OrOperator* orOperator;

public:



	enum logicalOperator{AND,
						OR	};

	FuzzyRule();
	FuzzyRule(const std::string& rule);

	virtual ~FuzzyRule() {};

	const std::string& getRuleDescription() const;





};

#endif /* FUZZYRULE_H_ */
