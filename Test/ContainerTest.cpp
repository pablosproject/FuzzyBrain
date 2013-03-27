#include "gtest/gtest.h"
#include "MappedPointersContainer.hpp"
#include "fuzzy_sets/TriangularFuzzySet.h"

class MappedTesting: public ::testing::Test {

protected:
	virtual void SetUp(){

		first = new TriangularFuzzySet("first", -1, 2,3);
		second = new TriangularFuzzySet("second", 1, 3,4);
		third = new TriangularFuzzySet("third", 2, 5,6);

		container.insert(first->getName(),first);
		container.insert(second->getName(),second);
		container.insert(third->getName(),third);


	}

	MappedPointersContainer<TriangularFuzzySet> container;
	TriangularFuzzySet* first;
	TriangularFuzzySet* second;
	TriangularFuzzySet* third;


};

TEST_F(MappedTesting , InsertTesting){

	TriangularFuzzySet* empty = new TriangularFuzzySet("",-1,3,5);
	ASSERT_FALSE(container.insert(empty->getName(), empty));

	std::string name = "test";
	empty->configureSet(name, -1,3,5);
	ASSERT_TRUE(container.insert(empty->getName(), empty));

	TriangularFuzzySet* repeated = new TriangularFuzzySet("test", 1,3,5);
	ASSERT_FALSE(container.insert(repeated->getName(), repeated));

	ASSERT_FALSE(container.insert(repeated->getName(), NULL));
}


TEST_F(MappedTesting, HasTesting){

	ASSERT_TRUE(container.hasElement("first"));
	ASSERT_FALSE(container.hasElement("fourth"));
	ASSERT_FALSE(container.hasElement(""));

}

TEST_F(MappedTesting, GetTesting){

	ASSERT_EQ(first, container.getElement("first"));
	ASSERT_EQ(NULL, container.getElement("fourth"));
	ASSERT_EQ(NULL, container.getElement(""));
}

TEST_F(MappedTesting, GetIDTesting){

	ASSERT_GE(container.getID("first"), 0);
	ASSERT_LT(container.getID("tesgg"), 0);
	ASSERT_LT(container.getID(""), 0);
}

TEST_F(MappedTesting, GetElementIDTEsting){

	int id = container.getID("first");
	FuzzySet* result = container.getElement(id);

	ASSERT_EQ(result, first);
	ASSERT_EQ(NULL, container.getElement(103));
}

TEST_F(MappedTesting, HasIDTesting){

	int id = container.getID("second");

	ASSERT_TRUE(container.hasID(id));
	ASSERT_FALSE(container.hasID(6344));
}

TEST_F(MappedTesting, CopyConstructorTesting){

	MappedPointersContainer <TriangularFuzzySet> copy = MappedPointersContainer<TriangularFuzzySet>(container);

	ASSERT_TRUE(copy.getElement("first") != container.getElement("first"));

	//various test
	ASSERT_GE(copy.getID("first"), 0);
	ASSERT_LT(copy.getID("tesgg"), 0);

	int id = container.getID("first");
	FuzzySet* result = container.getElement(id);

	ASSERT_EQ(result, first);
	ASSERT_EQ(NULL, container.getElement(103));

	TriangularFuzzySet* empty = new TriangularFuzzySet("",-1,3,5);
	ASSERT_FALSE(container.insert(empty->getName(), empty));
	std::string name = "test";
	empty->configureSet(name, -1,3,5);
	ASSERT_TRUE(container.insert(empty->getName(), empty));
}
