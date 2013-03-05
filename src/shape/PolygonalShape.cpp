/*
 * PlygonalShape.cpp
 *
 *  Created on: Nov 15, 2012
 *      Author: igloo
 */

#include "PolygonalShape.h"


PolygonalShape::PolygonalShape(): scaled(false),scaledValue(0), correctlyInitialized(false){}

PolygonalShape::~PolygonalShape() {}

bool PolygonalShape::isCorrectlyInitialized() const {
	return correctlyInitialized;
}

bool PolygonalShape::isScaled() const {
	return scaled;
}

float PolygonalShape::getScale() const {
	if (this->scaled)
		return this->scaledValue;
	else
		return 1;//if not scaled the scale is 1
}

bool PolygonalShape::scale(float value) {

	if(value < 0 || value > 1){
		LERROR << " Scaled value not correct.";
		return false;
	}

	this->scaled = true;
	this->scaledValue = value;

	return true;
}

void PolygonalShape::resetScale() {
	this->scaled = false;
	this->scaledValue = 1;
}
