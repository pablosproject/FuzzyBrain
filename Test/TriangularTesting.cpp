#include "gtest/gtest.h"
#include "fuzzy_sets/TriangularFuzzySet.h"
#include <stdio.h>
#include <math.h>
#include "Utility.h"

class TriangularTesting: public ::testing::Test {

protected:

	virtual void SetUp(){

		 rect_left =TriangularFuzzySet("name_left" , 2, 2, 4);
		 rect_right =TriangularFuzzySet("name_right", 2, 4, 4);
		 normal =TriangularFuzzySet("name_normal",-1, 0, 1);

	}

	TriangularFuzzySet rect_left ;
	TriangularFuzzySet rect_right ;
	TriangularFuzzySet normal;
};

TEST_F(TriangularTesting , BoundariesOut){

	ASSERT_FLOAT_EQ(0,rect_left.CalculateMembership(1));
	ASSERT_FLOAT_EQ(0, rect_right.CalculateMembership(-2));
	ASSERT_FLOAT_EQ(0, normal.CalculateMembership(10));
}

TEST_F(TriangularTesting, BoundariesTriangle){

	ASSERT_FLOAT_EQ(1, rect_left.CalculateMembership(2));
	ASSERT_FLOAT_EQ(0, rect_left.CalculateMembership(4));
	ASSERT_FLOAT_EQ(0, rect_right.CalculateMembership(2));
	ASSERT_FLOAT_EQ(1, rect_right.CalculateMembership(4));
	ASSERT_FLOAT_EQ(0, normal.CalculateMembership(1));
	ASSERT_FLOAT_EQ(0, normal.CalculateMembership(-1));
}

TEST_F(TriangularTesting, TopOfTriangleInB){
	ASSERT_FLOAT_EQ(1,rect_left.CalculateMembership(2));
	ASSERT_FLOAT_EQ(1, rect_right.CalculateMembership(4));
	ASSERT_FLOAT_EQ(1, normal.CalculateMembership(0));
}

TEST_F(TriangularTesting, ConstructorTesting){

	TriangularFuzzySet ToTest;
	std::string test ("test");
	std::string empty ("");

	ASSERT_TRUE(ToTest.configureSet(test,-2,-1,0));
	ASSERT_FALSE(ToTest.configureSet(test,1,2,1));
	ASSERT_FALSE(ToTest.configureSet(test, 1,1,1));
	ASSERT_FALSE(ToTest.configureSet(test,1,-1,1));
	ASSERT_FALSE(ToTest.configureSet(test, 1,-1,2));
	ASSERT_FALSE(ToTest.configureSet(test,3,2,1));
	ASSERT_TRUE(ToTest.configureSet(empty,1,2,3));
	ASSERT_FALSE(ToTest.configureSet(empty,1,2,1));


}

TEST_F(TriangularTesting, NonValidSet){

	TriangularFuzzySet ToTest;
	std::string name ("name");
	std::string empty ("");
	std::string errated ("errated");

	ToTest.setPoints(-1,-2,-3);
	ASSERT_LT(ToTest.CalculateMembership(10),0);
	ToTest.configureSet(name,-1,-2,-3);
	ASSERT_LT(ToTest.CalculateMembership(10),0);


	TriangularFuzzySet emptyName("");
	ASSERT_LT(emptyName.CalculateMembership(20),0);
	emptyName.setPoints(1,3,5);
	ASSERT_LT(emptyName.CalculateMembership(2),0);

	TriangularFuzzySet errateSet(errated,-3,4,1);
	ASSERT_LT(errateSet.CalculateMembership(2),0);



}

TEST_F(TriangularTesting, BoundariesFunctionTesting){

	TriangularFuzzySet toTest;
	std::string name = "boundaries";

	ASSERT_TRUE(notNumber::checkNaN(toTest.getLowBoundary()));
	ASSERT_TRUE(notNumber::checkNaN(toTest.getUpBoundary()));

	toTest.configureSet(name,-5,0,10);
	ASSERT_FLOAT_EQ(-5, toTest.getLowBoundary());
	ASSERT_FLOAT_EQ(10, toTest.getUpBoundary());

}

TEST_F(TriangularTesting, scaleTest){

	//Test scaled on non initialized fuzzy set
	TriangularFuzzySet* test1 = new TriangularFuzzySet();
	ASSERT_FALSE(test1->mamdaniScale(0.4));
	test1->setName("test");
	ASSERT_FALSE(test1->mamdaniScale(0.4));

	//Test the scaling on a correct fuzzy set
	ASSERT_TRUE(test1->setPoints(-2,-1,1));
	ASSERT_TRUE(test1->mamdaniScale(0.5));

	//test of a modification and configuration on a scaled fuzzy set
	ASSERT_FALSE(test1->setPoints(3,4, 5));
	ASSERT_FALSE(test1->configureSet("nome", 1,2,3));

	//test that the membership is correct with the scaled value.

	ASSERT_EQ(test1->CalculateMembership(-1),0.5);
	ASSERT_EQ(test1->CalculateMembership(0), 0.5);
	ASSERT_EQ(test1->CalculateMembership(-1.5), 0.5);
	ASSERT_EQ(test1->CalculateMembership(-1.75), 0.25);

	//Scaled test with scale 0
	TriangularFuzzySet *test2 = new TriangularFuzzySet("test2", -2, 0, 1);

	ASSERT_TRUE(test2->mamdaniScale(0));
	ASSERT_EQ(test2->CalculateMembership(0), 0);
	ASSERT_EQ(test2->CalculateMembership(-1), 0);
	ASSERT_EQ(test2->CalculateMembership(0.5), 0);

	//Scale with 1
	test2->mamdaniScale(1);

	ASSERT_EQ(test2->CalculateMembership(1),0);
	ASSERT_EQ(test2->CalculateMembership(0), 1);
	ASSERT_EQ(test2->CalculateMembership(-2), 0);
	ASSERT_EQ(test2->CalculateMembership(0.75), 0.25);
	ASSERT_EQ(test2->CalculateMembership(-0.5), 0.75);
	ASSERT_EQ(test2->CalculateMembership(-1.5), 0.25);

	//Incorrect scaled value
	ASSERT_FALSE(test1->mamdaniScale(-0.5));
	ASSERT_FALSE(test1->mamdaniScale(1.5));

	//Rectangular trapezoid test value
	rect_left.mamdaniScale(0.5);
	rect_right.mamdaniScale(0.5);

	ASSERT_FLOAT_EQ(0.5, rect_left.CalculateMembership(3));
	ASSERT_FLOAT_EQ(0.25, rect_left.CalculateMembership(3.5));
	ASSERT_FLOAT_EQ(0.125, rect_left.CalculateMembership(3.75));
	ASSERT_FLOAT_EQ(0, rect_left.CalculateMembership(5));

	ASSERT_FLOAT_EQ(0.5, rect_right.CalculateMembership(3));
	ASSERT_FLOAT_EQ(0.5, rect_right.CalculateMembership(3.5));
	ASSERT_FLOAT_EQ(0.125, rect_right.CalculateMembership(2.25));
	ASSERT_FLOAT_EQ(0, rect_right.CalculateMembership(0));

}

TEST_F(TriangularTesting, AreaTesting){

	ASSERT_FLOAT_EQ(1, rect_left.getArea());
	ASSERT_FLOAT_EQ(1, rect_right.getArea());
	ASSERT_FLOAT_EQ(1, normal.getArea());

	//not initialized rect
	TriangularFuzzySet test;
	ASSERT_LT(test.getArea(),0);
	ASSERT_FALSE(test.setPoints(-1,0,-2));
	ASSERT_LT(test.getArea(),0);
	ASSERT_TRUE(test.configureSet("test", -5,-3,-1));
	ASSERT_FLOAT_EQ(2,test.getArea());

	//Test area of scaled triangle

	rect_left.mamdaniScale(0.5);
	ASSERT_FLOAT_EQ(0.75, rect_left.getArea());

	normal.mamdaniScale(0.75);
	float res2 = (2.5*0.75/2.0);
	ASSERT_FLOAT_EQ(res2,normal.getArea());
}

TEST_F(TriangularTesting, CentroidTesting){

	ASSERT_FLOAT_EQ(0, normal.getCentroid());

	float res = 8.0/3.0;
	ASSERT_FLOAT_EQ(res, rect_left.getCentroid());

	float res2 = 10.0/3.0;
	ASSERT_FLOAT_EQ(res2, rect_right.getCentroid());


	//not initialized triangle
	TriangularFuzzySet test;
	ASSERT_TRUE(notNumber::checkNaN(test.getCentroid()));
	ASSERT_FALSE(test.setPoints(-1,0,-2));
	ASSERT_TRUE(notNumber::checkNaN(test.getCentroid()));
	ASSERT_TRUE(test.configureSet("test", -5,-3,-1));
	ASSERT_FLOAT_EQ(-3, test.getCentroid());

	//scaled triangle

	normal.mamdaniScale(0.75);
	ASSERT_FLOAT_EQ(0,normal.getCentroid());

	rect_left.mamdaniScale(0.5);
	float res1 =2.7777777;
	ASSERT_FLOAT_EQ(res1, rect_left.getCentroid());

}

TEST_F (TriangularTesting, CopyConstructorTest){

	TriangularFuzzySet rect_left_2 = TriangularFuzzySet(rect_left);
	TriangularFuzzySet rect_right_2 = TriangularFuzzySet(rect_right);
	TriangularFuzzySet normal_2 = TriangularFuzzySet(normal);

	//TEst some method to see if it's correct

	ASSERT_FLOAT_EQ(0,rect_left_2.CalculateMembership(1));
	ASSERT_FLOAT_EQ(0, rect_right_2.CalculateMembership(-2));
	ASSERT_FLOAT_EQ(0, normal_2.CalculateMembership(10));

	ASSERT_FLOAT_EQ(1, rect_left_2.getArea());
	ASSERT_FLOAT_EQ(1, rect_right_2.getArea());
	ASSERT_FLOAT_EQ(1, normal_2.getArea());

	ASSERT_FLOAT_EQ(1,rect_left_2.CalculateMembership(2));
	ASSERT_FLOAT_EQ(1, rect_right_2.CalculateMembership(4));
	ASSERT_FLOAT_EQ(1, normal_2.CalculateMembership(0));

}

