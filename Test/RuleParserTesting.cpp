#include "gtest/gtest.h"
#include "fuzzy_rules/RuleAnalyzer.h"
#include "linguistic_variables/MamdaniOutputVariable.h"
#include "fuzzy_sets/TriangularFuzzySet.h"
#include "fuzzy_sets/RectangularFuzzySet.h"



class RuleAnalyzerTesting: public ::testing::Test {

protected:

	RuleAnalyzer analyzer;
	MappedPointersContainer< InputLinguisticVariable>* input;
	MamdaniOutputVariable* out;

	virtual void SetUp(){

		//configuring input variables and set
		InputLinguisticVariable* water = new InputLinguisticVariable("water", -10, 10);
		InputLinguisticVariable* sea = new InputLinguisticVariable("sea", -10, 10);

		//adding set to variables
		water->addSet(new TriangularFuzzySet("high", -10, -9, -8));
		water->addSet(new TriangularFuzzySet("med", -9, -9, -7));
		water->addSet(new TriangularFuzzySet("low", -8, -7, -6));

		sea->addSet(new TriangularFuzzySet("cold", 0, 1,2));
		sea->addSet(new TriangularFuzzySet("neutral", -1, 1,2));
		sea->addSet(new TriangularFuzzySet("hot", -2, 1,2));


		input = new MappedPointersContainer< InputLinguisticVariable>();
		input->insert(water->getName(), water);
		input->insert(sea->getName(), sea);


		out = new MamdaniOutputVariable("valvola", -100,100);
		out->addSet(new RectangularFuzzySet("open", -10, 10));
		out->addSet(new RectangularFuzzySet("close", -20, 10));

		analyzer = RuleAnalyzer(input, out);
	}


};

TEST_F(RuleAnalyzerTesting, InvalidSintaxRuleTesting){

	//test with syntactical wrong proposition
	std::string wrong= "If water is high and sea is hot then ,valvola is ";
	std::string wrong2= "If water is high and sea is hot then ,valvola is 34dssf 342,,sd"; // extra character
	std::string wrong3= "If water is high and sea is hot then ,valvola  34dssf";//without is
	std::string wrong4= "If water is high and sea  hot then ,valvola is 34dssf";
	std::string wrong5= "If water is high sea is hot then ,valvola is 34dssf";//without and
	std::string wrong6= "If water is high and sea is hot ,valvola is 34dssf"; //without if
	std::string wrong7= "water is high and sea is hot then ,valvola is 34dssf"; // without
	std::string wrong8= "If water is high and sea is hot then valvola is open or close";// extra consequent


	MamdaniRule* wrong_r = new MamdaniRule(wrong);
	MamdaniRule* wrong_r2 = new MamdaniRule(wrong2);
	MamdaniRule* wrong_r3 = new MamdaniRule(wrong3);
	MamdaniRule* wrong_r4 = new MamdaniRule(wrong4);
	MamdaniRule* wrong_r5 = new MamdaniRule(wrong5);
	MamdaniRule* wrong_r6 = new MamdaniRule(wrong6);
	MamdaniRule* wrong_r7 = new MamdaniRule(wrong7);
	MamdaniRule* wrong_r8 = new MamdaniRule(wrong8);

	ASSERT_FALSE(analyzer.parseRule(wrong_r));
	ASSERT_FALSE(analyzer.parseRule(wrong_r2));
	ASSERT_FALSE(analyzer.parseRule(wrong_r3));
	ASSERT_FALSE(analyzer.parseRule(wrong_r4));
	ASSERT_FALSE(analyzer.parseRule(wrong_r5));
	ASSERT_FALSE(analyzer.parseRule(wrong_r6));
	ASSERT_FALSE(analyzer.parseRule(wrong_r7));
	ASSERT_FALSE(analyzer.parseRule(wrong_r8));

}


TEST_F(RuleAnalyzerTesting, InvalidVariableTesting){

	//test with missing variable proposition
	std::string invalid= "If wateras is high and sea is hot then valvola is open ";
	std::string invalid2= "If snow is high and sea is hot then valvola is open ";
	std::string invalid3= "If watera is high and seas is hot then valvola is open ";
	std::string invalid4= "If watera is high and sea is hot then valvolotta is open ";

	MamdaniRule* invalid_r = new MamdaniRule(invalid);
	MamdaniRule* invalid_r2 = new MamdaniRule(invalid2);
	MamdaniRule* invalid_r3 = new MamdaniRule(invalid3);
	MamdaniRule* invalid_r4 = new MamdaniRule(invalid4);
	 //add to the analyzer and parse it

	ASSERT_FALSE(analyzer.parseRule(invalid_r));
	ASSERT_FALSE(analyzer.parseRule(invalid_r2));
	ASSERT_FALSE(analyzer.parseRule(invalid_r3));
	ASSERT_FALSE(analyzer.parseRule(invalid_r4));

}

TEST_F(RuleAnalyzerTesting, invalidSetTesting){

	std::string invalid= "If wateras is cold and sea is hot then valvola is high ";
	std::string invalid2= "If wateras is high and sea is hotsd then valvola is open";

	MamdaniRule* invalid_r = new MamdaniRule(invalid);
	MamdaniRule* invalid_r2 = new MamdaniRule(invalid2);

	ASSERT_FALSE(analyzer.parseRule(invalid_r));
	ASSERT_FALSE(analyzer.parseRule(invalid_r2));
}

TEST_F(RuleAnalyzerTesting, correctnessTest){

	std::string valid= "If water is high and sea is hot then valvola is open";
	std::string valid2= "If water is not high and sea is hot then valvola is open";
	std::string valid3= "If water is high and sea is hot then valvola is not open   ";
	std::string valid4= "IF water is high AND sea is hot then valvola IS open";
	std::string valid5= "If water is high or sea is hot then valvola is open";
	std::string valid6= "If water is low and sea is cold or water is not low then valvola is open";
	std::string valid7= "If water is low or sea is cold or sea is cold then valvola is open";




	MamdaniRule* valid_r = new MamdaniRule(valid);
	MamdaniRule* valid_r2 = new MamdaniRule(valid2);
	MamdaniRule* valid_r3 = new MamdaniRule(valid3);
	MamdaniRule* valid_r4 = new MamdaniRule(valid4);
	MamdaniRule* valid_r5 = new MamdaniRule(valid5);
	MamdaniRule* valid_r6 = new MamdaniRule(valid6);
	MamdaniRule* valid_r7 = new MamdaniRule(valid7);


	ASSERT_TRUE(analyzer.parseRule(valid_r));
	ASSERT_TRUE(analyzer.parseRule(valid_r2));
	ASSERT_TRUE(analyzer.parseRule(valid_r3));
	ASSERT_TRUE(analyzer.parseRule(valid_r4));
	ASSERT_TRUE(analyzer.parseRule(valid_r5));
	ASSERT_TRUE(analyzer.parseRule(valid_r6));
	ASSERT_TRUE(analyzer.parseRule(valid_r7));

	analyzer.printRule(valid_r);
	analyzer.printRule(valid_r2);
	analyzer.printRule(valid_r3);
	analyzer.printRule(valid_r4);
	analyzer.printRule(valid_r5);
	analyzer.printRule(valid_r6);
	analyzer.printRule(valid_r7);



}

TEST_F(RuleAnalyzerTesting, spacingRuleNameTest){

	InputLinguisticVariable * spaced = new InputLinguisticVariable("I am spaced", -10, 10);
	spaced->addSet(new TriangularFuzzySet("high spaced", -10, -9, -8));
	spaced->addSet(new TriangularFuzzySet("med spaced", -9, -9, -7));
	spaced->addSet(new TriangularFuzzySet("low spaced", -8, -7, -6));

	out->addSet(new TriangularFuzzySet("high spaced", -10, -9, -8));

	input->insert(spaced->getName(), spaced);

	std::string valid= "If I am spaced is high spaced and sea is hot then valvola is open";
	std::string valid2= "If I am spaced is not high spaced and sea is hot then valvola is open";
	std::string valid3= "If I am spaced is med spaced and sea is hot then valvola is not open   ";
	std::string valid4= "IF I am spaced is low spaced AND sea is hot then valvola IS open";
	std::string valid5= "IF I am spaced is low spaced AND sea is hot then valvola IS high spaced";
	std::string invalid= "If I ms is cold and sea is hot then valvola is high ";
	std::string invalid2= "If I am spaced is cold and sea is hot then valvola is high ";


	MamdaniRule* valid_r = new MamdaniRule(valid);
	MamdaniRule* valid_r2 = new MamdaniRule(valid2);
	MamdaniRule* valid_r3 = new MamdaniRule(valid3);
	MamdaniRule* valid_r4 = new MamdaniRule(valid4);
	MamdaniRule* valid_r5 = new MamdaniRule(valid5);
	MamdaniRule* invalid_r = new MamdaniRule(invalid);
	MamdaniRule* invalid_r2 = new MamdaniRule(invalid2);


	ASSERT_TRUE(analyzer.parseRule(valid_r));
	ASSERT_TRUE(analyzer.parseRule(valid_r2));
	ASSERT_TRUE(analyzer.parseRule(valid_r3));
	ASSERT_TRUE(analyzer.parseRule(valid_r4));
	ASSERT_TRUE(analyzer.parseRule(valid_r5));
	ASSERT_FALSE(analyzer.parseRule(invalid_r));
	ASSERT_FALSE(analyzer.parseRule(invalid_r2));

}
TEST_F(RuleAnalyzerTesting, initializationTest){

	std::string valid= "If water is high and sea is hot then valvola is open";
	MamdaniRule* valid_r = new MamdaniRule(valid);
	RuleAnalyzer analiz2;
	ASSERT_FALSE(analiz2.parseRule(valid_r));
	ASSERT_TRUE(analyzer.parseRule(valid_r));

}
