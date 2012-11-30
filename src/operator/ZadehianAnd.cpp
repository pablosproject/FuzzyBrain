/*
 * ZadehianAnd.cpp
 *
 *  Created on: Oct 24, 2012
 *      Author: igloo
 */

#include "ZadehianAnd.h"
#include <algorithm>


float ZadehianAnd::andOperation (float f1 , float f2) const{
	return std::min(f1,f2);
}

