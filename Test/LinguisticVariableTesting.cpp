/*
 * LinguisticVariableTesting.cpp
 *
 *  Created on: Oct 10, 2012
 *      Author: igloo
 */
#include "gtest/gtest.h"
#include "fuzzy_sets/TrapezoidalFuzzySet.h"
#include "fuzzy_sets/TriangularFuzzySet.h"
#include "fuzzy_sets/SingletonFuzzySet.h"
#include "fuzzy_sets/RectangularFuzzySet.h"
#include "linguistic_variables/LinguisticVariable.h"
#include "linguistic_variables/InputLinguisticVariable.h"

class LinguisticVariableTesting: public ::testing::Test {

protected:
	virtual void SetUp(){

		temperatura = std::string("temperatura");
		variable =  new LinguisticVariable(temperatura ,-10,10);
	}

	std::string temperatura;
	LinguisticVariable *variable;

};


TEST_F(LinguisticVariableTesting, TestingAddSetBoundariesValues){

	TriangularFuzzySet test_triangolo("test_triangolo");
	SingletonFuzzySet test_singleton("test_singleton");
	TriangularFuzzySet test_triangolo_boundaries("test_triangolo_boundaries");
	SingletonFuzzySet test_singleton_boundaries("test_singleton_boundaries");
	RectangularFuzzySet test_rectangular("test_rectangular");
	RectangularFuzzySet test_rectangular_boundaries("test_rectangular_boundaries");
	TrapezoidalFuzzySet test_trapezoidal("test_trapezoidal");
	TrapezoidalFuzzySet test_trapezoidal_boundaries("test_trapezoidal_boundaries");
	test_triangolo.setPoints(-11,0,10);
	test_singleton.setPoint(15.0);
	test_triangolo_boundaries.setPoints(-10.0,0,10.0);
	test_singleton_boundaries.setPoint(-10);
	test_rectangular.setPoints(8,15);
	test_rectangular_boundaries.setPoints(-10,10);
	test_trapezoidal.setPoints(-11,10,13,15);
	test_trapezoidal_boundaries.setPoints(-10,-10,1,10);

	ASSERT_FALSE(variable->addSet(&test_triangolo));
	ASSERT_TRUE(variable->addSet(&test_triangolo_boundaries));
	ASSERT_FALSE(variable->addSet(&test_singleton));
	ASSERT_TRUE(variable->addSet(&test_singleton_boundaries));
	ASSERT_FALSE(variable->addSet(&test_rectangular));
	ASSERT_TRUE(variable->addSet(&test_rectangular_boundaries));
	ASSERT_FALSE(variable->addSet(&test_trapezoidal));
	ASSERT_TRUE(variable->addSet(&test_trapezoidal_boundaries));

	//Testing with correct value

	TriangularFuzzySet triangolo_correct("triangolo_correct");
	SingletonFuzzySet  singleton_correct("singleton_correct");
	RectangularFuzzySet rectangular_correct("rectangular_correct");
	TrapezoidalFuzzySet trapezoidal_correct("trapezoidal_correct");

	triangolo_correct.setPoints(-1.5,0,1);
	singleton_correct.setPoint(0.05);
	rectangular_correct.setPoints(5,8);
	trapezoidal_correct.setPoints(-0.002,1,3.5,5);

	ASSERT_TRUE(variable->addSet(&triangolo_correct));
	ASSERT_TRUE(variable->addSet(&singleton_correct));
	ASSERT_TRUE(variable->addSet(&rectangular_correct));
	ASSERT_TRUE(variable->addSet(&trapezoidal_correct));

}

TEST_F(LinguisticVariableTesting, TestingAddInvalidSet){

	TriangularFuzzySet triangle;
	TrapezoidalFuzzySet trapezoid;
	SingletonFuzzySet singleton;
	RectangularFuzzySet rectangle;

	ASSERT_FALSE(variable->addSet(&triangle));
	ASSERT_FALSE(variable->addSet(&trapezoid));
	ASSERT_FALSE(variable->addSet(&singleton));
	ASSERT_FALSE(variable->addSet(&rectangle));

	std::string name = "name";
	triangle.configureSet(name, 5, 6, 7);

	ASSERT_TRUE(variable->addSet(&triangle));
}

TEST_F(LinguisticVariableTesting, testAddExistingSet){

	TriangularFuzzySet triangle("triangle",1,2,3);
	RectangularFuzzySet rect("triangle", 3,5);

	variable->addSet(&triangle);
	ASSERT_FALSE(variable->addSet(&rect));

	TrapezoidalFuzzySet trapez("trapezoid", -10,0,9,10);
	ASSERT_TRUE(variable->addSet(&trapez));
}

TEST_F(LinguisticVariableTesting, testAddFunctionality){

	TriangularFuzzySet triangle ("triangle",1,2,3);

	variable->addSet(&triangle);

	ASSERT_TRUE(variable->hasSet("triangle"));
}

TEST_F(LinguisticVariableTesting, testMembershipFunction){

	TriangularFuzzySet triangle("triangle", -1,0,1);
	variable->addSet(&triangle);

	ASSERT_FLOAT_EQ(variable->membershipToASet("triangle",0.5), 0.5);
	ASSERT_EQ(variable->membershipToASet("triangle", -3),0);

	int id_triangle = variable->getSetID("triangle");

	ASSERT_FLOAT_EQ(variable->membershipToASet(id_triangle,0.5), 0.5);
	ASSERT_EQ(variable->membershipToASet(id_triangle, -3),0);
}

TEST_F(LinguisticVariableTesting, testMembershipFunctioninexistentSet){

	ASSERT_LT(variable->membershipToASet("",10),0);
	ASSERT_LT(variable->membershipToASet(10293,10),0);
	ASSERT_LT(variable->membershipToASet("prova",10),0);

}

TEST_F(LinguisticVariableTesting, testMembershipFunctionPointOutRange){

	TriangularFuzzySet triangle ("triangle", 1,2,3);
	variable->addSet(&triangle);
	int id_triangle = variable->getSetID("triangle");

	ASSERT_LT(variable->membershipToASet("triangle",100),0);
	ASSERT_LT(variable->membershipToASet(id_triangle,-20),0);

}

TEST_F(LinguisticVariableTesting, testGetSetIDENonExistent){

	ASSERT_LT(variable->getSetID("set"), 0);

}


TEST_F(LinguisticVariableTesting, testConsistenceVariable){

	LinguisticVariable empty_name= LinguisticVariable("",-10,10);
	ASSERT_FALSE(empty_name.checkConsistence());


	LinguisticVariable range2= LinguisticVariable("range",10,-10);
	ASSERT_FALSE(range2.checkConsistence());

	LinguisticVariable correct= LinguisticVariable("range",-10,10);
	ASSERT_TRUE(correct.checkConsistence());
}

TEST_F(LinguisticVariableTesting, InputVariableTest){

	InputLinguisticVariable input = InputLinguisticVariable ("test", -10, 10);
	InputLinguisticVariable input2 = InputLinguisticVariable ("tes2t", -15, 10);
	InputLinguisticVariable input3 = InputLinguisticVariable ("test3", -15, 10, -20);

	//test insertion incorrect value
	ASSERT_TRUE(input.setInput(-10));
	ASSERT_FALSE(input.setInput(11));

	//Test get value
	ASSERT_TRUE(notNumber::checkNaN(input2.getInput()));
	ASSERT_TRUE(notNumber::checkNaN(input3.getInput()));
	ASSERT_FLOAT_EQ(input.getInput(), -10);

	ASSERT_TRUE(input3.setInput(0));
	ASSERT_FLOAT_EQ(input3.getInput(), 0);

	//test getter
	ASSERT_TRUE(input.isSetInput());
	ASSERT_FALSE(input2.isSetInput());

}

TEST_F(LinguisticVariableTesting, copyConstructor){

	TriangularFuzzySet test_triangolo("test_triangolo");
	SingletonFuzzySet test_singleton("test_singleton");
	TriangularFuzzySet test_triangolo_boundaries("test_triangolo_boundaries");

	test_triangolo.setPoints(-10,0,10);
	test_singleton.setPoint(8.0);
	test_triangolo_boundaries.setPoints(-10.0,0,10.0);

	ASSERT_TRUE(variable->addSet(&test_triangolo));
	ASSERT_TRUE(variable->addSet(&test_triangolo_boundaries));
	ASSERT_TRUE(variable->addSet(&test_singleton));

	LinguisticVariable copy (*variable);

	ASSERT_TRUE(copy.hasSet("test_triangolo"));
	ASSERT_TRUE(copy.hasSet("test_singleton"));
	ASSERT_TRUE(copy.hasSet("test_triangolo_boundaries"));

	ASSERT_FLOAT_EQ(copy.getSet("test_triangolo")->getLowBoundary(), -10);
	ASSERT_FLOAT_EQ(copy.getSet("test_triangolo")->getUpBoundary(), 10);
}
