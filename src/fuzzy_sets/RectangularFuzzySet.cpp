/*
 * RectangularFuzzySet.cpp
 *
 *  Created on: Oct 3, 2012
 *      Author: igloo
 */

#include "RectangularFuzzySet.h"

log4cplus::Logger RectangularFuzzySet::logger = logging::getLogger("FuzzySet.RectangularFuzzySet");

RectangularFuzzySet::RectangularFuzzySet(const std::string& _name): SimplePolygonalFuzzySet(_name),initialized(false){}

RectangularFuzzySet::RectangularFuzzySet(): SimplePolygonalFuzzySet(""), initialized(false){}

RectangularFuzzySet::RectangularFuzzySet(const std::string& _name, float Apoint,
		float BPoint): SimplePolygonalFuzzySet(_name){

	this->rectangle = RectangularShape(Apoint,BPoint);
	this->initialized = checkConsistence();

}


bool RectangularFuzzySet::setPoints(float APoint, float BPoint){

	if (this->rectangle.isScaled()){
		LOG4CPLUS_ERROR(this->logger, this->name + ": Cannot modify a scaled fuzzy set.");
		return false;
	}

	this->rectangle = RectangularShape(APoint,BPoint);

	this->initialized = checkConsistence();

	return this->rectangle.isCorrectlyInitialized();

}

RectangularFuzzySet::~RectangularFuzzySet() {
	// TODO Auto-generated destructor stub
}

float RectangularFuzzySet::CalculateMembership(float point) const{

	if (!initialized){
		LOG4CPLUS_ERROR(this->logger, "Set is not initialized properly. Impossible calculate membership.");
		return -1;
	}

	return this->rectangle.value(point);
}

float RectangularFuzzySet::getUpBoundary() const{
	if (initialized)
		return this->rectangle.getUpBoundary();
	else
		return NAN;
}

float RectangularFuzzySet::getLowBoundary() const{
	if (initialized)
		return this->rectangle.getLowBoundary();
	else
		return NAN;
}

bool RectangularFuzzySet::checkConsistence() {

	if(this->name == "" || !this->rectangle.isCorrectlyInitialized())
		return false;
	else
		return true;
}

void RectangularFuzzySet::setName(const std::string& _name){

	if(_name == "")
		LOG4CPLUS_WARN(this->logger, "Name cannot be an empty string. Possible inconsistences.");
	this->name = _name;
	this->initialized = checkConsistence();
}

bool RectangularFuzzySet::configureSet(const std::string& _name, float Apoint,
		float BPoint) {

	if (_name == "")
		LOG4CPLUS_WARN(this->logger, this->name + ": Name cannot be an empty string. Possible inconsistences.");

	if (this->rectangle.isScaled()){
		LOG4CPLUS_ERROR(this->logger, this->getName() + "  Cannot configure a scaled triangle.");
		return false;
	}

	if (setPoints(Apoint, BPoint)){
		this->name = _name;
		this->initialized = checkConsistence();
		return true;
	}
	else
		LOG4CPLUS_ERROR(this->logger, this->name + " Set cannot be configured. Points error");
	return false;
}

float RectangularFuzzySet::getArea() const {

	if (!initialized){
		LOG4CPLUS_ERROR(logger, this->getName()+": cannot calculate the area of an uninitialized rectangle.");
		return -1;
	}
	else
	return this->rectangle.getArea();
}

bool RectangularFuzzySet::mamdaniScale(float value) {

	if (this -> initialized)
		return this->rectangle.scale(value);
	else{
		LOG4CPLUS_ERROR(logger, this->getName() + " Cannot scale a non initialized fuzzy set.");
		return false;
	}

}

float RectangularFuzzySet::getCentroid() const {
	if(!initialized){
		LOG4CPLUS_ERROR(logger, this->getName()+": cannot calculate the centroid of an uninitialized rectangle.");
		return NAN;
	}
	else
		return this->rectangle.getCentroid();
}

float RectangularFuzzySet::getScale() const {
	if(!initialized){
		LOG4CPLUS_ERROR(logger, this->getName()+": cannot return the scale of an uninitialized rectangle.");
		return -1;
	}

	return this->rectangle.getScale();
}

bool RectangularFuzzySet::isScaled() const {
	return this->rectangle.isScaled();
}

void RectangularFuzzySet::resetScale() {
	this->rectangle.resetScale();
}

RectangularFuzzySet* RectangularFuzzySet::clone() const {
	return new RectangularFuzzySet(*this);
}
