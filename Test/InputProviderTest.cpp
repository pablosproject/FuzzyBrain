#include "gtest/gtest.h"
#include <string>
#include "linguistic_variables/InputLinguisticVariable.h"
#include "linguistic_variables/MamdaniOutputVariable.h"
#include "MamdaniFuzzyObject.h"
#include "FuzzyEngine.h"
#include "input_providers/ManualInputProvider.h"

class InputProviderTesting: public ::testing::Test {

protected:

	virtual void SetUp(){

		engine = new FuzzyEngine();
		obj1 = new MamdaniFuzzyObject();
		obj2Nested = new MamdaniFuzzyObject();
	//simple setup of a nested object

		InputLinguisticVariable *varObj1 = new InputLinguisticVariable("Inputobj1", -10,10);
		InputLinguisticVariable *var2Obj1 = new InputLinguisticVariable("Input2obj1", 0,10);
		InputLinguisticVariable *varObj2 = new InputLinguisticVariable("Inputobj2", -5,5);
		MamdaniOutputVariable *outObj1 = new MamdaniOutputVariable("outobj1",0,20);
		MamdaniOutputVariable *outObj2 = new MamdaniOutputVariable("outobj2", -20, 10);
		InputLinguisticVariable *varObj1Nested = new InputLinguisticVariable(*outObj2);

		obj1->addInputVar(varObj1);
		obj1->addInputVar(var2Obj1);
		obj1->addInputVar(varObj1Nested);
		obj1->setOutputVar(outObj1);

		obj1->setInput(varObj1Nested->getName(),obj2Nested);

		obj2Nested->addInputVar(varObj2);
		obj2Nested->setOutputVar(outObj2);

		engine->addRootFuzzyObject(obj1);
		engine->addFuzzyObject(obj2Nested);


	}

	FuzzyEngine *engine;
	MamdaniFuzzyObject *obj1;
	MamdaniFuzzyObject *obj2Nested;

};

TEST_F(InputProviderTesting, ManualProviderTest){

	std::string correct= "outobj1:Inputobj1:0.5\n; outobj1: Input2obj1:4; outobj2: Inputobj2:-2";
	std::string incorrect_name= "outbj1:Inputonj1:0;outobj1:Input2obj1:-25,1;outobj2:Inputobj2:0";
	std::string incorrect_name2= "outbj1: Inputonj1:0;outobj1:Inut2obj1:-25,1;outobj2:Inputobj2:0";
	std::string incorrect_values= "outbj1: Inputonj1:0;outobj1:Input2obj1:-25,1;outobj2:Inputobj2:-13";

	ManualInputProvider provider = ManualInputProvider(correct.c_str());
	ManualInputProvider provider2 = ManualInputProvider(incorrect_name.c_str());
	ManualInputProvider provider3 = ManualInputProvider(incorrect_name2.c_str());
	ManualInputProvider provider4 = ManualInputProvider(incorrect_values.c_str());

	ASSERT_TRUE(provider.processInput(engine));
	ASSERT_FALSE(provider2.processInput(engine));
	ASSERT_FALSE(provider3.processInput(engine));
	ASSERT_FALSE(provider4.processInput(engine));

	ASSERT_FLOAT_EQ(engine->getObject("outobj1")->getInputValue("Inputobj1"), 0.5);
	ASSERT_FLOAT_EQ(engine->getObject("outobj1")->getInputValue("Input2obj1"), 4);
	ASSERT_FLOAT_EQ(engine->getObject("outobj2")->getInputValue("Inputobj2"), -2);

}
