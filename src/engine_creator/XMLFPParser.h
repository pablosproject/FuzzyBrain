/*
 * Parser.h
 *
 *  Created on: Sep 20, 2012
 *      Author: igloo
 */

#ifndef XMLFPPARSER_H_
#define XMLFPPARSER_H_


#include "../lib/pugixml.hpp"
#include <cstring>
#include <iostream>
#include "../MamdaniFuzzyObject.h"
#include "../Utility.h"
#include "../fuzzy_sets/TriangularFuzzySet.h"
#include "../fuzzy_sets/RectangularFuzzySet.h"
#include "../fuzzy_sets/TrapezoidalFuzzySet.h"
#include "../fuzzy_sets/SingletonFuzzySet.h"
#include <stdlib.h>
#include <algorithm>
#include "../FuzzyEngine.h"
#include "../linguistic_variables/InputLinguisticVariable.h"

using namespace pugi;


class XMLFPParser {

private:
	/**
	 * Loop over all the linguistic variables and add it to the object passed as parameter.
	 * @param node
	 * @param object The object which the variables has to be added
	 * @param outputName he name of the consequent, extract from the xml.
	 * @return	True if the operation end successfully, false otherwise.
	 */
	bool loopLinguisticVariables(const xml_node& node, MamdaniFuzzyObject* object, const string& outputName);

	/**
	 * Analyze the single linguistic variable, and decide if it has to be added
	 * as input or output variable for the fuzzy object passed as a parameter.
	 * @param node	xml node
	 * @param object	The object which the variable has to be added
	 * @param outputName	The name of the consequent, extract from the xml.
	 * @return	True if the operation end successfully, false otherwise.
	 */
	bool parseLinguisticVariable (const xml_node& node, MamdaniFuzzyObject* object, const string& outputName);

	/**
	 * Process an input var and add it to the object
	 */
	bool processInputVariable(const xml_node& var_root, MamdaniFuzzyObject* object);
	/**
	 * Process an output var and add it to the object
	 */
	bool processOutputVariable (const xml_node& var_root, MamdaniFuzzyObject* object);

	/**
	 * Parse a fuzzy object as indicated in the FuzzyPlayer XML. Process variables,
	 * set and rules.
	 */
	bool parseFuzzyObject(const xml_node& object_root, MamdaniFuzzyObject* object);

	/**
	 * Loop over all the fuzzy sets, and add it to the passed variable.
	 * @param sets_root	The xml node root of all the sets.
	 * @param variable	Variable to which is added.
	 * @return	True if the operation end successfully, false otherwise.
	 */
	bool loopFuzzySets(const xml_node& sets_root, LinguisticVariable* variable);

	/**
	 * Parse a single fuzzy set and add it to the specified variable.
	 * @param node	The xml node root of the single set.
	 * @param variable	Variable to which is added.
	 * @return	True if the operation end successfully, false otherwise.
	 */
	bool parseFuzzySet (const xml_node& node, LinguisticVariable* variable);

	/**
	 * Loop over all the rues and add it to the fuzzy object passed as a parameter.
	 * @param rules_root	The root of all the rules.
	 * @param object	Object to which is added the rule.
	 * @return	True if the operation end successfully, false otherwise.
	 */
	bool loopRules(const xml_node& rules_root, MamdaniFuzzyObject* object);
	/**
	 * Loop over every knowledge chip
	 * @param applicationRoot	The root of the xml document
	 * @param object 			The MamdaniFuzzyObject that contain the knowledge chips
	 * @param engine			The fuzzy engine to which the knowledge chips are added
	 * @return True if the operation end successfully, false otherwise.
	 */

	bool loopKnowledgeChip(const xml_node& applicationRoot, MamdaniFuzzyObject* object, FuzzyEngine* engine );

	/**
	 * Process a knowledge chip, including all the object that are nested in the chip.
	 * @param chipRoot	The xml node root for the chip.
	 * @param engine	The main fuzzy engine.
	 * @return	The FuzzyObject created by the knowledge chip
	 */
	MamdaniFuzzyObject* processKnowledgeChip(const xml_node& chipRoot, FuzzyEngine* engine);

	/**
	 * Parse a single rule and add it to a object.
	 * @param rules_root	The root of the single rule.
	 * @param object	Object to which is added the rule.
	 * @return	True if the operation end successfully, false otherwise.
	 */
	bool parseRule (const xml_node& node, MamdaniFuzzyObject* object);

	/**
	 * This function correct if the point is outside of the range of the variable.
	 * @param X The point, passed by reference.
	 */
	void correctPoint(float& X, const LinguisticVariable *variable);


	const char_t* consequentNameChip(const xml_node& rules_root);
	const char_t* consequentNameObject(const xml_node& rules_root);

	/**
	 * Function that uniform the name of the token, because in the
	 * knowledge chip the name is different.
	 * @param tokenName The string to be transformed.
	 */
	void uniformTokenName(string& tokenName);

	/**
	 * Function that eliminate "(" and ")" from the
	 * rule.
	 * @param rule The string that contain the rule description.
	 */
	void uniformRuleSintax(string& rule);


public:

	XMLFPParser();
	~XMLFPParser();
	bool Parse(const string& filePath, FuzzyEngine* engine);
};

#endif /* PARSER_H_ */
