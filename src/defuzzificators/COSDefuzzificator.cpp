/*
 * COSDefuzzificator.cpp
 *
 *  Created on: Nov 22, 2012
 *      Author: igloo
 */

#include "COSDefuzzificator.h"

COSDefuzzificator::COSDefuzzificator() {}

COSDefuzzificator::~COSDefuzzificator() {}

float COSDefuzzificator::defuzzify(const MamdaniOutputVariable* output) const {

	float numerator = 0;
	float denumerator = 0;

	if (output->getNumberOfFinalSet() == 0)
		return NAN;

	for (int i = 0 ; i<output->getNumberOfFinalSet(); i++){
		int id = output->getModulatedSet()[i];
		float area = output->getSet(id)->getArea();
		float centroid = output->getSet(id)->getCentroid();
		numerator+= (area * centroid);
		denumerator+= area;
	}

	return numerator/denumerator;
}

COSDefuzzificator* COSDefuzzificator::clone() {
	return new COSDefuzzificator(*this);
}
