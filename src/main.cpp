//============================================================================
// Name        :
// Author      : Paolo Tagliani
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "MamdaniFuzzyObject.h"
#include "fuzzy_sets/TriangularFuzzySet.h"
#include "fuzzy_sets/TrapezoidalFuzzySet.h"
#include "defuzzificators/CentroidDefuzzificator.h"
#include "lib/getopt/getopt_pp.h"
#include "FuzzyEngine.h"
#include "engine_creator/XMLFPParser.h"


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

bool createEngine(FuzzyEngine& engine, GetOpt::GetOpt_pp& options){
	//TODO: inserimento logging qui
	string descriptor_path = "";

	if(options >> GetOpt::Option("xml", descriptor_path))
	{
		cout << "Read engine description from xml file. "<< descriptor_path<<"\n";
		//setta in modo che il motore venga configurato, e se tutto a posto fai.
		return true;
	}
	else
	{
		cout <<"Argomento errato: descrizione del motore non pervenuta.\n";
		return false;
	}
}
/**
 * Function that parse the parameters and react to the option passed for the input.
 * It automatically creates the engine's input provider and launch the input parsing.
 * @param engine	The fuzzy engine already constructed.
 * @param options	The command line options
 * @return	A boolean to indicate the success of the operation.
 */
bool setInputs(FuzzyEngine& engine, GetOpt::GetOpt_pp& options){

	string input_path = "";

	if(options >> GetOpt::OptionPresent("inputStream"))
	{
		cout << "Read engine description from input stream. \n";
		return true;

	}
	else if(options >> GetOpt::Option("fileInput", input_path))
	{
		cout << "Read engine description from input path: " << input_path <<".\n";
		return true;
	}
	else if(options >> GetOpt::OptionPresent("stringInput")){
		cout << "Read engine input from command line parameter. \n" ;
	}
	else{
		cout << "Cannot find a valid input descriptor for the engine";
		return false;
	}

}

int main(int argc, char* argv[]) {

	XMLFPParser parser = XMLFPParser();
	parser.Parse("FormaFisica.xml",NULL);
}

