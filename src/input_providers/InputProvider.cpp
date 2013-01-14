/*
 * InputProvider.cpp
 *
 *  Created on: Dec 6, 2012
 *      Author: igloo
 */

#include "InputProvider.h"

InputProvider::~InputProvider() {
}

void InputProvider::ExtractEntry(std::istream& stream, std::string& obj,
		std::string& var, float& val) const {

	//Initialize, for error control
	obj = "";
	var = "";
	val = NAN;

	std::string value;

	if (getline(stream, obj, ':')
			&& getline(stream, var, ':')
			&& getline(stream, value, ':')){
		val = parsing::extractFloat(value.c_str());
		removePacesStartAndEnd(obj);
		removePacesStartAndEnd(var);
	}
}

void InputProvider::removePacesStartAndEnd(std::string& string) const {

	//from start
	while (string [0] == ' '){
		string.erase(0,1);
	}
	//from end and backward
	while (string[string.size()-1] == ' '){
		string.erase(string.size()-1,1);
	}
}
