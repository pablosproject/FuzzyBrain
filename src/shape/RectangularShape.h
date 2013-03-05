/*
 * RectangularShape.h
 *
 *  Created on: 21/nov/2012
 *      Author: pablosproject
 */

#ifndef RECTANGULARSHAPE_H_
#define RECTANGULARSHAPE_H_

#include "PolygonalShape.h"
#include "../Utility.h"

class RectangularShape: public PolygonalShape {

private:
	float A;
	float B;

	bool setPoints(float APoint, float BPoint);

public:
	RectangularShape();
	RectangularShape(float A, float B);
	~RectangularShape();

	 float value(float point) const;

	 float getLowBoundary() const;
	 float getUpBoundary() const;

	 float getArea() const;
	 float getCentroid() const;

};

#endif /* RECTANGULARSHAPE_H_ */
