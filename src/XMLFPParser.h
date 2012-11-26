/*
 * Parser.h
 *
 *  Created on: Sep 20, 2012
 *      Author: igloo
 */

#ifndef PARSER_H_
#define PARSER_H_


#include "lib/pugixml.hpp"
#include <iostream>

static const char* APPLICATION_TAG = "Application";
static const char* LINGUISTIC_VARIABLE_TAG = "FuzzyFunction";
static const char* LINGUISTIC_VARIABLE_ID_TAG = "FuzzyFunctionId";
static const char* LINGUISTIC_VARIABLE_SETS_TAG = "FuzzyValues";
static const char* LINGUISTIC_VARIABLE_SET_TAG = "FuzzyValue";
static const char* LINGUISTIC_VARIABLE_SET_DEFINITION_TAG = "FuzzyValueMagnitude";
static const char* LINGUISTIC_VARIABLE_SET_POINT_A_TAG = "Avalue";
static const char* LINGUISTIC_VARIABLE_SET_POINT_B_TAG = "Bvalue";
static const char* LINGUISTIC_VARIABLE_SET_POINT_C_TAG = "Cvalue";
static const char* LINGUISTIC_VARIABLE_SET_POINT_D_TAG = "Dvalue";
static const char* RULES_TAG = "FuzzyRules";
static const char* RULE_TAG = "FuzzyRuleLine";
static const char* RULE_ANTECEDENT_TAG = "Antecedent";
static const char* RULE_TOKENS_TAG = "TokenCollection";
static const char* RULE_TOKEN_TAG = "Token";
static const char* RULE_OPERATOR_TAG = "Connector";





class XMLFPParser {

private:

	pugi::xml_document document;
	void parseLinguisticVariable (const pugi::xml_node* node);
	void parseFuzzySet (const pugi::xml_node* node);
	void parseRule (const pugi::xml_node *node);
	void parseToken (const pugi::xml_node* node);


public:

	XMLFPParser();
	~XMLFPParser();
	bool Parse(const std::string& filePath);
};

#endif /* PARSER_H_ */
