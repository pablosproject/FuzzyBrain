/*
 * LinguisticVariable.h
 *
 *  Created on: Oct 10, 2012
 *      Author: igloo
 */

#ifndef LINGUISTICVARIABLE_H_
#define LINGUISTICVARIABLE_H_

#include <map>
#include <vector>
#include <string>
#include "../Utility.h"
#include "../MappedPointersContainer.hpp"
#include "../fuzzy_sets/FuzzySet.h"


class LinguisticVariable {

protected:

	std::string name;
	float min_range;
	float max_range;
	MappedPointersContainer<FuzzySet> sets_data;
	bool initialized;

	FuzzySet* getMutableSet(int id);




public:

	/**
	 * Constructor of a single Linguistic variable.
	 * The only constrain with these constructor is that the minimum
	 * range has to be less and not equal of max range.
	 * @param _name			The name of the variable, mandatory parameter.
	 * @param _min_range	Minimum range if the variable.
	 * @param _max_range	maximum range if the variable.
	 */
	LinguisticVariable(const std::string& _name, float _min_range,
			float _max_range); //TODO: constrolla che il min e il massimo siano corretti
	virtual ~LinguisticVariable();

	/**
	 * Default copy constructor of a linguistic variable, copy all internal
	 * sets and variables.
	 * @param toCopy the object to copy
	 */
	LinguisticVariable(const LinguisticVariable& toCopy);

	/***
	 * Function that calculate the membership of a variable to a fuzzy set,
	 * given a value that indicates the actual value of the variable.
	 * @param setName		Name of the set to be tested
	 * @param inputValue	Value of the variable.
	 * @return	The value of the membership. A negative number if there's an error
	 */
	const float membershipToASet(const std::string& setName,
			float inputValue) const;

	/***
	 * Function that calculate the membership of a variable to a fuzzy set,
	 * given a value that indicates the actual value of the variable.
	 * @param set_ID		ID of the set to be tested
	 * @param inputValue	Value of the variable.
	 * @return	The value of the membership. A negative number if there's an error
	 */
	const float membershipToASet(const int set_ID, float inputValue) const;

	/**
	 * Permit to add a set to a variable, by passing it.
	 * This function controls that the created set is valid for the current variable:
	 *
	 * 	-The name of the set must not exist in these variable.
	 * 	-The set value has to be inside the variables value.
	 *
	 * @param setToAdd The fuzzy set to add.
	 * @return	True if the set is correctly added, false otherwise.
	 */
	bool addSet(FuzzySet* setToAdd);

	bool hasSet(const std::string& name) const;

	bool hasSetID(int id) const;

	/**
	 *  Get from the internal data structure an ID for the Fuzzy Set.
	 *
	 * @param name
	 * @return	The ID of the set if exists, or a number <0 if not exists.
	 */
	int getSetID(const std::string& name) const;

	const FuzzySet* getSet(const std::string& name)const;

	const FuzzySet* getSet(int id)const;

	float getMaxRange() const;
	float getMinRange() const;

	const std::string& getName() const;

	bool checkConsistence() const;

	int getNumberOfSet() const;
};

#endif /* LINGUISTICVARIABLE_H_ */

