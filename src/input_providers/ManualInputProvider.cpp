/*
 * ManualInputProvider.cpp
 *
 *  Created on: Dec 6, 2012
 *      Author: igloo
 */

#include "ManualInputProvider.h"


using namespace std;

ManualInputProvider::~ManualInputProvider() {
	// TODO Auto-generated destructor stub
}


ManualInputProvider::ManualInputProvider(): input("") {}

ManualInputProvider::ManualInputProvider(const char* in){
	this->input = string (in);
}

bool ManualInputProvider::processInput(FuzzyEngine* engine) {

	if(!this->input.empty()){

		istringstream ss1 (string(this->input));
		string entry;

		string obj;
		string var;
		float value;

		while( getline(ss1,entry,';')){
			istringstream ss2(entry);
			ExtractEntry(ss2, obj, var, value);

			//Control over parsing results
			if(obj=="" || var =="" || notNumber::checkNaN(value)){
				LERROR <<"Error during parsing the input: " << entry;
				return false;
			}
			else{
				if (!engine->setinput(obj,var,value)){
					LERROR <<"Error during parsing the input, could not add: " << entry;
					return false;
				}
			}
		}
	}
	else{
		LERROR <<"Input inexistent.";
		return false;
	}

	//all success-->exit true
	return true;
}
