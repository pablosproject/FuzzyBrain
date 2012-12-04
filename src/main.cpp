//============================================================================
// Name        :
// Author      : Paolo Tagliani
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
<<<<<<< HEAD
#include "XMLFPParser.h"
#include <log4cplus/loggingmacros.h>
#include "FuzzyLogger.h"
#include "Utility.h"
#include "RuleAnalyzer.h"
#include "MamdaniRule.h"
#include "LinguisticVariable.h"
#include "TriangularFuzzySet.h"
#include "RectangularFuzzySet.h"
#include "MappedContainer.hpp"
#include "MamdaniOutputVariable.h"
#include "MamdaniFuzzyObject.h"
#include "TrapezoidalFuzzySet.h"
=======
#include "engine_creator/XMLFPParser.h"
>>>>>>> Reoganization and partial XML parser implementation

using namespace std;

int main() {

	XMLFPParser	parser = XMLFPParser();
<<<<<<< HEAD
	parser.Parse("/Users/igloo/Downloads/FormaFisica.xml", NULL);
=======
	FuzzyEngine engine = FuzzyEngine();
	parser.Parse("/Users/igloo/Downloads/FormaFisica.xml", &engine);
>>>>>>> Reoganization and partial XML parser implementation
}
