//============================================================================
// Name        :
// Author      : Paolo Tagliani
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "lib/getopt_pp.h"
#include "FuzzyEngine.h"
#include "Configurator.h"
#include "lib/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]) {

	using namespace GetOpt;
	GetOpt_pp ops(argc, argv);


	//Check if the use want help
	if (!Configurator::checkHelp(ops)) {

		//TODO: configure the defuzzificator
		FuzzyEngine principalEngine;

		//If the result of the configurator is less than 0 there's some error
		int configuration_res = Configurator::configure(principalEngine, ops);

		if ( configuration_res > 0){
			float run_result = principalEngine.run();
			if (run_result > 0){
				cout << run_result;
				_END_EASYLOGGINGPP
				return 0;
			}
			else
				_END_EASYLOGGINGPP
				return run_result; //TODO: manage different cases
		}
		else
		{
			_END_EASYLOGGINGPP
			return configuration_res;
			//TODO: return the exit code and manage the log
		}
	}

}

