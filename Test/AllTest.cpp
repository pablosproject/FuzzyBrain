/*
 * AllTest.cpp
 *
 *  Created on: Oct 3, 2012
 *      Author: igloo
 */

#include "gtest/gtest.h"


int main(int argc, char **argv) {

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
