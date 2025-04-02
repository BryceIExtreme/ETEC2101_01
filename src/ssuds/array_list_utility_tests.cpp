#include <gtest/gtest.h>
#include <array_list.h>
#include <array_list_utility.h>

#define EXECUTE_ARRAY_LIST_UTILITY_TESTS 1
#if EXECUTE_ARRAY_LIST_UTILITY_TESTS

class ArrayListTestFixture : public ::testing::Test
{
protected:
	void SetUp() override
	{
		slist2.append("B");
		slist2.append("C");
		slist2.prepend("A");
		slist2.insert("D", 3);
	}

	void TearDown() override
	{

	}


	ssuds::ArrayList<std::string> slist1;
	ssuds::ArrayList<std::string> slist2;
	ssuds::ArrayList<int> ilist;
};

TEST_F(ArrayListTestFixture, Quicksort)
{
	quicksort(slist2, 0, 4, ssuds::SortOrder::ASCENDING);

}


#endif