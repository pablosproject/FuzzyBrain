/*
 * PlygonalShape.h
 *
 *  Created on: Nov 15, 2012
 *      Author: igloo
 */

#ifndef POLYGONALSHAPE_H_
#define POLYGONALSHAPE_H_
#include "../Utility.h"

class PolygonalShape {

private:


protected:

	bool scaled;
	float scaledValue;

	bool correctlyInitialized;

public:

	PolygonalShape();
	virtual ~PolygonalShape();

	virtual float getArea() const = 0;
	virtual bool scale(float value);
	virtual float value(float point) const = 0;
	virtual float getLowBoundary() const = 0;
	virtual float getUpBoundary() const = 0;
	virtual float getCentroid() const = 0;
	bool isCorrectlyInitialized() const;
	bool isScaled() const;
	float getScale() const;
	void resetScale();
};

#endif /* PLYGONALSHAPE_H_ */
