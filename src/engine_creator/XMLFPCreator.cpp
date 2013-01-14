/*
 * XMLFPCreator.cpp
 *
 *  Created on: Nov 26, 2012
 *      Author: igloo
 */

#include "XMLFPCreator.h"

XMLFPCreator::XMLFPCreator(const std::string& XMLPathName, Defuzzificator* defuzz): pathName(XMLPathName), engineDefuzzificator(defuzz){}

XMLFPCreator::~XMLFPCreator() {
	delete (engineDefuzzificator);
}

bool XMLFPCreator::createEngine(FuzzyEngine* engine) const {
	XMLFPParser parser = XMLFPParser();

	if (parser.Parse(this->pathName, engine)){
		engine->setAllDefuzzificator(engineDefuzzificator);
		return true;
	}
	else
		return false;
}
