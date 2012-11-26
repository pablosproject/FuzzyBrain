/*
 * RectangularShape.h
 *
 *  Created on: 21/nov/2012
 *      Author: pablosproject
 */

#ifndef RECTANGULARSHAPE_H_
#define RECTANGULARSHAPE_H_

#include "PolygonalShape.h"
#include "Utility.h"

class RectangularShape: public PolygonalShape {

private:
	float A;
	float B;

	bool setPoints(float APoint, float BPoint);

	//logger
	static log4cplus::Logger logger;

public:
	RectangularShape();
	RectangularShape(float A, float B);
	~RectangularShape();

	virtual float value(float point) const;

	virtual float getLowBoundary() const;
	virtual float getUpBoundary() const;

	virtual float getArea() const;
	virtual float getCentroid() const;

};

#endif /* RECTANGULARSHAPE_H_ */
