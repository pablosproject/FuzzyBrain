/*
 * MamdaniRuleTest.cpp
 *
 *  Created on: Oct 25, 2012
 *      Author: igloo
 */
#include "gtest/gtest.h"
#include "fuzzy_rules/MamdaniRule.h"
#include <string>
#include "operator/ZadehianAnd.h"
#include "operator/ZadehianOr.h"
#include "linguistic_variables/MamdaniOutputVariable.h"
#include "fuzzy_sets/TriangularFuzzySet.h"

class MamdaniRuleTesting: public ::testing::Test {

protected:

	virtual void SetUp(){

		rule_desc ="IF sea IS cold AND grass IS green THEN rain IS high";
		rule = MamdaniRule(rule_desc);

		/*
		 * TEMPERATURE: -low: 0
		 * 				- medium: 0.5
		 * 				-high: 0.5
		 * 	PRESSURE:   - low:0
		 * 				-medium: 0
		 * 				-high: 0.5
		 */
		vector<float> temperaturevalue(3, 0.0);
		vector<float> pressurevalue(3, 0.0);

		temperaturevalue[1] = 0.5;
		temperaturevalue[2] = 0.5;
		pressurevalue[2] = 1;
		value = vector<vector <float> >(2);
		value[0] = temperaturevalue;
		value[1] = pressurevalue;

		output = new MamdaniOutputVariable("valvola",-5,5);
		TriangularFuzzySet* low = new TriangularFuzzySet("low", -2, -1, 0);
		TriangularFuzzySet* high = new TriangularFuzzySet("high", 0, 1, 2);
		TriangularFuzzySet* close = new TriangularFuzzySet("close", -1, 0, 1);
		output->addSet(low);
		output->addSet(close );
		output->addSet(high);


	}

	std::string rule_desc;
	MamdaniRule rule;
	valueCache value;
	MamdaniOutputVariable* output;

};

TEST_F(MamdaniRuleTesting, TestAddAntecedentConsequent){

	ASSERT_FALSE(rule.addAntecedentToken(-1,0, false, FuzzyRule::AND));
	ASSERT_FALSE(rule.addAntecedentToken(100,-3, false, FuzzyRule::OR));
	ASSERT_TRUE(rule.addAntecedentToken(3,20, false, FuzzyRule::AND));
	ASSERT_TRUE(rule.addAntecedentToken(0,20, false, FuzzyRule::OR));

	ASSERT_FALSE(rule.addConsequent("",1, false));
	ASSERT_FALSE(rule.addConsequent("rain",-4, false));
	ASSERT_TRUE(rule.addConsequent("rain",0, false));

	ASSERT_TRUE(rule.hasAntecedentToken(0,20, false));
	ASSERT_FALSE(rule.hasAntecedentToken(-1,1, false));
}

TEST_F(MamdaniRuleTesting, TestConstructorEmpty){


}
TEST_F(MamdaniRuleTesting, TestEvaluateAntecedentZadehianAndOR){

	MamdaniRule simple;
	MamdaniRule simpleOr;
	MamdaniRule simplenot;
	MamdaniRule simpleOrNot;
	MamdaniRule complex1;
	MamdaniRule complex2;

	 AndOperator* andop= new ZadehianAnd();
	 OrOperator* orop = new ZadehianOr();

	//if temperature is medium and pressure is high then
	simple.addAntecedentToken(0,1,false,FuzzyRule::AND);
	simple.addAntecedentToken(1,2,false,FuzzyRule::AND);
	simple.setAndOperator(andop);
	simple.setOrOperator(orop);
	//if temperature is medium or pressure is high
	simpleOr.addAntecedentToken(0,1,false,FuzzyRule::AND);
	simpleOr.addAntecedentToken(1,2,false,FuzzyRule::OR);
	simpleOr.setAndOperator(andop);
	simpleOr.setOrOperator(orop);
	//if temperature is not medium and pressure is not high
	simplenot.addAntecedentToken(0,1,true,FuzzyRule::AND);
	simplenot.addAntecedentToken(1,2,true,FuzzyRule::AND);
	simplenot.setAndOperator(andop);
	simplenot.setOrOperator(orop);
	//if temperature is no medium or pressure is not high
	simpleOrNot.addAntecedentToken(0,1,true,FuzzyRule::AND);
	simpleOrNot.addAntecedentToken(1,2,true,FuzzyRule::OR);
	simpleOrNot.setAndOperator(andop);
	simpleOrNot.setOrOperator(orop);
	//if temperature is high and pressure is high or if pressure is medium and temperature is medium
	complex1.addAntecedentToken(0,2,false,FuzzyRule::AND);
	complex1.addAntecedentToken(1,2,false,FuzzyRule::AND);
	complex1.addAntecedentToken(1,1,false,FuzzyRule::OR);
	complex1.addAntecedentToken(0,1,false,FuzzyRule::AND);
	complex1.setAndOperator(andop);
	complex1.setOrOperator(orop);
	//if temperature is not low or pressure is high or if pressure is medium and temperature is medium
	complex2.addAntecedentToken(0,0,true,FuzzyRule::AND);
	complex2.addAntecedentToken(1,2,false,FuzzyRule::OR);
	complex2.addAntecedentToken(0,1,false,FuzzyRule::OR);
	complex2.addAntecedentToken(1,1,false,FuzzyRule::AND);
	complex2.setAndOperator(andop);
	complex2.setOrOperator(orop);

	ASSERT_FLOAT_EQ(simple.evaluateAntecedent(value),0.5);
	ASSERT_FLOAT_EQ(simpleOr.evaluateAntecedent(value),1);
	ASSERT_FLOAT_EQ(simplenot.evaluateAntecedent(value), 0);
	ASSERT_FLOAT_EQ(simpleOrNot.evaluateAntecedent(value),0.5);
	ASSERT_FLOAT_EQ(complex1.evaluateAntecedent(value),0.5);
	ASSERT_FLOAT_EQ(complex2.evaluateAntecedent(value),1);
}

TEST_F(MamdaniRuleTesting, TestGetConsequent){

	MamdaniRule simple;
	MamdaniRule simpleOr;
	MamdaniRule simplenot;
	MamdaniRule simpleOrNot;
	MamdaniRule complex1;
	MamdaniRule complex2;

	 AndOperator* andop= new ZadehianAnd();
	 OrOperator* orop = new ZadehianOr();

	 //test adding non coherent consequent
	 simple.addConsequent("valvol", 2,false);
	 ASSERT_FALSE(simple.modulateConsequent(output, 0.5));

	 simple.addConsequent("valvola", 4,false);
	 ASSERT_FALSE(simple.modulateConsequent(output, 0.5));

	 //not valid scaling value
	 simple.addConsequent("valvola", 0,false);
	 ASSERT_FALSE(simple.modulateConsequent(output, 1.2));




	//if temperature is medium and pressure is high-- 0.5
	simple.addAntecedentToken(0,1,false,FuzzyRule::AND);
	simple.addAntecedentToken(1,2,false,FuzzyRule::AND);
	simple.setAndOperator(andop);
	simple.setOrOperator(orop);
	//then valvolva is high
	simple.addConsequent("valvola",2,false);
	ASSERT_TRUE(simple.modulateConsequent(output, 0.5));
	ASSERT_FLOAT_EQ(output->getSet(2)->getScale(), 0.5);

	//if temperature is medium or pressure is high-- 1
	simpleOr.addAntecedentToken(0,1,false,FuzzyRule::AND);
	simpleOr.addAntecedentToken(1,2,false,FuzzyRule::OR);
	simpleOr.setAndOperator(andop);
	simpleOr.setOrOperator(orop);
	//then valvola is not high
	simpleOr.addConsequent("valvola",2,false);
	ASSERT_TRUE(simpleOr.modulateConsequent(output, 1));
	ASSERT_FLOAT_EQ(output->getSet(2)->getScale(), 1); // increment the value existent
	ASSERT_EQ(output->getNumberOfFinalSet(),1);//verify that has not added another set to the modulated array

	//if temperature is no medium or pressure is not high
	simpleOrNot.addAntecedentToken(0,1,true,FuzzyRule::AND);
	simpleOrNot.addAntecedentToken(1,2,true,FuzzyRule::OR);
	simpleOrNot.setAndOperator(andop);
	simpleOrNot.setOrOperator(orop);
	//then valvola is close
	simpleOrNot.addConsequent("valvola",1,false);
	ASSERT_TRUE(simpleOrNot.modulateConsequent(output, 0.5));
	ASSERT_FLOAT_EQ(output->getSet(1)->getScale(), 0.5); // increment the value existent
	ASSERT_EQ(output->getNumberOfFinalSet(),2);//verify that has not added another set to the modulated array

	//if temperature is not low or pressure is high or if pressure is medium and temperature is medium
	complex2.addAntecedentToken(0,0,true,FuzzyRule::AND);
	complex2.addAntecedentToken(1,2,false,FuzzyRule::OR);
	complex2.addAntecedentToken(0,1,false,FuzzyRule::OR);
	complex2.addAntecedentToken(1,1,false,FuzzyRule::AND);
	complex2.setAndOperator(andop);
	complex2.setOrOperator(orop);
	//then valvola is low
	simpleOrNot.addConsequent("valvola",0,false);
	ASSERT_TRUE(simpleOrNot.modulateConsequent(output, 0.5));
	ASSERT_FLOAT_EQ(output->getSet(0)->getScale(), 0.5); // increment the value existent
	ASSERT_EQ(output->getNumberOfFinalSet(),3);//verify that has not added another set to the modulated array


}

