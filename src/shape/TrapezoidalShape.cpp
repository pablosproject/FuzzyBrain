/*
 * TrapezoidalShape.cpp
 *
 *  Created on: Nov 21, 2012
 *      Author: igloo
 */

#include "TrapezoidalShape.h"


TrapezoidalShape::TrapezoidalShape():A(0), B(0), C(0), D(0){}

TrapezoidalShape::TrapezoidalShape(float A, float B, float C, float D) {
	if (setPoints(A,B,C,D))
		this->correctlyInitialized = true;
	else
		this->correctlyInitialized = false;
}

TrapezoidalShape::~TrapezoidalShape() {
	// TODO Auto-generated destructor stub
}

bool TrapezoidalShape::setPoints(float _A, float _B, float _C, float _D) {

	if (_A > _B || _B > _C || _C > _D){
		LERROR << "Points are incorrect. Not growing on the x-axis";
		return false;
	}
    if (_B == _C){							 //it can't be a triangle
		LERROR << "Points are incorrect. Top points can't be equal.";
    	return false;
    }
	if (_A == _B && _C == _D){
		LERROR << "Points are incorrect. Can't be a rect.";
		return false;								//it can't be a rect
	}

	this->A = _A;
	this->B = _B;
	this->C = _C;
	this->D = _D;

	return true;
}

float TrapezoidalShape::getUpBoundary() const {
	return this->D;
}

float TrapezoidalShape::getLowBoundary() const {
	return this->A;
}

float TrapezoidalShape::value(float point) const {

	float membership = -1;

	if (point < this->A || point > this->D)	//out of the base of the trapezoid
		membership = 0;

	else if (point > this->B && point < this->C)	//Point on the top base of the trapezoid
		membership = 1;

	else if (point >= this->A && point <= this->B)	// on the first diagonal side
		if (this->A == this->B) membership = 1;	//it's a rect
		else membership = rect::calculatePositiveRectYPoint(this->A, this->B, point);

	else if (point >= this->C && point <= this->D)
		if (this->C == this->D) membership = 1;
		else membership = rect::calculateNegativeRectYPoint(this->C, this->D, point);


	//Check for a scaled set
	if(this->scaled && membership >= this->scaledValue)
		membership = this->scaledValue;

	return membership;

}

float TrapezoidalShape::getArea() const {
	if(!this->scaled){
		return area::areaTrapeziod(this->A, this->B, this->C, this->D, 1);
	}
	else{
		if (this->scaledValue == 0)
			return 0;

		float B_temp = rect::calculatePositiveRectXPoint(this->A, this->B, this->scaledValue);
		float C_temp = rect::calculateNegativeRectXPoint(this->C, this->D, this->scaledValue);
		return area::areaTrapeziod(this->A, B_temp, C_temp, this->D, this->scaledValue);
	}
}

float TrapezoidalShape::getCentroid() const {
	if(!this->scaled)
		return centroid::centroidTrapezoid(this->A, this->B, this->C, this->D);
	else{
		float B_temp = rect::calculatePositiveRectXPoint(this->A, this->B, this->scaledValue);
		float C_temp = rect::calculateNegativeRectXPoint(this->C, this->D, this->scaledValue);
		return centroid::centroidTrapezoid(this->A, B_temp, C_temp, this->D);
	}
}
