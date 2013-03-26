/*
 * FuzzyObject.h
 *
 *  Created on: Oct 24, 2012
 *      Author: Paolo Tagliani
 *
 */

/**
 *      This is the base abstact interface that represents a generic fuzzy inference system.
 *      A generic inference system is usually composed by a set of rules and by a set of
 *      input/output variable. This interface abstract the basic method that an inference system
 *      has to implement.
 */
#ifndef FUZZYOBJECT_H_
#define FUZZYOBJECT_H_

#include <string>

class FuzzyObject {
public:

	virtual ~FuzzyObject(){};

	/**
	 * This method must be implemented in every subclass.
	 * It basically return the final output of the fuzzy inference system.
	 *
	 * @return The outputa of the fuzzy inference system.
	 */
	virtual float getOutput() = 0;

	/**
	 * Every fuzzy system has to be a name that is used to refer
	 * to it by other fuzzy systems.
	 *
	 * @return A string with the name of the fuzzy inference system.
	 */
	virtual const std::string& getName() const = 0;


};

#endif /* FUZZYOBJECT_H_ */
