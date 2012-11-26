/*
 * Utility.cpp
 *
 *  Created on: 12/ott/2012
 *      Author: pablosproject
 */
#include "Utility.h"

namespace rect{

	 float calculatePositiveRectYPoint(float A, float B, float point){
		return (point - A) / (B -A);
	}

	 float calculateNegativeRectYPoint(float A, float B, float point){
		return (-(point - A) / (B - A) + 1);
	}

	 float calculatePositiveRectXPoint(float A, float B, float point) {
		 return point * (B-A) + A;
	 }

	 float calculateNegativeRectXPoint(float A, float B, float point) {
		 return (-(point -1) * (B - A) + A);
	 }

}


namespace notNumber{

	 bool checkNaN(float x){
		return x!=x;
	}
}

namespace logging{

static bool configured = false;

using namespace log4cplus;

Logger getLogger(const std::string& name){

	if (!configured){
		configurateLogger();
	}
	return Logger::getInstance(name);
}
void configurateLogger() {

	PropertyConfigurator::doConfigure(LOG4CPLUS_STRING_TO_TSTRING("/Users/igloo/Documents/workspace/FuzzyTrainer/logger_configuration.config"));
}

}

bool tokenizing::nextToken(std::string& token,  std::istringstream& string) {
	if(string >> token)
		return true;
	else
		return false;
}

float centroid::centroidTriangle(float A, float B, float C) {

	return (A + B + C) / 3;
}

float centroid::centroidTrapezoid(float A, float B, float C, float D) {

	float numerator = (C*C) + (D*D)+ (C*D)-(A*A)-(B*B)-(A*B);
	float denumerator = 3 * (C + D -A - B);
	return numerator/denumerator;
}

float area::areaTriangle(float A, float B, float height) {

	return (B - A) * height /2;
}

float area::areaTrapeziod(float A, float B, float C, float D, float height) {

	return ((C - B) + (D - A)) * height /2;
}

float centroid::centroidRectange(float A, float B) {
	float numerator = (B*B) - (A*A);
	float denumerator = 2 *(B - A);
	return numerator/denumerator;
}

float area::areaRectange(float A, float B, float height) {
	return (B - A) * height;
}
