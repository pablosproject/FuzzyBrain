/*
 * RulesContainer.h
 *
 *  Created on: Oct 25, 2012
 *      Author: igloo
 */

#ifndef RULESCONTAINER_H_
#define RULESCONTAINER_H_
#include <vector>
#include "../fuzzy_rules/MamdaniRule.h"
#include "../linguistic_variables/MamdaniOutputVariable.h"
#include "../linguistic_variables/InputLinguisticVariable.h"
#include "../Utility.h"
#include "../MappedPointersContainer.hpp"

class RulesContainer {

private:

	//Vector used for caching the vaue of set pre-calculated and passed to the rule
	valueCache values;
	std::vector <MamdaniRule*> rules;	//The rules that are in the container
	//TODO:Manage the memory delle rule. Le cancella solo il container

	/**
	 * Fill the cache vector with all the precalculated value for a given input
	 */
	bool createCache(const MappedPointersContainer <InputLinguisticVariable>& input);

public:

	~RulesContainer();
	RulesContainer();

	void addRule(MamdaniRule* rule);

	void setOutput(MamdaniOutputVariable* output);

	/**
	 * This method starts the evaluation of the antecedents on all the rules in the container.
	 *@param The vector that contains the input values of all the variables.
	 * @return A boolean that indicates if the operation was done correctly.
	 */
	bool evaluateRules(const MappedPointersContainer <InputLinguisticVariable>& input, MamdaniOutputVariable* out);

	void printCache() const;
};

#endif /* RULESCONTAINER_H_ */
