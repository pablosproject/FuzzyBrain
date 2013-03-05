/*
 * RectangularShape.cpp
 *
 *  Created on: 21/nov/2012
 *      Author: pablosproject
 */

#include "RectangularShape.h"

RectangularShape::RectangularShape(): A(0), B(0) {}

RectangularShape::RectangularShape(float A, float B){

	if (setPoints(A,B))
		this->correctlyInitialized = true;
	else
		this->correctlyInitialized = false;

}

RectangularShape::~RectangularShape() {
	// TODO Auto-generated destructor stub
}

bool RectangularShape::setPoints(float APoint, float BPoint) {

	if (APoint >= BPoint){
		LERROR << "The points are not correct.";
		return false;
	}

	this->A = APoint;
	this->B = BPoint;

	return true;

}

float RectangularShape::value(float point) const {

	float membership = -1;

	if (point < this->A || point >this->B)
		membership = 0;
	else{
		if (scaled)
			membership = scaledValue;
		else
			membership = 1;
	}
	return membership;
}

float RectangularShape::getLowBoundary() const {
	return this->A;
}

float RectangularShape::getUpBoundary() const {
	return this->B;
}

float RectangularShape::getArea() const {

	if (!this->scaled)
		return area::areaRectange(this->A, this->B, 1);
	else{
		return area::areaRectange(this->A,this->B, this->scaledValue);
	}
}

float RectangularShape::getCentroid() const {
		return centroid::centroidRectange(this->A, this->B);
}
