//============================================================================
// Name        :
// Author      : Paolo Tagliani
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
<<<<<<< HEAD
#include "MamdaniFuzzyObject.h"
#include "fuzzy_sets/TriangularFuzzySet.h"
#include "fuzzy_sets/TrapezoidalFuzzySet.h"
#include "defuzzificators/CentroidDefuzzificator.h"

=======
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
>>>>>>> de9151170be91f346d2f0cb77ba7185c4eaa0a41

using namespace std;


void testCentroid(){
	MamdaniFuzzyObject* calculator = new MamdaniFuzzyObject();

			//A perfect reply of the calculator example
			InputLinguisticVariable* x = new InputLinguisticVariable("x",-10,10);
			TrapezoidalFuzzySet* negative = new TrapezoidalFuzzySet("Negative", -10, -10, -1, 0);
			TriangularFuzzySet* zero = new TriangularFuzzySet("Zero", -1,0,1);
			TrapezoidalFuzzySet* positive = new TrapezoidalFuzzySet("Positive", 0,1,10,10);

			x->addSet(negative);
			x->addSet(zero);
			x->addSet(positive);

			MamdaniOutputVariable* y = new MamdaniOutputVariable("y", -3,3);
			TriangularFuzzySet* negative_2 = new TriangularFuzzySet("Negative", -2, -1, 0);
			TriangularFuzzySet* positive_2 = new TriangularFuzzySet("Positive", 0,1,2);
			TriangularFuzzySet* largenegative = new TriangularFuzzySet("Largenegative", -3, -2, -1);
			TriangularFuzzySet* largepositive = new TriangularFuzzySet("Largepositive",1,2,3);



			y->addSet(negative_2);
			y->addSet(zero);
			y->addSet(positive_2);
			y->addSet(largenegative);
			y->addSet(largepositive);

			InputLinguisticVariable* z = new InputLinguisticVariable("z", -10, 10);

			z->addSet(negative);
			z->addSet(zero);
			z->addSet(positive);

			calculator->addInputVar(x);
			calculator->setOutputVar(y);
			calculator->addInputVar(z);

			//adding rules
			calculator->addRule(new MamdaniRule("IF x IS Zero AND z IS Negative THEN y IS Negative"));
			calculator->addRule(new MamdaniRule("IF x IS Negative AND z IS Negative THEN y IS Largenegative"));
			calculator->addRule(new MamdaniRule("IF x IS Negative AND z IS Zero THEN y IS Negative"));
			calculator->addRule(new MamdaniRule("IF x IS Negative AND z IS Positive THEN y IS Zero"));
			calculator->addRule(new MamdaniRule("IF x IS Zero AND z IS Zero THEN y IS Zero"));
			calculator->addRule(new MamdaniRule("IF x IS Zero AND z IS Positive THEN y IS Positive"));
			calculator->addRule(new MamdaniRule("IF x IS Positive AND z IS Negative THEN y IS Zero"));
			calculator->addRule(new MamdaniRule("IF x IS Positive AND z IS Zero THEN y IS Positive"));
			calculator->addRule(new MamdaniRule("IF x IS Positive AND z IS Positive THEN y IS Largepositive"));

			calculator->setInput("x", 1);
			calculator->setInput("z",1);

			CentroidDefuzzificator* defuz = new CentroidDefuzzificator(100);
			calculator->setDefuzzificator(defuz);

		    std::cout << "Output: "<< calculator->getOutput();
}

int main() {

<<<<<<< HEAD
	testCentroid();
=======
	XMLFPParser	parser = XMLFPParser();
<<<<<<< HEAD
	parser.Parse("/Users/igloo/Downloads/FormaFisica.xml", NULL);
=======
	FuzzyEngine engine = FuzzyEngine();
	parser.Parse("/Users/igloo/Downloads/FormaFisica.xml", &engine);
>>>>>>> Reoganization and partial XML parser implementation
>>>>>>> de9151170be91f346d2f0cb77ba7185c4eaa0a41
}

