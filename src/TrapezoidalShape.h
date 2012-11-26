/*
 * TrapezoidalShape.h
 *
 *  Created on: Nov 21, 2012
 *      Author: igloo
 */

#ifndef TRAPEZOIDALSHAPE_H_
#define TRAPEZOIDALSHAPE_H_

#include "PolygonalShape.h"

class TrapezoidalShape : public PolygonalShape{

private:

	float A;
	float B;
	float C;
	float D;

	bool setPoints(float A, float B, float C, float D);

	//logger for the object
	static log4cplus::Logger logger;

public:

	TrapezoidalShape();
	TrapezoidalShape(float A, float B, float C, float D);
	~TrapezoidalShape();

	virtual float value(float point) const;

	virtual float getLowBoundary() const;
	virtual float getUpBoundary() const;

	virtual float getArea() const;
	virtual float getCentroid() const;

};

#endif /* TRAPEZOIDALSHAPE_H_ */
