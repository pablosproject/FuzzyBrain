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

public:

	TrapezoidalShape();
	TrapezoidalShape(float A, float B, float C, float D);
	~TrapezoidalShape();

	 float value(float point) const;

	 float getLowBoundary() const;
	 float getUpBoundary() const;

	 float getArea() const;
	 float getCentroid() const;

};

#endif /* TRAPEZOIDALSHAPE_H_ */
