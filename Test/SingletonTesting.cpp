/*
 * SingletonTesting.cpp
 *
 *  Created on: 08/ott/2012
 *      Author: pablosproject
 */
#include "gtest/gtest.h"
#include "fuzzy_sets/SingletonFuzzySet.h"
#include "Utility.h"


class SingletonTesting: public ::testing::Test {

protected:
	virtual void SetUp(){
		single = SingletonFuzzySet("single",1);
	}

	SingletonFuzzySet single;

};


TEST_F(SingletonTesting, OutOfBoundAndCOrrectValue){

	ASSERT_FLOAT_EQ(0, single.CalculateMembership(-1));
	ASSERT_FLOAT_EQ(0, single.CalculateMembership(0.9));
	ASSERT_FLOAT_EQ(1, single.CalculateMembership(1));

}

TEST_F(SingletonTesting, NotInitializedSet){

	SingletonFuzzySet toTest;

	ASSERT_LT(toTest.CalculateMembership(1),0);

	toTest.setPoint(3);

	ASSERT_LT(toTest.CalculateMembership(2),0);

	std::string name = "testname";
	toTest.setName(name);
	ASSERT_GE(toTest.CalculateMembership(1),0);


}

TEST_F(SingletonTesting, BoundariesFunctionTesting){

	SingletonFuzzySet toTest;
	ASSERT_TRUE(notNumber::checkNaN(toTest.getLowBoundary()));
	ASSERT_TRUE(notNumber::checkNaN(toTest.getUpBoundary()));

	std::string name = "bound";
	toTest.configureSet(name,-5);
	ASSERT_FLOAT_EQ(-5, toTest.getLowBoundary());
	ASSERT_FLOAT_EQ(-5, toTest.getUpBoundary());

}




