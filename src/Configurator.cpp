/*
 * Configurator.cpp
 *
 *  Created on: Dec 20, 2012
 *      Author: igloo
 */

#include "Configurator.h"
static const string help="ENGINE DESCRIPTOR--------------------	\n"
		"--xml	<path_to_xml>	provide descriptor of engine with FuzzyWorld xml.\n\n"
		"INPUT DESCRIPTOR---------------------\n"
		"Input syntax: '<object_name>:<variable_name>:>value>'\n"
		"--inputstream	input are passed througn the standard input stream\n"
		"--fileinput	<path_to_file>	input are reader from a text file\n"
		"--stringInput	<input> the input string specify the input\n\n"
		"HELP--------------------------------\n"
		"-h or --help\n\n"
		"VERBOSE-----------------------------\n"
		"-v\n";

bool Configurator::setInputs(FuzzyEngine& engine, GetOpt::GetOpt_pp& options) {

	string input_path = "";
	bool verbose = checkVerbose(options);

	if (options >> GetOpt::OptionPresent("inputStream")) {
		//TODO: implementa
		if(verbose)
		cout << "Read engine description from input stream. \n";
		return true;

	} else if (options >> GetOpt::Option("fileInput", input_path)) {
		//TODO:implementa
		if (verbose)
		cout << "Read engine description from input path: " << input_path
				<< ".\n";
		return true;
	} else if (options >> GetOpt::Option("stringInput", input_path)) {
		if(verbose)
		cout << "Read engine input from command line parameters: "<< input_path<<"\n";
		ManualInputProvider *input = new ManualInputProvider(input_path.c_str());
		engine.setInputProvider(input);
		return true;
	} else {
		cout << "Cannot find a valid input descriptor for the engine\n";
		return false;
	}
}

bool Configurator::createEngine(FuzzyEngine& engine,
		GetOpt::GetOpt_pp& options) {
	//TODO: inserimento logging qui

	string descriptor_path = "";
	bool verbose = checkVerbose(options);


	if (options >> GetOpt::Option("xml", descriptor_path)) {
		if(verbose)
		cout << "Read engine description from xml file: " << descriptor_path
				<< "\n";
		XMLFPCreator *creator = new XMLFPCreator(descriptor_path);
		engine.setEngineCreator(creator);
		return true;
	} else {
		cout << "Please provide a engine descriptor (--xml pathname)\n";
		return false;
	}
}

bool Configurator::checkVerbose(GetOpt_pp& options) {
	if(options >> OptionPresent('v'))
		return true;
	else
		return false;
}

void printHelp(){
	cout<<help;
}

bool Configurator::configure(FuzzyEngine& engine, GetOpt_pp& options) {

	if(options>> OptionPresent('h',"help") ){
		printHelp();
		return false;
	}
	else{
		createEngine(engine, options);
		setInputs(engine,options);
		return true;
	}
}
