/*
 * MamdaniObjectTesting.cpp
 *
 *  Created on: Oct 31, 2012
 *      Author: igloo
 */
#include "gtest/gtest.h"
#include "MamdaniFuzzyObject.h"
#include "linguistic_variables/LinguisticVariable.h"
#include "fuzzy_sets/TrapezoidalFuzzySet.h"
#include "fuzzy_sets/TriangularFuzzySet.h"
#include "linguistic_variables/MamdaniOutputVariable.h"
#include "fuzzy_rules/MamdaniRule.h"
#include <string>

class MamdaniObjectTesting: public ::testing::Test {

protected:

	MamdaniFuzzyObject* calculator;

	virtual void SetUp(){

		calculator = new MamdaniFuzzyObject();

		//A perfect reply of the calculator example
		InputLinguisticVariable* x = new InputLinguisticVariable("x",-10,10);
		TrapezoidalFuzzySet* negative = new TrapezoidalFuzzySet("Negative", -10, -10, -1, 0);
		TriangularFuzzySet* zero = new TriangularFuzzySet("Zero", -1,0,1);
		TrapezoidalFuzzySet* positive = new TrapezoidalFuzzySet("Positive", 0,1,10,10);

		x->addSet(negative);
		x->addSet(zero);
		x->addSet(positive);

		MamdaniOutputVariable* y = new MamdaniOutputVariable("y", -3,3);
		TriangularFuzzySet* negative_2 = new TriangularFuzzySet("Negative", -2, -1, 0);
		TriangularFuzzySet* positive_2 = new TriangularFuzzySet("Positive", 0,1,2);
		TriangularFuzzySet* largenegative = new TriangularFuzzySet("Largenegative", -3, -2, -1);
		TriangularFuzzySet* largepositive = new TriangularFuzzySet("Largepositive",1,2,3);



		y->addSet(negative_2);
		y->addSet(zero);
		y->addSet(positive_2);
		y->addSet(largenegative);
		y->addSet(largepositive);

		InputLinguisticVariable* z = new InputLinguisticVariable("z", -10, 10);

		z->addSet(negative);
		z->addSet(zero);
		z->addSet(positive);

		calculator->addInputVar(x);
		calculator->setOutputVar(y);
		calculator->addInputVar(z);

		//adding rules
		calculator->addRule(new MamdaniRule("IF x IS Zero AND z IS Negative THEN y IS Negative"));
		calculator->addRule(new MamdaniRule("IF x IS Negative AND z IS Negative THEN y IS Largenegative"));
		calculator->addRule(new MamdaniRule("IF x IS Negative AND z IS Zero THEN y IS Negative"));
		calculator->addRule(new MamdaniRule("IF x IS Negative AND z IS Positive THEN y IS Zero"));
		calculator->addRule(new MamdaniRule("IF x IS Zero AND z IS Zero THEN y IS Zero"));
		calculator->addRule(new MamdaniRule("IF x IS Zero AND z IS Positive THEN y IS Positive"));
		calculator->addRule(new MamdaniRule("IF x IS Positive AND z IS Negative THEN y IS Zero"));
		calculator->addRule(new MamdaniRule("IF x IS Positive AND z IS Zero THEN y IS Positive"));
		calculator->addRule(new MamdaniRule("IF x IS Positive AND z IS Positive THEN y IS Largepositive"));


	}


};

TEST_F(MamdaniObjectTesting, TestAddingInputValue){

	//Test with float
	ASSERT_TRUE(calculator->setInput("x", -10));
	ASSERT_FALSE(calculator->setInput("as", -10));

	ASSERT_FLOAT_EQ(calculator->getInputValue("x"), -10);

	//Test with pointer to an object
	ASSERT_FALSE(calculator->setInput("z", calculator));
	ASSERT_TRUE(calculator->setInput("z", new MamdaniFuzzyObject()));
	ASSERT_FALSE(calculator->setInput("Ntive", new MamdaniFuzzyObject()));
	ASSERT_TRUE(calculator->setInput("z", new MamdaniFuzzyObject()));// repetition to see if substitute the value in the array

	//Test with a value outside of the variable range
	ASSERT_FALSE(calculator->setInput("x", -20));
	ASSERT_FALSE(calculator->setInput("x",11));

}

TEST_F(MamdaniObjectTesting, TestAddingInputVar){

	InputLinguisticVariable* duplicated = new InputLinguisticVariable("x",-10,10);
	ASSERT_FALSE(calculator->addInputVar(duplicated));

	//Variale invalid because of range
	InputLinguisticVariable* l = new InputLinguisticVariable("test",32,11);
	ASSERT_FALSE(calculator->addInputVar(l));

	//Variale invalid because of name
	InputLinguisticVariable* l2 = new InputLinguisticVariable("",11,32);
	ASSERT_FALSE(calculator->addInputVar(l2));

	//Variale invalid because of range and name
	InputLinguisticVariable* l3 = new InputLinguisticVariable("",32,11);
	ASSERT_FALSE(calculator->addInputVar(l3));

	//Correct variable
	InputLinguisticVariable* correct = new InputLinguisticVariable("correct",11,32);
	ASSERT_TRUE(calculator->addInputVar(correct));
}

TEST_F(MamdaniObjectTesting, TestSetOutputVar){

	MamdaniOutputVariable* out = new MamdaniOutputVariable("r",-4,10);
	ASSERT_FALSE(calculator->setOutputVar(out));

	MamdaniFuzzyObject object;
	ASSERT_TRUE(object.setOutputVar(out));
	ASSERT_FALSE(object.setOutputVar(out));


}

TEST_F(MamdaniObjectTesting, TestAddRule){

	MamdaniRule* correct = new MamdaniRule("IF x IS Negative AND z IS Zero THEN y IS Negative");
	MamdaniRule* correct_spacing =new MamdaniRule("IF  x IS Negative and z IS Zero THEN  y IS Largenegative");
	MamdaniRule* correct_lower =new MamdaniRule("if x is Negative and z is Zero then y is Negative");


	MamdaniRule* empty = new MamdaniRule();
	MamdaniRule* empty2 = new MamdaniRule("");
	MamdaniRule* incorrect1 =new MamdaniRule("IFa x IS Negative AND z IS Zero THEN y IS Negative");
	MamdaniRule* incorrect2 =new MamdaniRule("IF x  Negative AND z IS Zero THEN y IS Negative");
	MamdaniRule* incorrect3 =new MamdaniRule("IF x IS Negative AND z .IS Zero");
	MamdaniRule* incorrect4 =new MamdaniRule("IF x IS Negative z IS Zero THEN y IS Negative");
	MamdaniRule* variable_inexistent =new MamdaniRule("IF q IS Negative z IS Zero THEN y IS Negative");
	MamdaniRule* set_inexistent =new MamdaniRule("IF x IS Neative z IS Zero THEN y IS Negative");
	MamdaniRule* consequent_incorrect =new MamdaniRule("IF x IS Negative z IS Zero THEN x IS Negative");
	MamdaniRule* consequent_incorrect2 =new MamdaniRule("IF x IS Negative z IS Zero THEN x IS Negative AND false");


	ASSERT_TRUE(calculator->addRule(correct));
	ASSERT_TRUE(calculator->addRule(correct_lower));
	ASSERT_TRUE(calculator->addRule(correct_spacing));

	ASSERT_FALSE(calculator->addRule(empty));
	ASSERT_FALSE(calculator->addRule(empty2));
	ASSERT_FALSE(calculator->addRule(incorrect1));
	ASSERT_FALSE(calculator->addRule(incorrect2));
	ASSERT_FALSE(calculator->addRule(incorrect3));
	ASSERT_FALSE(calculator->addRule(incorrect4));
	ASSERT_FALSE(calculator->addRule(variable_inexistent));
	ASSERT_FALSE(calculator->addRule(set_inexistent));
	ASSERT_FALSE(calculator->addRule(consequent_incorrect));
	ASSERT_FALSE(calculator->addRule(consequent_incorrect2));


}

TEST_F(MamdaniObjectTesting, testCache){
	calculator->setInput("x", 0.5);
	calculator->setInput("z", 0.0);

	calculator->getOutput();//calculate the antecedent and consequent
	calculator->printCache();
}

TEST_F(MamdaniObjectTesting, testFuzzyReasining){

	//Test with no input value set
	calculator->setInput("z",1);
	float output = calculator->getOutput();
	ASSERT_TRUE(notNumber::checkNaN(output));

	calculator->setInput("x",1);
	calculator->setInput("z",1);

	 output = calculator->getOutput();

	//All the consequent set are 0 only largepositive is 1
	const MamdaniOutputVariable* out = calculator->getOutputVar();
	ASSERT_EQ(out->getNumberOfFinalSet(),1);

	ASSERT_FALSE(out->getSet(out->getSetID("Negative"))->isScaled());
	ASSERT_FALSE(out->getSet(out->getSetID("Largenegative"))->isScaled());
	ASSERT_FALSE(out->getSet(out->getSetID("Positive"))->isScaled());
	ASSERT_FALSE(out->getSet(out->getSetID("Zero"))->isScaled());
	ASSERT_FLOAT_EQ(out->getSet(out->getSetID("Largepositive"))->getScale(),1);
	ASSERT_TRUE(out->getSet(out->getSetID("Largepositive"))->isScaled());

	ASSERT_EQ(output, 2);


}

TEST_F(MamdaniObjectTesting, TestDefuzzificationSimple){
	//TestDeffuzification with no values
	ASSERT_TRUE(notNumber::checkNaN(calculator->getOutput()));

	calculator->setInput("x", 1);
	calculator->setInput("z",1);

	ASSERT_FLOAT_EQ(calculator->getOutput(),2);

	//DEffuzzify another time to set if the output variable is reset
	calculator->setInput("x",-1);
	calculator->setInput("z",-1);

	ASSERT_FLOAT_EQ(calculator->getOutput(),-2);

}


TEST_F(MamdaniObjectTesting, TestDefuzzificationNested){


	MamdaniFuzzyObject  *calculator2 = new MamdaniFuzzyObject();
	InputLinguisticVariable* x2 = new InputLinguisticVariable("x",-10,10);
	TrapezoidalFuzzySet* negative = new TrapezoidalFuzzySet("Negative", -10, -10, -1, 0);
	TriangularFuzzySet* zero = new TriangularFuzzySet("Zero", -1,0,1);
	TrapezoidalFuzzySet* positive = new TrapezoidalFuzzySet("Positive", 0,1,10,10);

	x2->addSet(negative);
	x2->addSet(zero);
	x2->addSet(positive);

	MamdaniOutputVariable* y2 = new MamdaniOutputVariable("y", -3,3);
	TriangularFuzzySet* negative_2 = new TriangularFuzzySet("Negative", -2, -1, 0);
	TriangularFuzzySet* positive_2 = new TriangularFuzzySet("Positive", 0,1,2);
	TriangularFuzzySet* largenegative = new TriangularFuzzySet("Largenegative", -3, -2, -1);
	TriangularFuzzySet* largepositive = new TriangularFuzzySet("Largepositive",1,2,3);



	y2->addSet(negative_2);
	y2->addSet(zero);
	y2->addSet(positive_2);
	y2->addSet(largenegative);
	y2->addSet(largepositive);

	InputLinguisticVariable* z2 = new InputLinguisticVariable("z", -10, 10);

	z2->addSet(negative);
	z2->addSet(zero);
	z2->addSet(positive);

	calculator2->addInputVar(x2);
	calculator2->setOutputVar(y2);
	calculator2->addInputVar(z2);

	//adding rules
	calculator2->addRule(new MamdaniRule("IF x IS Zero AND z IS Negative THEN y IS Negative"));
	calculator2->addRule(new MamdaniRule("IF x IS Negative AND z IS Negative THEN y IS Largenegative"));
	calculator2->addRule(new MamdaniRule("IF x IS Negative AND z IS Zero THEN y IS Negative"));
	calculator2->addRule(new MamdaniRule("IF x IS Negative AND z IS Positive THEN y IS Zero"));
	calculator2->addRule(new MamdaniRule("IF x IS Zero AND z IS Zero THEN y IS Zero"));
	calculator2->addRule(new MamdaniRule("IF x IS Zero AND z IS Positive THEN y IS Positive"));
	calculator2->addRule(new MamdaniRule("IF x IS Positive AND z IS Negative THEN y IS Zero"));
	calculator2->addRule(new MamdaniRule("IF x IS Positive AND z IS Zero THEN y IS Positive"));
	calculator2->addRule(new MamdaniRule("IF x IS Positive AND z IS Positive THEN y IS Largepositive"));

	calculator->setInput("x",1);
	calculator->setInput("z",calculator2);

	calculator2->setInput("x", -1);
	calculator2->setInput("z",-1);

	ASSERT_FLOAT_EQ(calculator->getOutput(),0);

}

TEST_F(MamdaniObjectTesting, TestDefuzzificationSimpleRepeatedRules){

	//adding another time a duplication of the rules
	calculator->addRule(new MamdaniRule("IF x IS Zero AND z IS Negative THEN y IS Negative"));
	calculator->addRule(new MamdaniRule("IF x IS Negative AND z IS Negative THEN y IS Largenegative"));
	calculator->addRule(new MamdaniRule("IF x IS Negative AND z IS Zero THEN y IS Negative"));
	calculator->addRule(new MamdaniRule("IF x IS Negative AND z IS Positive THEN y IS Zero"));
	calculator->addRule(new MamdaniRule("IF x IS Zero AND z IS Zero THEN y IS Zero"));
	calculator->addRule(new MamdaniRule("IF x IS Zero AND z IS Positive THEN y IS Positive"));
	calculator->addRule(new MamdaniRule("IF x IS Positive AND z IS Negative THEN y IS Zero"));
	calculator->addRule(new MamdaniRule("IF x IS Positive AND z IS Zero THEN y IS Positive"));
	calculator->addRule(new MamdaniRule("IF x IS Positive AND z IS Positive THEN y IS Largepositive"));

	//TestDeffuzification with no values
	ASSERT_TRUE(notNumber::checkNaN(calculator->getOutput()));

	calculator->setInput("x", 1);
	calculator->setInput("z",1);

	ASSERT_FLOAT_EQ(calculator->getOutput(),2);

	//DEffuzzify another time to set if the output variable is reset
	calculator->setInput("x",-1);
	calculator->setInput("z",-1);

	ASSERT_FLOAT_EQ(calculator->getOutput(),-2);

}



