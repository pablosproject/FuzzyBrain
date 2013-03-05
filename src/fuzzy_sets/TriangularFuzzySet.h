/*
 * TriangularFuzzySet.h
 *
 *  Created on: Sep 24, 2012
 *      Author: igloo
 */

#ifndef TRIANGULARFUZZYSET_H_
#define TRIANGULARFUZZYSET_H_

#include "SimplePolygonalFuzzySet.h"
#include "../Utility.h"
#include "../shape/TriangularShape.h"

#include <math.h>

class TriangularFuzzySet : public SimplePolygonalFuzzySet {
private:

	TriangularShape triangle;
	bool initialized;


	bool checkConsistence();


public:

	TriangularFuzzySet();
	TriangularFuzzySet(const std::string& _name);
	TriangularFuzzySet(const std::string& _name,  float Apoint, float BPoint, float Cpoint);


	TriangularFuzzySet* clone() const;
	/**
	 * Used to set the value of a triangle fuzzy set.
	 * The point A,B,C must be groeing on the x axys and
	 * only two (A or B) (B or C) can be equal.
	 * @param APoint
	 * @param BPoint
	 * @param CPoint
	 * @return True if the value is correct and it's assigned. False otherwise
	 */
	bool setPoints(float APoint , float BPoint , float CPoint);

	/**
	 * Set all the value of a triangle fuzzy set and also set the name.
	 * The point A,B,C must be growing on the x axys and
	 * only two (A or B) (B or C) can be equal.
	 * If the name is an empty string the set'll not be initialized and it'll
	 * give an error.
	 *
	 * @param _name
	 * @param Apoint
	 * @param BPoint
	 * @param Cpoint
	 * @return True if the value is correct and it's assigned. False otherwise
	 */
	bool configureSet(const std::string& _name, float Apoint, float BPoint, float Cpoint);

	~TriangularFuzzySet();

	 float CalculateMembership (float point) const;

	 float getLowBoundary() const;
	 float getUpBoundary() const;

	 void setName(const std::string& _name);

	 bool mamdaniScale(float value);

	 float getScale() const;

	/**
	 * Return the area of the fuzzy set.
	 * @return	The area, or a negative number if there are some problem.
	 */
	 float getArea() const;

	/**
	 * Return the X position of the centroid of the fuzzy set.
	 * @return The position of the centroid or NAN if there're some error.
	 */
	 float getCentroid() const;

	bool isScaled() const;

	 void resetScale();


};

#endif /* TRIANGULARFUZZYSET_H_ */
