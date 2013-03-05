/*
 * RectangularFuzzySet.h
 *
 *  Created on: Oct 3, 2012
 *      Author: igloo
 */

#ifndef RECTANGULARFUZZYSET_H_
#define RECTANGULARFUZZYSET_H_

#include "SimplePolygonalFuzzySet.h"
#include "../Utility.h"
#include "../shape/RectangularShape.h"

class RectangularFuzzySet : public SimplePolygonalFuzzySet {

private:

	RectangularShape rectangle;
	bool initialized;

	bool checkConsistence();


public:

	RectangularFuzzySet();
	RectangularFuzzySet(const std::string& _name);
	RectangularFuzzySet(const std::string& _name, float Apoint, float BPoint);

	~RectangularFuzzySet();

	/**
	 * Used to set the value of a rectangular fuzzy set.
	 * The point A,B must be growing on the x axys and
	 * cannot be equal.
	 *
	 * @param APoint
	 * @param BPoint
	 * @return True if the value is correct and it's assigned. False otherwise.
	 */

	bool setPoints(float APoint, float BPoint);

	/**
	 * Set all the value of a Rectangular fuzzy set and also set the name.
	 * The point A,B,C must be growing on the x axys and
	 * only two (A or B) (B or C) can be equal.
	 * If the name is an empty string the set'll not be initialized and it'll
	 * give a warn.
	 *
	 * @param _name
	 * @param Apoint
	 * @param BPoint
	 * @return True if the value is correct and it's assigned. False otherwise
	 */
	bool configureSet(const std::string& _name, float Apoint, float BPoint);

	 float CalculateMembership (float point) const;

	 RectangularFuzzySet* clone() const;

	 float getUpBoundary() const;
	 float getLowBoundary() const;

	 void setName(const std::string& _name);

	float getArea() const;

	 bool mamdaniScale(float value);

	 float getScale() const;

	bool isScaled() const;

	 void resetScale();

	/**
	 * Return the X position of the centroid of the fuzzy set.
	 * @return The position of the centroid or NAN if there're some error.
	 */
	 float getCentroid() const;
};

#endif /* RECTANGULARFUZZYSET_H_ */
