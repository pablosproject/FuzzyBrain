#include "gtest/gtest.h"
#include "engine_creator/XMLFPCreator.h"
#include "FuzzyEngine.h"
#include "linguistic_variables/LinguisticVariable.h"
#include "MamdaniFuzzyObject.h"
#include "fuzzy_sets/SingletonFuzzySet.h"
#include "fuzzy_sets/TrapezoidalFuzzySet.h"

class XMLFPTesting: public ::testing::Test {

protected:
	virtual void SetUp(){

	//simple xml with only one level
	creator = new XMLFPCreator("/Users/pablosproject/Documents/workspace/FuzzyBrain/Debug/birra_francesco.xml");
	}

	FuzzyEngine engine;
	XMLFPCreator* creator;

};

TEST_F(XMLFPTesting, parsingTestSimple){

	ASSERT_TRUE(creator->createEngine(&engine));

	//Test with some of the fuzzy set defined
	const MamdaniFuzzyObject* beer = engine.getObject("LaBirra");

	//Control that all the variables created exists
	const LinguisticVariable* colore =  beer->getInputVar("Colore");
	const LinguisticVariable* schiuma  =  beer->getInputVar("Schiuma");
	const LinguisticVariable* gradazione =  beer->getInputVar("Gradazione");
	const LinguisticVariable* fermentazione =  beer->getInputVar("Fermentazione");
	const LinguisticVariable* out = beer->getOutputVar();

	//test that all variables exists
	ASSERT_TRUE(colore != NULL);
	ASSERT_TRUE(schiuma != NULL);
	ASSERT_TRUE(gradazione != NULL);
	ASSERT_TRUE(fermentazione != NULL);
	ASSERT_TRUE(out != NULL);

	//test that the variables contain all teh fuzzy set indicated with the correct extreme values
	 // test type of value
	 const  TrapezoidalFuzzySet* colore_chiara = dynamic_cast<const TrapezoidalFuzzySet*>(colore->getSet("Chiara"));
	 const TrapezoidalFuzzySet* colore_rossa = dynamic_cast<const TrapezoidalFuzzySet*>(colore->getSet("Rossa"));
	 const TrapezoidalFuzzySet* colore_scura = dynamic_cast<const TrapezoidalFuzzySet*>(colore->getSet("Scura"));

	//test boundaries
	ASSERT_FLOAT_EQ(colore_chiara->getLowBoundary() , 0);
	ASSERT_FLOAT_EQ(colore_rossa->getLowBoundary()	, 3);
	ASSERT_FLOAT_EQ(colore_scura->getLowBoundary() ,  5);

	ASSERT_FLOAT_EQ(colore_chiara->getUpBoundary(), 4);
	ASSERT_FLOAT_EQ(colore_rossa->getUpBoundary(), 6);
	ASSERT_FLOAT_EQ(colore_scura->getUpBoundary() , 8);

	const SingletonFuzzySet* fermentaz_alta = dynamic_cast<const SingletonFuzzySet*>(fermentazione->getSet("Alta"));

	const SingletonFuzzySet* fermentaz_bassa = dynamic_cast<const SingletonFuzzySet*>(fermentazione->getSet("Bassa"));


	ASSERT_FLOAT_EQ(fermentaz_bassa->getLowBoundary(), 0);
	ASSERT_FLOAT_EQ(fermentaz_alta->getLowBoundary(), 1);

	//test output variable
	ASSERT_TRUE(out->getName() == "LaBirra");
	ASSERT_FLOAT_EQ(out->getMinRange() , 0);
	ASSERT_FLOAT_EQ(out->getMaxRange() , 8);
}

TEST_F(XMLFPTesting, fileErrorTest){
	//Test with an unexistent or inconsistent file
}
