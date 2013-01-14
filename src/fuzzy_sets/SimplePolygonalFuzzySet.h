/*
 * SimplePolygonalFuzzySet.h
 *
 *  Created on: Nov 15, 2012
 *      Author: igloo
 */

#ifndef SIMPLEPOLYGONALFUZZYSET_H_
#define SIMPLEPOLYGONALFUZZYSET_H_

#include "FuzzySet.h"

class SimplePolygonalFuzzySet: public FuzzySet {

public:
	SimplePolygonalFuzzySet(const std::string& _name);
	virtual ~SimplePolygonalFuzzySet();

	virtual float getArea() const = 0;

	virtual float getLowBoundary() const = 0;

	virtual float getUpBoundary() const = 0;

	virtual bool mamdaniScale(float value) = 0;

	virtual float CalculateMembership(float point) const = 0;

	virtual float getCentroid() const = 0;

	virtual float getScale() const = 0;

	virtual bool isScaled() const = 0;

	virtual void resetScale() = 0;

};

#endif /* SIMPLEPOLYGONALFUZZYSET_H_ */
