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

	float defuzzify(const MamdaniOutputVariable* output) const;
	void setNumSample(int numSample);

	CentroidDefuzzificator* clone ();
};

#endif /* CENTROIDDEFUZZIFICATOR_H_ */
