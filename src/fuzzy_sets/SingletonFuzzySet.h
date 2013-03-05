/*
ã * SingletonFuzzySet.h
 *
 *  Created on: 08/ott/2012
 *      Author: pablosproject
 */

#ifndef SINGLETONFUZZYSET_H_
#define SINGLETONFUZZYSET_H_

#include "FuzzySet.h"
#include <math.h>
#include "../Utility.h"

class SingletonFuzzySet : public FuzzySet {

private:
	float A;
	bool initialized;
	bool checkConsistence();


public:

	SingletonFuzzySet();
	SingletonFuzzySet(const std::string& _name);
	SingletonFuzzySet(const std::string& _name, float APoint);

	virtual ~SingletonFuzzySet();

	/**
	 * Set the parameter and initialize the fuzzy set.

	 * @param A
	 * @return A boolean that indicate if the operation is successful
	 */
	bool setPoint(float APoint);

	/**
	 * Set all the value of a singleton fuzzy set and also set the name.
	 * If the name is an empty string the set'll not be initialized and it'll
	 * give a warn.
	 *
	 * @param _name
	 * @param Apoint
	 * @return True if the value is correct and it's assigned. False otherwise
	 */
	bool configureSet(std::string& _name, float Apoint);

	virtual float CalculateMembership (float point) const;

	virtual float getUpBoundary() const;
	virtual float getLowBoundary() const;

	virtual void setName(const std::string& _name);

	virtual bool mamdaniScale(float value);
	virtual float getScale() const;
	virtual bool isScaled() const;
	virtual float getArea() const;
	virtual float getCentroid() const;
	virtual void resetScale();

	SingletonFuzzySet* clone() const;


};

#endif /* SINGLETONFUZZYSET_H_ */
