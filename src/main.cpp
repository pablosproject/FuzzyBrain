//============================================================================
// Name        : igloo.cpp
// Author      : Paolo Tagliani
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
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

using namespace std;

int main() {

	XMLFPParser parser = XMLFPParser();
	parser.Parse("/Users/igloo/DOcuments/workspace/FuzzyTrainer/FormaFisica.xml");
	return 0;
}
