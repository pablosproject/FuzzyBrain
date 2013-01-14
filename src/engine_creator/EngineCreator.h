/*
 * EngineCreator.h
 *
 *  Created on: Nov 26, 2012
 *      Author: igloo
 */

#ifndef ENGINECREATOR_H_
#define ENGINECREATOR_H_
#include "../FuzzyEngine.h"

class EngineCreator {

public:
	virtual ~EngineCreator();

	virtual bool createEngine(FuzzyEngine* engine) const = 0;
};

#endif /* ENGINECREATOR_H_ */
