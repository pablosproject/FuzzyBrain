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


	return Discretization(output, min_range, max_range);
}

void CentroidDefuzzificator::setNumSample(int numSample) {
	this->numSample = numSample;
}

float CentroidDefuzzificator::Discretization(const MamdaniOutputVariable* out,
		float min_range, float max_range) const{

	//Using double and long double to have the maximum precision and
	//avoid double overflow on a large number of sample

	double stepSize = (max_range - min_range) / this->numSample;

	long double numerator = 0.0;
	long double denumerator = 0.0;
	double point = min_range;

	for (int i = 0; i< this->numSample; i++){

		double membership = out->membershipForPoint(point);
		numerator += point * membership;
		denumerator += membership;
		point += stepSize;
	}

	float result = numerator / denumerator;
	//cout<<"Numerator: "<<numerator<<" denumerator: " <<denumerator<<"\n";
	//cout<< "Result of the defuzzification with centroid "<< result<<"\n";
	return result;
}

CentroidDefuzzificator* CentroidDefuzzificator::clone() {
	return new CentroidDefuzzificator(*this);
}
