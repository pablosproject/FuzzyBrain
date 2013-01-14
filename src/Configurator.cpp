/*
 * Configurator.cpp
 *
 *  Created on: Dec 20, 2012
 *      Author: igloo
 */
#include "Configurator.h"
//Declaration of constant used to return value
static const int OK = 1;

static const string help =
		"ENGINE DESCRIPTOR--------------------	\n"
				"--xml	<path_to_xml>	provide descriptor of engine with FuzzyWorld xml.\n\n"
				"INPUT DESCRIPTOR---------------------\n"
				"Input syntax: '<object_name>:<variable_name>:>value>;'\n"
				"--inputstream	input are passed througn the standard input stream\n"
				"--fileinput	<path_to_file>	input are reader from a text file\n"
				"--stringInput	<input> the input string specify the input\n\n"
				"DEFUZZIFICATION METHOD----------------\n"
				"--dm <method> --do <option> specify the defuzzification method; Available methods:"
				"		cs = Center of sum, takes no option"
				"		cog = Center of gravity or centroid. Takes as arguments the number"
				"			  of sample used to integrate the output linguistic variable."
				"If not specified the standard is the CENTER OF SUM"
				"HELP--------------------------------\n"
				"-h or --help\n\n"
				"VERBOSE-----------------------------\n"
				"-v\n";

bool Configurator::setInputs(FuzzyEngine& engine, GetOpt::GetOpt_pp& options) {

	string input_path = "";

	bool verbose = checkVerbose(options);

	if (options >> GetOpt::OptionPresent("inputStream")) {
		//TODO: implementa
		if (verbose)
			cout << "Read engine description from input stream. \n";
		return true;

	} else if (options >> GetOpt::Option("fileInput", input_path)) {
		//TODO:implementation
		if (verbose)
			cout << "Read engine description from input path: " << input_path
					<< ".\n";
		return true;
	} else if (options >> GetOpt::Option("stringInput", input_path)) {
		if (verbose)
			cout << "Read engine input from command line parameters: "
					<< input_path << "\n";
		ManualInputProvider *input = new ManualInputProvider(
				input_path.c_str());
		engine.setInputProvider(input);
		return true;
	}else {
		cout << "Cannot find a valid input descriptor for the engine\n";
		return false;
	}
}

bool Configurator::createEngine(FuzzyEngine& engine,
		GetOpt::GetOpt_pp& options) {
	//TODO: inserimento logging qui

	string descriptor_path = "";
	Defuzzificator *engineDefuzzificator;

	bool verbose = checkVerbose(options);
	bool defuzzifier_specified = checkDefuzzificator(options);

	if (defuzzifier_specified){
		engineDefuzzificator = getDefuzzifier(engine, options, verbose);
		if (!engineDefuzzificator)
			return false;
	}
	else
		engineDefuzzificator = new COSDefuzzificator();

	if (options >> GetOpt::Option("xml", descriptor_path)) {
		if (verbose)
			cout << "Read engine description from xml file: " << descriptor_path
					<< "\n";
		XMLFPCreator *creator = new XMLFPCreator(descriptor_path, engineDefuzzificator);
		engine.setEngineCreator(creator);
		return true;
	} else {
		cout << "Please provide a engine descriptor (--xml pathname)\n";
		return false;
	}
}

bool Configurator::checkVerbose(GetOpt_pp& options) {
	if (options >> OptionPresent('v'))
		return true;
	else
		return false;
}

void printHelp() {
	cout << help;
}

int Configurator::configure(FuzzyEngine& engine, GetOpt_pp& options) {

	if (!createEngine(engine, options))
		return LOADING_AND_CREATING_ENGINE_ERROR;
	if (!setInputs(engine, options))
		return INPUT_SETUP_ERROR;
	return OK;
}

bool Configurator::checkHelp(GetOpt_pp& options) {
	if (options >> OptionPresent('h', "help")) {
		printHelp();
		return true;
	} else
		return false;
}

bool Configurator::checkDefuzzificator(GetOpt_pp& options){
		if(options>>GetOpt::OptionPresent("dm"))
			return true;
		else
			return false;
}

Defuzzificator* Configurator::getDefuzzifier(FuzzyEngine& engine, GetOpt_pp& options, bool verbose){

	string defuzz_method = "";
	int defuzz_opt;

	if(options>>GetOpt::Option("dm",defuzz_method)){
		if(defuzz_method == "cs"){
			if(verbose)
				cout <<"Selected defuzzification method center of sum. \n";
			return new COSDefuzzificator();
		}
		else if (defuzz_method == "cog"){
			if(verbose)
				cout <<"Selected defuzzification method center of gravity. \n";
			if (options >> GetOpt::Option("do",defuzz_opt)){
				if (verbose)
					cout << "Number of sample for the defuzzification: " <<defuzz_opt<<" \n";
				CentroidDefuzzificator* defuzz = new CentroidDefuzzificator(defuzz_opt);
				return defuzz;
			}
			else{
				if (verbose)
					cout << "Default Number of sample for the defuzzification: 100 \n";
				CentroidDefuzzificator* defuzz = new CentroidDefuzzificator();
				return defuzz;
			}
		}
		else{
			cout <<"Not valid defuzzification method: "<< defuzz_method<<"\n";
			return NULL;
		}
	}
	else{
		if (verbose)
				cout << "Defuzzification method not specified, using default CoS.";
		return NULL;
	}
}
