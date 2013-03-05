/*
 * Configurator.h
 *
 *  Created on: Dec 20, 2012
 *      Author: igloo
 */

#ifndef CONFIGURATOR_H_
#define CONFIGURATOR_H_
#include <string>
#include <iostream>
#include "lib/getopt_pp.h"
#include "FuzzyEngine.h"
#include "input_providers/ManualInputProvider.h"
#include "engine_creator/XMLFPCreator.h"
#include "ErrorDefinition.h"
#include "defuzzificators/CentroidDefuzzificator.h"

namespace Configurator {

using namespace GetOpt;
/**
 * Function that parse the parameters and react to the option passed for the input.
 * It automatically creates the engine's input provider and launch the input parsing.
 * @param engine	The fuzzy engine already constructed.
 * @param options	The command line options
 * @return	A boolean to indicate the success of the operation.
 */
bool setInputs(FuzzyEngine& engine, GetOpt_pp& options);

bool createEngine(FuzzyEngine& engine, GetOpt_pp& options);

bool checkVerbose(GetOpt_pp& options);

int configure(FuzzyEngine& engine, GetOpt_pp& options);

bool checkHelp(GetOpt_pp& options);

Defuzzificator* getDefuzzifier(FuzzyEngine& engine, GetOpt_pp& options,
		bool verbose);

bool checkDefuzzificator(GetOpt_pp& options);

} /* namespace Configurator */
#endif /* CONFIGURATOR_H_ */
