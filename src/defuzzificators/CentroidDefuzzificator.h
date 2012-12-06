/*
 * CentroidDefuzzificator.h
 *
 *  Created on: Nov 14, 2012
 *      Author: igloo
 */

#ifndef CENTROIDDEFUZZIFICATOR_H_
#define CENTROIDDEFUZZIFICATOR_H_

#include "Defuzzificator.h"
#include "../Utility.h"

class CentroidDefuzzificator: public Defuzzificator {

private:
	int numSample;
	float Discretization(const MamdaniOutputVariable * out, float min_range, float max_range) const;

public:
	/**
	 * Default constructor for the Centroid Defuzzificator.
	 * @param numSample The number of sample for the given defuzzificator, by default is 100.
	 */
	CentroidDefuzzificator(int samples = 100);
	virtual ~CentroidDefuzzificator();

<<<<<<< HEAD
	float defuzzify(const MamdaniOutputVariable* output) const;
	void setNumSample(int numSample);
=======
	float defuzzify(const LinguisticVariable* output);

>>>>>>> de9151170be91f346d2f0cb77ba7185c4eaa0a41
};

#endif /* CENTROIDDEFUZZIFICATOR_H_ */
