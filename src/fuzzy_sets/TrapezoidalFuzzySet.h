/*
 * TrapezoidalFuzzySet.h
 *
 *  Created on: Oct 3, 2012
 *      Author: igloo
 */

#ifndef TRAPEZOIDALFUZZYSET_H_
#define TRAPEZOIDALFUZZYSET_H_

#include "SimplePolygonalFuzzySet.h"
#include "../Utility.h"
#include "../shape/TrapezoidalShape.h"


class TrapezoidalFuzzySet: public SimplePolygonalFuzzySet {

private:

	TrapezoidalShape trapezoid;
	bool initialized;

	bool checkConsistence();

public:

	TrapezoidalFuzzySet();
	TrapezoidalFuzzySet(const std::string& _name);
	TrapezoidalFuzzySet(const std::string& _name, float APoint, float BPoint, float CPoint, float DPoint);


	~TrapezoidalFuzzySet();

	TrapezoidalFuzzySet* clone() const;
	/**
	 * Used to set the value of a trapezoidal fuzzy set.
	 * The point A,B,C, must be growing on the x axys and
	 * only two (A or B) (C or D) can be equal. It can't be modeled
	 * as a rectangular fuzzy set, because a rect set already exists.
	 * @param APoint
	 * @param BPoint
	 * @param CPoint
	 * @param DPOint
	 * @return a boolean that indicate if the assignment is correct.
	 */
	bool setPoints(float APoint, float BPoint, float CPoint, float DPOint);

	/**
	 * Set all the value of a trapezoidal fuzzy set and also set the name.
	 * The point A,B,C must be growing on the x axys and
	 * only two (A or B) (B or C) can be equal.
	 * If the name is an empty string the set'll not be initialized and it'll
	 * give a warning. With an empty name you cannot use the set.
	 *
	 * @param _name
	 * @param Apoint
	 * @param BPoint
	 * @param Cpoint
	 * @param DPoint
	 * @return True if the value is correct and it's assigned. False otherwise
	 */
	bool configureSet(const std::string& _name, float Apoint, float BPoint, float Cpoint, float DPoint);

	 float CalculateMembership (float point) const;

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

#endif /* TRAPEZOIDALFUZZYSET_H_ */
