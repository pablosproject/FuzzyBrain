//============================================================================
// Name        :
// Author      : Paolo Tagliani
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "lib/getopt/getopt_pp.h"
#include "FuzzyEngine.h"
#include "Configurator.h"


int main(int argc, char* argv[]) {

    using namespace GetOpt;
    GetOpt_pp ops(argc, argv);


    //TODO: configure the defuzzificator
	FuzzyEngine principalEngine;

	if(Configurator::configure(principalEngine,ops))
		cout<< principalEngine.run()<<"\n";
	//TODO: run and return the results or the exit value
}

