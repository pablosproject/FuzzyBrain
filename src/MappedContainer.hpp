/*
 * MappedContainer.h
 *
 *  Created on: Oct 17, 2012
 *      Author: igloo
 */

#ifndef MAPPEDCONTAINER_H_
#define MAPPEDCONTAINER_H_

#include <vector>
#include <map>

#include "Utility.h"

using namespace std;

typedef map<string,int>::const_iterator MappedContainerIt;


template <class X>class MappedContainer {

private:

	vector <X> elements;
	map<string, int> lookup;
	int ID;

	//logger
	static log4cplus::Logger logger;

public:

	MappedContainer();
	~MappedContainer();


	/**
	 * Insert an element in the container.
	 *
	 * @param name Name of the object to be added.
	 * @param object Pointer to the object to be added.
	 * @return	A boolean that indicate if the operation was successful.
	 */
	bool insert(const string& name,  X object);

	/**
	 * Search for an object in the container, and eventually return it.
	 * @param name	Name of the object to be searched.
	 * @return A pointer to the object, or NULL if it is not find.
	 */
	X getElement(const string& name) const;

	/**
	 * Indicates if a given element is in the container.
	 * @param name Name of the object to test for.
	 * @return
	 */
	const bool hasElement(const string& name) const;

	/**
	 * Find the element and return an unique id, used to retrive it after.
	 * @param name
	 * @return	An id (number >= 0), or a negative number if there's error
	 */
	const int getID(const string& name) const;

	/**
	 * Return a pointer to  a element giving the ID.
	 * @param ID
	 * @return	The element, or NULL if there're some errors
	 */
	X getElement(int _ID) const;

	/**
	 * Search if a given ID exist in the container
	 * @param ID
	 * @return	The result of the search.
	 */
	const bool hasID(const int _ID) const;

	/**
	 * Free all the memory of the internal data structure.
	 * You need to call this method if you pass pointers to
	 * the container and want to free the memory
	 */
	void freeContainer();

	/**
	 * Get the number of objects in the container.
	 * @return	The number of objects in the container.
	 */
	int getLength() const;

	/**
	 * Get the maximum value of ID
	 * @return The max id value
	 */
	int getMaxID() const;

	MappedContainerIt begin() const;
	MappedContainerIt end() const;

};

template <class X> log4cplus::Logger MappedContainer<X>::logger = logging::getLogger("MappedContainer");

template<class X>
MappedContainer<X>::MappedContainer():ID(0){}

template<class X>
MappedContainer<X>::~MappedContainer() {
}

template<class X>
bool MappedContainer<X>::insert(const string& name,	X object) {

	bool correct = true;

	if (name == ""){
		LOG4CPLUS_ERROR(logger, "Cannot insert an element with empty name");
		correct = false;
	}

	if(lookup.insert(pair<string, int>(name,ID)).second == false){
		LOG4CPLUS_WARN(logger, "The element already esxist in the container");
		correct =  false;
	}

	if (object == NULL){
		LOG4CPLUS_ERROR(logger, "Cannot insert an empty pointer.");
		correct = false;
	}
	elements.push_back(object);
	ID++;
	return correct;

}


template<class X>
X MappedContainer<X>::getElement(const string& name) const {

	if (name == ""){
		LOG4CPLUS_ERROR(logger, "Could not find an element if the name is empty.");
		return NULL;
	}

	map<string, int>::const_iterator it;
	it = lookup.find(name);

	if(it == lookup.end()){
		LOG4CPLUS_WARN(logger, "The element to remove does not exists in the container");
		return false;
	}

	return elements[it->second];
}

template<class X>
const bool MappedContainer<X>::hasElement(const string& name) const {

	if (name == ""){
		LOG4CPLUS_ERROR(logger, "Could not find an element if the name is empty.");
		return false;
	}

	map<string, int>::const_iterator it;
	it = lookup.find(name);

	if (it == lookup.end())
		return false;
	else return true;
}

template<class X>
const int MappedContainer<X>::getID(const string& name) const {

	if (name == ""){
		LOG4CPLUS_ERROR(logger, "Could not find an element if the name is empty.");
		return -5;
	}

	map<string, int>::const_iterator it;
	it = lookup.find(name);

	if (it == lookup.end())
		return -5;
	else return it->second;

}

template<class X>
X MappedContainer<X>::getElement(int _ID) const {

	if(_ID >=0 && _ID <= ID && elements[_ID] != NULL)
		return elements[_ID];
	else
		return NULL;
}

template<class X>
const bool MappedContainer<X>::hasID(int _ID) const {

	if(_ID>=0 && _ID <= ID && elements[_ID] != NULL)
		return true;
	else
		return false;
}

template<class X>
inline void MappedContainer<X>::freeContainer() {

	for (unsigned int i=0 ; i<elements.size(); i++){
		delete(elements[i]);
		elements[i]=0;
	}
}

template<class X>
inline int MappedContainer<X>::getLength() const {
	return lookup.size();
}

template<class X>
inline MappedContainerIt MappedContainer<X>::begin() const {
	return this->lookup.begin();
}

template<class X>
inline MappedContainerIt MappedContainer<X>::end() const {
	return this->lookup.end();
}

template<class X>
inline int MappedContainer<X>::getMaxID() const {
	return this->ID;
}

#endif /* MAPPEDCONTAINER_H_ */
