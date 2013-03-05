/*
 * InputProvider.h
 *
 *  Created on: Dec 6, 2012
 *      Author: igloo
 */
#ifndef INPUTPROVIDER_H_
#define INPUTPROVIDER_H_
#include "../Utility.h"
#include <iostream>
#include "../FuzzyEngine.h"


class InputProvider {

protected:
	/**
	 * Function that accept an input stream as an input
	 * and parse the result, by returning the names and
	 * a float
	 * @param stream	The stream containing a single entry
	 * @return	A boolean that confirm the operation
	 */
	void ExtractEntry(std::istream& stream, std::string& obj, std::string& var, float& val ) const;

	void removePacesStartAndEnd(std::string& string) const;

public:

	virtual ~InputProvider();
	virtual bool processInput(FuzzyEngine* engine) = 0;

};


#endif /* INPUTPROVIDER_H_ */
