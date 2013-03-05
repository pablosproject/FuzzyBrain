/*
 * TriangularShape.cpp
 *
 *  Created on: Nov 15, 2012
 *      Author: igloo
 */

#include "TriangularShape.h"


TriangularShape::TriangularShape(float A, float B, float C){
	if(setPoints(A,B,C))
		this->correctlyInitialized = true;
	else
		this->correctlyInitialized = false;

}

TriangularShape::TriangularShape():A(0), B(0), C(0){}

TriangularShape::~TriangularShape() {}

bool TriangularShape::setPoints(float _A, float _B, float _C) {

	if (_A > _B || _A >= _C || _B > _C ){ //Check that all the lements are growing on X axys
		LERROR <<" The points are not correct.";
		return false;
	}

	this->A = _A;
	this->B = _B;
	this->C = _C;

	return true;

}

float TriangularShape::value(float point) const{

	float value = -1;

	if (point < this->A || point > this->C)	//Outside the base of triangle
		value =  0;
	else if ( point == this->B)	//Top of the triangle.
		value = 1;
	else if (point < this->B)
		value = rect::calculatePositiveRectYPoint(this->A, this->B, point);
	else if (point > this->B)
		value = rect::calculateNegativeRectYPoint(this->B, this->C, point);

	if(this->scaled && value >= this->scaledValue)
		value = this->scaledValue;

	return value;
}

float TriangularShape::getLowBoundary() const {
	if (correctlyInitialized)
		return this->A;
	else
		return -1;
}

float TriangularShape::getUpBoundary() const {
	if (correctlyInitialized)
		return this->C;
	else
		return -1;
}

float TriangularShape::getArea() const {

	if (!this->scaled)
		return area::areaTriangle(this->A, this->C, 1);	//scaled == 1
	else{//If it is scaled it's a trapezoid
		float B_temp = rect::calculatePositiveRectXPoint(this->A, this->B, this->scaledValue);
		float C_temp = rect::calculateNegativeRectXPoint(this->B, this->C, this->scaledValue);

		return area::areaTrapeziod(this->A, B_temp, C_temp, this->C, this->scaledValue);
	}
}


float TriangularShape::getCentroid() const {

	if (!this->scaled)
		return centroid::centroidTriangle(this->A, this->B, this->C);

	else{
		float B_temp = rect::calculatePositiveRectXPoint(this->A, this->B, this->scaledValue);
		float C_temp = rect::calculateNegativeRectXPoint(this->B, this->C, this->scaledValue);

		return centroid::centroidTrapezoid(this->A,B_temp,C_temp,this->C);
	}
}
