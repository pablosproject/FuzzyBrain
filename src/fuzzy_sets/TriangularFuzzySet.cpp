/*
 * TriangularFuzzySet.cpp
 *
 *  Created on: Sep 24, 2012
 *      Author: igloo
 */

#include "TriangularFuzzySet.h"



TriangularFuzzySet::TriangularFuzzySet(): SimplePolygonalFuzzySet(""), initialized(false){}

TriangularFuzzySet::TriangularFuzzySet(const std::string& _name, float Apoint,
		float BPoint, float Cpoint) : SimplePolygonalFuzzySet(_name){

	this->triangle = TriangularShape(Apoint, BPoint, Cpoint);
	this->initialized = checkConsistence();
}

TriangularFuzzySet::TriangularFuzzySet(const std::string& _name): SimplePolygonalFuzzySet(_name),initialized(false){}


bool TriangularFuzzySet::setPoints(float APoint , float BPoint , float CPoint) {

		if (this->triangle.isScaled()){
			LERROR << this->getName() << "  Cannot set point of a scaled triangle.";
			return false;
		}

		this->triangle = TriangularShape(APoint,BPoint,CPoint);

		this->initialized = checkConsistence();

		return this->triangle.isCorrectlyInitialized();

}

bool TriangularFuzzySet::configureSet(const std::string& _name, float Apoint,
		float BPoint, float Cpoint) {

	if ( _name == "")
		LWARNING << this->name << " Name cannot be an empty string. Possible inconsistences.";

	if (this->triangle.isScaled()){
		LERROR << this->getName() << "  Cannot configure a scaled triangle.";
		return false;
	}

	if (setPoints(Apoint, BPoint, Cpoint)){
		this->name = _name;
		this->initialized = checkConsistence();
		return true;
	}
	else
		LERROR << this->name << " Set cannot be configured. Points error";
	return false;

}

float TriangularFuzzySet::CalculateMembership(float point) const{

	if (!this->initialized){
		LERROR << this->name << " Set is not initialized properly. Impossible calculate membership.";
		return -1;
	}

	return this->triangle.value(point);

}

TriangularFuzzySet::~TriangularFuzzySet() {
	// TODO Auto-generated destructor stub
}

float TriangularFuzzySet::getLowBoundary() const {
	if (initialized)
		return this->triangle.getLowBoundary();
	else
		return NAN;
}

float TriangularFuzzySet::getUpBoundary() const {
	if (initialized)
		return this->triangle.getUpBoundary();
	else
		return NAN;
}

void TriangularFuzzySet::setName(const std::string& _name){

	if(_name == "")
		LWARNING << this->name << "Name cannot be an empty string. Possible inconsistences.";
	this->name = _name;
	this->initialized = checkConsistence();
}

bool TriangularFuzzySet::checkConsistence() {

	if (this->name == "" || !this->triangle.isCorrectlyInitialized())
		return false;
	else
		return true;
}

bool TriangularFuzzySet::mamdaniScale(float value) {
	if (this -> initialized)
		return this->triangle.scale(value);
	else{
		LERROR <<  this->getName() << " Cannot scale a non initialized fuzzy set.";
		return false;
	}
}

float TriangularFuzzySet::getArea() const {
	if (!initialized){
		LERROR <<  this->getName() << ": cannot calculate the area of an uninitialized triangle.";
		return -1;
	}
	else
	return this->triangle.getArea();
}

float TriangularFuzzySet::getCentroid() const {
	if(!initialized){
		LERROR <<  this->getName() << ": cannot calculate the centroid of an uninitialized triangle.";
		return NAN;
	}
	else
		return this->triangle.getCentroid();
}

float TriangularFuzzySet::getScale() const {
	if(!initialized){
		LERROR <<  this->getName() << ": cannot return the scale of an uninitialized triangle.";
		return -1;
	}
	return this->triangle.getScale();
}

bool TriangularFuzzySet::isScaled() const {
	return this->triangle.isScaled();
}

void TriangularFuzzySet::resetScale() {
	this->triangle.resetScale();
}

TriangularFuzzySet* TriangularFuzzySet::clone() const {
	return new TriangularFuzzySet(*this);
}
