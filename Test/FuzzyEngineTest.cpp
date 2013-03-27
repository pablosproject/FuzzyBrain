///*
// * FuzzyEngineTest.cpp
// *
// *  Created on: Nov 30, 2012
// *      Author: igloo
// */
//#include "gtest/gtest.h"
//#include "FuzzyEngine.h"
//
//
//class FuzzyEngineTesting: public ::testing::Test {
//
//protected:
//
//	FuzzyEngine *engine;
//	MamdaniFuzzyObject * calculator;
//
//	virtual void SetUp(){
//
//		engine = new FuzzyEngine();
//
//
//		calculator = new MamdaniFuzzyObject();
//
//				//A perfect reply of the calculator example
//				InputLinguisticVariable* x = new InputLinguisticVariable("x",-10,10);
//				TrapezoidalFuzzySet* negative = new TrapezoidalFuzzySet("Negative", -10, -10, -1, 0);
//				TriangularFuzzySet* zero = new TriangularFuzzySet("Zero", -1,0,1);
//				TrapezoidalFuzzySet* positive = new TrapezoidalFuzzySet("Positive", 0,1,10,10);
//
//				x->addSet(negative);
//				x->addSet(zero);
//				x->addSet(positive);
//
//				MamdaniOutputVariable* y = new MamdaniOutputVariable("y", -3,3);
//				TriangularFuzzySet* negative_2 = new TriangularFuzzySet("Negative", -2, -1, 0);
//				TriangularFuzzySet* positive_2 = new TriangularFuzzySet("Positive", 0,1,2);
//				TriangularFuzzySet* largenegative = new TriangularFuzzySet("Largenegative", -3, -2, -1);
//				TriangularFuzzySet* largepositive = new TriangularFuzzySet("Largepositive",1,2,3);
//
//
//
//				y->addSet(negative_2);
//				y->addSet(zero);
//				y->addSet(positive_2);
//				y->addSet(largenegative);
//				y->addSet(largepositive);
//
//				InputLinguisticVariable* z = new InputLinguisticVariable("z", -10, 10);
//
//				z->addSet(negative);
//				z->addSet(zero);
//				z->addSet(positive);
//
//				calculator->addInputVar(x);
//				calculator->setOutputVar(y);
//				calculator->addInputVar(z);
//
//				//adding rules
//				calculator->addRule(new MamdaniRule("IF x IS Zero AND z IS Negative THEN y IS Negative"));
//				calculator->addRule(new MamdaniRule("IF x IS Negative AND z IS Negative THEN y IS Largenegative"));
//				calculator->addRule(new MamdaniRule("IF x IS Negative AND z IS Zero THEN y IS Negative"));
//				calculator->addRule(new MamdaniRule("IF x IS Negative AND z IS Positive THEN y IS Zero"));
//				calculator->addRule(new MamdaniRule("IF x IS Zero AND z IS Zero THEN y IS Zero"));
//				calculator->addRule(new MamdaniRule("IF x IS Zero AND z IS Positive THEN y IS Positive"));
//				calculator->addRule(new MamdaniRule("IF x IS Positive AND z IS Negative THEN y IS Zero"));
//				calculator->addRule(new MamdaniRule("IF x IS Positive AND z IS Zero THEN y IS Positive"));
//				calculator->addRule(new MamdaniRule("IF x IS Positive AND z IS Positive THEN y IS Largepositive"));
//	}
//};
//
//TEST_F(FuzzyEngineTesting, TestAddingObjects){
//
//	//Use the calculator configuration already written
//
//}
//
