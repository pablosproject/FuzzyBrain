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


public:

	TriangularShape();
	TriangularShape(float A, float B, float C);
	~TriangularShape();

	 float value(float point) const;

	 float getLowBoundary() const;
	 float getUpBoundary() const;

	 float getArea() const;
	 float getCentroid() const;


};

#endif /* TRIANGULARSHAPE_H_ */
