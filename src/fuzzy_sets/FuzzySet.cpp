/*
 * FuzzySet.cpp
 *
 *  Created on: Oct 4, 2012
 *      Author: igloo
 */


#include "FuzzySet.h"

log4cplus::Logger FuzzySet::logger_set = logging::getLogger("FuzzySet");

FuzzySet::FuzzySet(const std::string& _name){

	if (_name == "")
		LOG4CPLUS_WARN(this->logger_set,"Name cannot be an empty string. Possible inconsistences.");

	this->name = _name;
}

FuzzySet::~FuzzySet() {
}

const std::string& FuzzySet::getName() const {
	return name;
}

void FuzzySet::setName(const std::string& _name){
	this->name = _name;
}
