/*
 * TrapezoidalFuzzySet.cpp
 *
 *  Created on: Oct 3, 2012
 *      Author: igloo
 */

#include "TrapezoidalFuzzySet.h"

TrapezoidalFuzzySet::TrapezoidalFuzzySet():SimplePolygonalFuzzySet(""), initialized(false) {};
TrapezoidalFuzzySet::TrapezoidalFuzzySet(const std::string& _name): SimplePolygonalFuzzySet(_name),initialized(false) {}
TrapezoidalFuzzySet::TrapezoidalFuzzySet(const std::string& _name, float APoint, float BPoint, float CPoint, float DPoint): SimplePolygonalFuzzySet(_name){

	this->trapezoid = TrapezoidalShape(APoint, BPoint, CPoint, DPoint);
	this->initialized = checkConsistence();

}


bool TrapezoidalFuzzySet::setPoints(float APoint, float BPoint, float CPoint, float DPoint){

	if (this->trapezoid.isScaled()){
		LERROR << this->getName() << "  Cannot set a point of a scaled trapezoid.";
		return false;
	}

	this->trapezoid = TrapezoidalShape (APoint, BPoint, CPoint, DPoint);
	this->initialized  = checkConsistence();

	return this->trapezoid.isCorrectlyInitialized();

}

bool TrapezoidalFuzzySet::configureSet(const std::string& _name, float Apoint,
		float BPoint, float Cpoint, float DPoint) {

	if(_name == "")
		LWARNING << "Name cannot be an empty string. Possible inconsistences.";

	if (this->trapezoid.isScaled()){
		LERROR << this->getName() << "  Cannot configure a trapezoid.";
		return false;
	}

	if (setPoints(Apoint, BPoint, Cpoint,DPoint)){
		this->name = _name;
		this->initialized = checkConsistence();
		return true;
	}
	else
		LERROR << "Set cannot be configured. Points error";
	return false;


}

TrapezoidalFuzzySet::~TrapezoidalFuzzySet() {
	// TODO Auto-generated destructor stub
}

float TrapezoidalFuzzySet::CalculateMembership(float point) const{

	if (!initialized){
		LERROR << "Set is not initialized properly. Impossible calculate membership.";
		return -1;
	}

	return this->trapezoid.value(point);

}

float TrapezoidalFuzzySet::getUpBoundary() const {
	if (initialized)
		return this->trapezoid.getUpBoundary();
	else
		return NAN;
}

float TrapezoidalFuzzySet::getLowBoundary() const {
	if (initialized)
		return this->trapezoid.getLowBoundary();
	else
		return NAN;
}

void TrapezoidalFuzzySet::setName(const std::string& _name){

	if(_name == "")
		LWARNING << "Name cannot be an empty string. Possible inconsistences.";
	this->name = _name;
	this->initialized = checkConsistence();
}

bool TrapezoidalFuzzySet::checkConsistence() {

	if (this->name == "" || !this->trapezoid.isCorrectlyInitialized())
		return false;
	else
		return true;
}

float TrapezoidalFuzzySet::getArea() const {

	if (!initialized){
		LERROR << this->getName() << ": cannot calculate the area of an uninitialized trapezoid.";
		return -1;
	}
	return this->trapezoid.getArea();
}

bool TrapezoidalFuzzySet::mamdaniScale(float value) {

	if (this -> initialized)
		return this->trapezoid.scale(value);
	else{
		LERROR << this->getName() << " Cannot scale a non initialized fuzzy set.";
		return false;
	}
}

float TrapezoidalFuzzySet::getCentroid() const {
	if(!initialized){
		LERROR << this->getName() << ": cannot calculate the centroid of an uninitialized trapezoid.";
		return NAN;
	}
	else
		return this->trapezoid.getCentroid();
}

float TrapezoidalFuzzySet::getScale() const {
	if(!initialized){
		LERROR << this->getName() <<": cannot return the scale of an uninitialized trapezoid.";
		return -1;
	}

	return this->trapezoid.getScale();
}

bool TrapezoidalFuzzySet::isScaled() const {
	return this->trapezoid.isScaled();
}

void TrapezoidalFuzzySet::resetScale() {
	this->trapezoid.resetScale();
}

TrapezoidalFuzzySet* TrapezoidalFuzzySet::clone() const {
	return new TrapezoidalFuzzySet(*this);
}
