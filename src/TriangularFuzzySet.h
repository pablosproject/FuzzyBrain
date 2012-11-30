/*
 * TriangularFuzzySet.h
 *
 *  Created on: Sep 24, 2012
 *      Author: igloo
 */

#ifndef TRIANGULARFUZZYSET_H_
#define TRIANGULARFUZZYSET_H_

#include "SimplePolygonalFuzzySet.h"
#include "Utility.h"
#include "TriangularShape.h"

#include <math.h>

class TriangularFuzzySet : public SimplePolygonalFuzzySet {
private:

	TriangularShape triangle;
	bool initialized;


	bool checkConsistence();


	//Logger
	static log4cplus::Logger logger;

public:

	TriangularFuzzySet();
	TriangularFuzzySet(const std::string& _name);
	TriangularFuzzySet(const std::string& _name,  float Apoint, float BPoint, float Cpoint);


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

	virtual float CalculateMembership (float point) const;

	virtual float getLowBoundary() const;
	virtual float getUpBoundary() const;

	virtual void setName(const std::string& _name);

	virtual bool scale(float value);

	virtual float getScale() const;

	/**
	 * Return the area of the fuzzy set.
	 * @return	The area, or a negative number if there are some problem.
	 */
	virtual float getArea() const;

	/**
	 * Return the X position of the centroid of the fuzzy set.
	 * @return The position of the centroid or NAN if there're some error.
	 */
	virtual float getCentroid() const;

	bool isScaled() const;

	virtual void resetScale();


};

#endif /* TRIANGULARFUZZYSET_H_ */
