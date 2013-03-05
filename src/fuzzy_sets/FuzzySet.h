/*
 * FuzzySet.h
 *
 *  Created on: Sep 24, 2012
 *      Author: igloo, Paolo Tagliani
 *
 *  This in an abstract class that it is used to create the basis of the different membership function.
 *  in this way is possible to optimize and separate different implementation to calculate membership function.
 */

#ifndef FUZZYSET_H_
#define FUZZYSET_H_

#include <string>
#include "../Utility.h"

class FuzzySet {

private:

protected:

	std::string name;

public:

	FuzzySet(const std::string& _name);

	virtual ~FuzzySet();

	/**
	 * Method that all the classes that subclass the interface has to implement.
	 * It handle error in the fuzzy set by returning a negative value.
	 * If you subclass this base class, you've to grant that the set is build
	 * properly, and that the name of the class is set.
	 *
	 * @param point	The point on the x axis for which calculate the membership
	 * @return	The value of membership for a fuzzy set. A negative value if there's error
	 * 			in the function or in the set.
	 */
	virtual float CalculateMembership(float point) const = 0;

	const std::string& getName() const;

	virtual void setName(const std::string& _name);

	virtual FuzzySet* clone() const = 0;

	/**
	 * Implement these method, so the linguistic variable can know the
	 * boundariy of the set.
	 * If the set is not initialized or is in inconsistent state,
	 * this function must return NaN.
	 *
	 * @return	The lower boundary of the fuzzy set or NaN if there are problems
	 */
	virtual float getLowBoundary() const = 0;

	/**
	 * Implement these method, so the linguistic variable can know the
	 * boundariy of the set.
	 * If the set is not initialized or is in inconsistent state,
	 * this function must return NaN.
	 *
	 * @return	The upper boundary of the fuzzy set or NaN if there are problems
	 */
	virtual float getUpBoundary() const = 0;

	/**
	 * Method that permit to scale (or clip) the current fuzzy set,
	 * to a given value passed as parameter.
	 *
	 * @param value The value to be used to clip the system. Must be less or equal than 1 and greater or equal 0.
	 * @return A pointer to the same object if the scaling does not modify the set, or a new fuzzy set that
	 * 			represent the scaled set.
	 */

	/**
	 * Method that scale the selected fuzzy set.
	 * @param value	The size of the scale. Must be between 0 and 1.
	 * @return	A boolean that confirm the operation.
	 */
	virtual bool mamdaniScale(float value) = 0;

	virtual float getScale() const = 0;

	virtual bool isScaled() const = 0;

	virtual void resetScale() = 0;

	virtual float getArea() const = 0;


	virtual float getCentroid() const = 0;


};

#endif
