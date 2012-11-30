/*
 * Parser.h
 *
 *  Created on: Sep 20, 2012
 *      Author: igloo
 */

#ifndef XMLFPPARSER_H_
#define XMLFPPARSER_H_


#include "lib/pugixml.hpp"
#include <iostream>
#include "MamdaniFuzzyObject.h"
#include "Utility.h"
#include "TriangularFuzzySet.h"
#include "RectangularFuzzySet.h"
#include "TrapezoidalFuzzySet.h"
#include <stdlib.h>

using namespace pugi;


class XMLFPParser {

private:

	bool parseLinguisticVariable (const xml_node& node, MamdaniFuzzyObject* object, const string& outputName);
	bool parseFuzzySet (const pugi::xml_node& node, LinguisticVariable* variable);
	void parseRule (const pugi::xml_node *node);
	void parseToken (const pugi::xml_node* node);
	void uniformTokenName(std::string& tokenName);
	bool parseFuzzyObject(const xml_node& object_root, MamdaniFuzzyObject* object);
	/**
	 * This function correct if the point is outside of the range of the variable.
	 * @param X The point, passed by reference.
	 */
	void correctPoint(float& X, const LinguisticVariable *variable);
	const pugi::char_t* consequentNameChip(const xml_node& rules_root);
	const pugi::char_t* consequentNameObject(const xml_node& rules_root);


	//logger
	static log4cplus::Logger logger;


public:

	XMLFPParser();
	~XMLFPParser();
	bool Parse(const std::string& filePath);
};

#endif /* PARSER_H_ */
