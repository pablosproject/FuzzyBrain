#include "gtest/gtest.h"
#include "fuzzy_sets/TrapezoidalFuzzySet.h"
#include <math.h>

class TrapezoidalTesting: public ::testing::Test {

protected:
	virtual void SetUp(){
		rect_left =TrapezoidalFuzzySet("left",2,2,5,6);
		rect_right = TrapezoidalFuzzySet("right",2,3,5,5);
		normal = TrapezoidalFuzzySet("normal",-2,-1,2,5);


	}

	TrapezoidalFuzzySet rect_left ;
	TrapezoidalFuzzySet rect_right ;
	TrapezoidalFuzzySet normal;

};


TEST_F(TrapezoidalTesting , BoundariesOut){

	ASSERT_FLOAT_EQ(1, rect_left.CalculateMembership(2));
	ASSERT_FLOAT_EQ(0, rect_left.CalculateMembership(6));
	ASSERT_FLOAT_EQ(0, rect_right.CalculateMembership(2));
	ASSERT_FLOAT_EQ(1, rect_right.CalculateMembership(5));
	ASSERT_FLOAT_EQ(0, normal.CalculateMembership(-2));
	ASSERT_FLOAT_EQ(0, normal.CalculateMembership(5));

}


TEST_F(TrapezoidalTesting, TopValues){

	ASSERT_FLOAT_EQ(1, rect_left.CalculateMembership(3));
	ASSERT_FLOAT_EQ(1, rect_left.CalculateMembership(3.5));
	ASSERT_FLOAT_EQ(1, rect_left.CalculateMembership(5));

	ASSERT_FLOAT_EQ(1, rect_right.CalculateMembership(3));
	ASSERT_FLOAT_EQ(1, rect_right.CalculateMembership(3.5));
	ASSERT_FLOAT_EQ(1, rect_right.CalculateMembership(5));

	ASSERT_FLOAT_EQ(1, normal.CalculateMembership(-1));
	ASSERT_FLOAT_EQ(1, normal.CalculateMembership(0));
	ASSERT_FLOAT_EQ(1, normal.CalculateMembership(2));
	ASSERT_FLOAT_EQ(1, normal.CalculateMembership(0.5));

}

TEST_F(TrapezoidalTesting, DiagonalValue){

	ASSERT_FLOAT_EQ(0.5, rect_left.CalculateMembership(5.5));
	ASSERT_FLOAT_EQ(0.25, rect_left.CalculateMembership(5.75));
	ASSERT_FLOAT_EQ(0.75, rect_left.CalculateMembership(5.25));

	ASSERT_FLOAT_EQ(0.75, rect_right.CalculateMembership(2.75));
	ASSERT_FLOAT_EQ(0.25, rect_right.CalculateMembership(2.25));
	ASSERT_FLOAT_EQ(0.5, rect_right.CalculateMembership(2.5));
	float m1 = 1.0 - 1.0 / 3.0;
	float m2 = 1.0 - 2.0/ 3.0;

	ASSERT_FLOAT_EQ(m1, normal.CalculateMembership(3));
	ASSERT_FLOAT_EQ(m2, normal.CalculateMembership(4));


}


TEST_F(TrapezoidalTesting, SetterValidation){

	TrapezoidalFuzzySet toTest;

	ASSERT_FALSE(toTest.setPoints(2,2,1,4));
	ASSERT_FALSE(toTest.setPoints(2,2,4,4));
	ASSERT_FALSE(toTest.setPoints(1,3,5,1));
	ASSERT_FALSE(toTest.setPoints(-1, 0, 0, 1));
	ASSERT_FALSE(toTest.setPoints(4,5,6,4));

	ASSERT_TRUE(toTest.setPoints(1,1,4,6));
	ASSERT_TRUE(toTest.setPoints(1,3,4,4));

	TrapezoidalFuzzySet toTest_2;
	std::string nome = "nome_test";
	std::string empty = "";
	ASSERT_TRUE(toTest_2.configureSet(nome,-1,0,2,3));
	ASSERT_TRUE(toTest_2.configureSet(empty,1,1,6,9));

}

TEST_F(TrapezoidalTesting, OutOfBoundaries){

	ASSERT_FLOAT_EQ(0,rect_left.CalculateMembership(0));
	ASSERT_FLOAT_EQ(0,rect_left.CalculateMembership(10));
	ASSERT_FLOAT_EQ(0,rect_left.CalculateMembership(-10));

	ASSERT_FLOAT_EQ(0,normal.CalculateMembership(25));
	ASSERT_FLOAT_EQ(0,rect_left.CalculateMembership(-11));
	ASSERT_FLOAT_EQ(0,rect_left.CalculateMembership(6));
}

TEST_F(TrapezoidalTesting, NotInizializedSet){

	TrapezoidalFuzzySet toTest;
	std::string name ("name");
	std::string empty ("");
	std::string errated ("errated");
	ASSERT_LT(toTest.CalculateMembership(12),0);

	toTest.setPoints(1,2,4,1);
	ASSERT_LT(toTest.CalculateMembership(13),0);

	toTest.configureSet(name,-1,0,4,5);
	ASSERT_GT(toTest.CalculateMembership(3),0);

	TrapezoidalFuzzySet emptyName("");
	ASSERT_LT(emptyName.CalculateMembership(20),0);
	emptyName.setPoints(1,3,5,5);
	ASSERT_LT(emptyName.CalculateMembership(2),0);

	TrapezoidalFuzzySet errateSet(errated,-3,4,1,5);
	ASSERT_LT(errateSet.CalculateMembership(2),0);


}

TEST_F(TrapezoidalTesting, BoundariesFunctionTesting){

	TrapezoidalFuzzySet toTest;
	ASSERT_TRUE(notNumber::checkNaN(toTest.getLowBoundary()));
	ASSERT_TRUE(notNumber::checkNaN(toTest.getUpBoundary()));

	std::string name = "name";
	toTest.configureSet(name,-5,-5,0,10);
	ASSERT_FLOAT_EQ(-5, toTest.getLowBoundary());
	ASSERT_FLOAT_EQ(10, toTest.getUpBoundary());

}

TEST_F(TrapezoidalTesting, scaleTest){

	//Test scaled on non initialized fuzzy set
	TrapezoidalFuzzySet* test1 = new TrapezoidalFuzzySet();
	ASSERT_FALSE(test1->mamdaniScale(0.4));
	test1->setName("test");
	ASSERT_FALSE(test1->mamdaniScale(0.4));

	//Test the scaling on a correct fuzzy set
	ASSERT_TRUE(test1->setPoints(-2,-1,1,2));
	ASSERT_TRUE(test1->mamdaniScale(0.5));

	//test of a modification and configuration on a scaled fuzzy set
	ASSERT_FALSE(test1->setPoints(3,4, 5, 6));
	ASSERT_FALSE(test1->configureSet("nome", 1,2,3,4));

	//test that the membership is correct with the scaled value.

	ASSERT_EQ(test1->CalculateMembership(0),0.5);
	ASSERT_EQ(test1->CalculateMembership(2), 0);
	ASSERT_EQ(test1->CalculateMembership(1), 0.5);
	ASSERT_EQ(test1->CalculateMembership(1.25), 0.5);
	ASSERT_EQ(test1->CalculateMembership(1.75), 0.25);

	//Scaled test with scale 0
	TrapezoidalFuzzySet *test2 = new TrapezoidalFuzzySet("test2", -2, 0, 1, 2);

	ASSERT_TRUE(test2->mamdaniScale(0));
	ASSERT_EQ(test2->CalculateMembership(0), 0);

	//Scale with 1
	test1->mamdaniScale(1);

	ASSERT_EQ(test1->CalculateMembership(0),1);
	ASSERT_EQ(test1->CalculateMembership(2), 0);
	ASSERT_EQ(test1->CalculateMembership(1), 1);
	ASSERT_EQ(test1->CalculateMembership(1.25), 0.75);
	ASSERT_EQ(test1->CalculateMembership(1.75), 0.25);


	//Incorrect scaled value
	ASSERT_FALSE(test1->mamdaniScale(-0.5));
	ASSERT_FALSE(test1->mamdaniScale(1.5));

	//Rectangular trapezoid test value
	rect_left.mamdaniScale(0.5);
	rect_right.mamdaniScale(0.5);

	ASSERT_FLOAT_EQ(0.5, rect_left.CalculateMembership(3));
	ASSERT_FLOAT_EQ(0.5, rect_left.CalculateMembership(3.5));
	ASSERT_FLOAT_EQ(0.5, rect_left.CalculateMembership(5));

	ASSERT_FLOAT_EQ(0.5, rect_right.CalculateMembership(3));
	ASSERT_FLOAT_EQ(0.5, rect_right.CalculateMembership(3.5));
	ASSERT_FLOAT_EQ(0.5, rect_right.CalculateMembership(5));

	ASSERT_FLOAT_EQ(0.5, rect_left.CalculateMembership(5.5));
	ASSERT_FLOAT_EQ(0.25, rect_left.CalculateMembership(5.75));
	ASSERT_FLOAT_EQ(0.5, rect_left.CalculateMembership(5.25));

	ASSERT_FLOAT_EQ(0.5, rect_right.CalculateMembership(2.75));
	ASSERT_FLOAT_EQ(0.25, rect_right.CalculateMembership(2.25));
	ASSERT_FLOAT_EQ(0.5, rect_right.CalculateMembership(2.5));

}

TEST_F(TrapezoidalTesting, AreaTesting){

	ASSERT_FLOAT_EQ(7.0/2.0, rect_left.getArea());
	ASSERT_FLOAT_EQ(5.0/2.0, rect_right.getArea());
	ASSERT_FLOAT_EQ(5, normal.getArea());

	//not initialized rect
	TrapezoidalFuzzySet test;
	ASSERT_LT(test.getArea(),0);
	ASSERT_FALSE(test.setPoints(-1,0,-2,4));
	ASSERT_LT(test.getArea(),0);
	ASSERT_TRUE(test.configureSet("test", -5,-3,-1,0));
	ASSERT_FLOAT_EQ(7.0/2.0,test.getArea());

	//Test area of scaled triangle

	rect_left.mamdaniScale(0.5);
	ASSERT_FLOAT_EQ(7.5/4.0, rect_left.getArea());

}

TEST_F(TrapezoidalTesting, CentroidTesting){


	ASSERT_FLOAT_EQ(3.7619047, rect_left.getCentroid());

	ASSERT_FLOAT_EQ(3.7333333, rect_right.getCentroid());


	//not initialized triangle
	TrapezoidalFuzzySet test;
	ASSERT_TRUE(notNumber::checkNaN(test.getCentroid()));
	ASSERT_FALSE(test.setPoints(-1,0,-2,4));
	ASSERT_TRUE(notNumber::checkNaN(test.getCentroid()));
	ASSERT_TRUE(test.configureSet("test", 2,3,5,5));
	ASSERT_FLOAT_EQ(3.7333333, test.getCentroid());



}

