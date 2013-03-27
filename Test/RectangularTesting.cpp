/*
 * RectangularTesting.cpp
 *
 *  Created on: 08/ott/2012
 *      Author: pablosproject
 */
#include "gtest/gtest.h"
#include "fuzzy_sets/RectangularFuzzySet.h"
#include "Utility.h"
#include <string>


class RectangularTesting: public ::testing::Test {

protected:
	virtual void SetUp(){

		rect= RectangularFuzzySet("rect",-1,1);
}

	 RectangularFuzzySet rect;

};

TEST_F (RectangularTesting, OutOfBound){

	ASSERT_FLOAT_EQ(0, rect.CalculateMembership(20));
	ASSERT_FLOAT_EQ(0, rect.CalculateMembership(-3));
}

TEST_F (RectangularTesting, Bundaries){

	ASSERT_FLOAT_EQ(1, rect.CalculateMembership(-1));
	ASSERT_FLOAT_EQ(1, rect.CalculateMembership(1));
}

TEST_F (RectangularTesting, MediumValues){

	ASSERT_FLOAT_EQ(1, rect.CalculateMembership(0));
	ASSERT_FLOAT_EQ(1, rect.CalculateMembership(-0.5));
	ASSERT_FLOAT_EQ(1, rect.CalculateMembership(0.5));

}

TEST_F(RectangularTesting, SetterValidation){

	RectangularFuzzySet toTest("toTest");

	ASSERT_FALSE(toTest.setPoints(1,1));
	ASSERT_FALSE(toTest.setPoints(1,-1));
	ASSERT_TRUE(toTest.setPoints(1,2));

	ASSERT_GE(toTest.CalculateMembership(0) ,0);

	std::string new_name = "new name";
	toTest.configureSet(new_name, 0,5);

	ASSERT_GE(toTest.CalculateMembership(3) ,0);

}

TEST_F(RectangularTesting, NotInitialzedSet){

	RectangularFuzzySet toTest("toTest");

	ASSERT_LT(toTest.CalculateMembership(1),0);

	toTest.setPoints(0,4);
	ASSERT_GT(toTest.CalculateMembership(1),0);

	RectangularFuzzySet toTest_2;
	ASSERT_LT(toTest_2.CalculateMembership(1),0);

	std::string empty = "";
	toTest_2.configureSet(empty,2,5);
	ASSERT_LT(toTest_2.CalculateMembership(1),0);

	RectangularFuzzySet toTest_3;
	toTest_3.setPoints(3,6);
	ASSERT_LT(toTest_3.CalculateMembership(4),0);


}

TEST_F(RectangularTesting, BoundariesFunctionTesting){

	RectangularFuzzySet toTest("toTest");
	ASSERT_TRUE(notNumber::checkNaN(toTest.getLowBoundary()));
	ASSERT_TRUE(notNumber::checkNaN(toTest.getUpBoundary()));

	toTest.setPoints(-5,10);
	ASSERT_FLOAT_EQ(-5, toTest.getLowBoundary());
	ASSERT_FLOAT_EQ(10, toTest.getUpBoundary());

}

TEST_F(RectangularTesting, scaleTest){
	//Test scaled on non initialized fuzzy set
	RectangularFuzzySet* test1 = new RectangularFuzzySet();
	ASSERT_FALSE(test1->mamdaniScale(0.4));
	test1->setName("test");
	ASSERT_FALSE(test1->mamdaniScale(0.4));

	//Test the scaling on a correct fuzzy set
	ASSERT_TRUE(test1->setPoints(-1, 1));
	ASSERT_TRUE(test1->mamdaniScale(0.5));

	//test of a modification on a scaled fuzzy set
	ASSERT_FALSE(test1->setPoints(3,4));


	//test that the membership is correct with the scaled value.

	ASSERT_EQ(test1->CalculateMembership(0),0.5);
	ASSERT_EQ(test1->CalculateMembership(2), 0);

	//Scaled test with scale 0
	RectangularFuzzySet *test2 = new RectangularFuzzySet("test2", -2, 2);

	ASSERT_TRUE(test2->mamdaniScale(0));
	ASSERT_EQ(test2->CalculateMembership(0), 0);

	//Scale with 1
	//Scaled test with scale 0
	RectangularFuzzySet *test3 = new RectangularFuzzySet("test2", -2, 2);

	ASSERT_TRUE(test3->mamdaniScale(1));
	ASSERT_EQ(test3->CalculateMembership(0), 1);

	//Incorrect scaled value
	ASSERT_FALSE(test3->mamdaniScale(-0.5));
	ASSERT_FALSE(test3->mamdaniScale(1.5));

}


TEST_F(RectangularTesting, AreaTesting){

	ASSERT_FLOAT_EQ(2.0, rect.getArea());


	//not initialized rect
	RectangularFuzzySet test;
	ASSERT_LT(test.getArea(),0);
	ASSERT_FALSE(test.setPoints(-1,-2));
	ASSERT_LT(test.getArea(),0);
	ASSERT_TRUE(test.configureSet("test", -5,-3));
	ASSERT_FLOAT_EQ(2,test.getArea());

	//Test area of scaled triangle

	rect.mamdaniScale(0.5);
	ASSERT_FLOAT_EQ(1, rect.getArea());

}

TEST_F(RectangularTesting, CentroidTesting){


	ASSERT_FLOAT_EQ(0, rect.getCentroid());
	RectangularFuzzySet test;
	ASSERT_TRUE(notNumber::checkNaN(test.getCentroid()));

}

