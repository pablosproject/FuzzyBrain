/*
 * CentroidDefuzzificator.cpp
 *
 *  Created on: Nov 14, 2012
 *      Author: igloo
 */

#include "CentroidDefuzzificator.h"

CentroidDefuzzificator::CentroidDefuzzificator(int samples): numSample(samples) {}

CentroidDefuzzificator::~CentroidDefuzzificator() {}

float CentroidDefuzzificator::defuzzify(const MamdaniOutputVariable* output) const{

	if (output->getNumberOfFinalSet() == 0)
		return NAN;

	float min_range = output->getMaxRange();
	float max_range = output->getMinRange();

	for (int i = 0; i< output->getNumberOfFinalSet(); i++){

		int id = output->getModulatedSet()[i];
		float minimum = output->getSet(id)->getLowBoundary();
		min_range = min(min_range, minimum);
		float maximum = output->getSet(id)->getUpBoundary();
		max_range = max(max_range, maximum);
	}

//	float rectSize = (max_range - min_range) / this->numSample;
//	float rectMid = (rectSize) / 2.0;
//
//	float numerator = 0;
//	float denumerator = 0;
//	float point = min_range;
//
//	for (int j = 0 ; j < this->numSample; j++){
//
//		float value = output->membershipForPoint(point + rectMid); //calculate the membership in the middle
//		numerator += (rectSize * value) * centroid::centroidRectange(point, point+rectSize); //area rectangle* centroid
//		denumerator += rectSize * value; //area rectangle
//		point += rectSize;
//	}
//
//	return numerator / denumerator;

	return Discretization(output, min_range, max_range);
}

void CentroidDefuzzificator::setNumSample(int numSample) {
	this->numSample = numSample;
}

float CentroidDefuzzificator::Discretization(const MamdaniOutputVariable* out,
		float min_range, float max_range) const{

	float stepSize = (max_range - min_range) / this->numSample;

	float numerator = 0;
	float denumerator = 0;
	float point = min_range;

	for (int i = 0; i< this->numSample; i++){

		float membership = out->membershipForPoint(point);
		numerator += point * membership;
		denumerator += membership;
		point += stepSize;
	}

	return numerator / denumerator;
}
