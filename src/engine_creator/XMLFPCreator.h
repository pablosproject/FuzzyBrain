/*
 * XMLFPCreator.h
 *
 *  Created on: Nov 26, 2012
 *      Author: igloo
 */

#ifndef XMLFPCREATOR_H_
#define XMLFPCREATOR_H_

#include "EngineCreator.h"
#include "XMLFPParser.h"
#include <string>
#include "../defuzzificators/Defuzzificator.h"


class XMLFPCreator: public EngineCreator {
private:

	std::string pathName;
	Defuzzificator* engineDefuzzificator;

public:
	XMLFPCreator(const std::string& XMLPathName, Defuzzificator* defuzz = new COSDefuzzificator);
	~XMLFPCreator();

	bool createEngine(FuzzyEngine* engine) const;
};

#endif /* XMLFPCREATOR_H_ */
