/*
 * FuzzyRule.cpp
 *
 *  Created on: Oct 29, 2012
 *      Author: igloo
 */

#include "FuzzyRule.h"


FuzzyRule::FuzzyRule(const std::string& rule) :ruleDescription(rule), andOperator(NULL), orOperator(NULL) {}

FuzzyRule::FuzzyRule() :
		ruleDescription(""), andOperator(NULL), orOperator(NULL) {
}

const std::string& FuzzyRule::getRuleDescription() const {
	return this->ruleDescription;
}
