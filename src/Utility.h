/*
 * rectUtil.h
 *
 *  Created on: Oct 3, 2012
 *      Author: igloo
 */

#ifndef UTILITY_H_
#define UTILITY_H_
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <iomanip>
#include <vector>
#include <sstream>
#include <math.h>
#include <iostream>




typedef std::vector<std::vector<float> > valueCache;

namespace rect{

	 float calculatePositiveRectYPoint(float A, float B, float point);

	 float calculateNegativeRectYPoint(float A, float B, float point);

	 float calculatePositiveRectXPoint(float A, float B, float point);

	 float calculateNegativeRectXPoint(float A, float B, float point);
}


namespace notNumber{

	 bool checkNaN(float x);
}

namespace logging{

using namespace log4cplus;

	  Logger getLogger(const std::string& name);
	  void configurateLogger();
}

namespace tokenizing{

	bool nextToken(std::string& token, std::istringstream& string);
}

namespace centroid{

	float centroidTriangle (float A, float B, float C);
	float centroidTrapezoid (float A, float B, float C, float D);
	float centroidRectange(float A, float B);
}

namespace area{

	float areaTriangle (float A ,float B, float height);
	float areaTrapeziod(float A, float B, float C, float D, float height);
	float areaRectange(float A, float B, float height);
}

#endif /* RECTUTIL_H_ */

