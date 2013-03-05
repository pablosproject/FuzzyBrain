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
	return (B+A)/2;
}

float area::areaRectange(float A, float B, float height) {
	return (B - A) * height;
}

float parsing::extractFloat(const char* toConvert) {
		std::string res = std::string(toConvert);
		replace(res.begin(), res.end(),',','.');
		return atof(res.c_str());
	}

