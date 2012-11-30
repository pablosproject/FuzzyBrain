/*
 * ZadehianOr.cpp
 *
 *  Created on: Oct 31, 2012
 *      Author: igloo
 */

#include "ZadehianOr.h"
#include <algorithm>


float ZadehianOr::orOperation(float f1, float f2) const{
	return std::max(f1,f2);
}
