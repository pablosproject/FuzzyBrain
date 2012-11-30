/*
 * TriangularShape.h
 *
 *  Created on: Nov 15, 2012
 *      Author: igloo
 */

#ifndef TRIANGULARSHAPE_H_
#define TRIANGULARSHAPE_H_

#include "PolygonalShape.h"

class TriangularShape: public PolygonalShape {

private:

	float A;
	float B;
	float C;


	bool setPoints(float A, float B, float C);


	//Logger
	static log4cplus::Logger logger;

public:

	TriangularShape();
	TriangularShape(float A, float B, float C);
	~TriangularShape();

	virtual float value(float point) const;

	virtual float getLowBoundary() const;
	virtual float getUpBoundary() const;

	virtual float getArea() const;
	virtual float getCentroid() const;


};

#endif /* TRIANGULARSHAPE_H_ */
