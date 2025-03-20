
#include <gtest/gtest.h>
#include "array_list.h"
#include <iostream>

ssuds::ArrayList<float> ArrayListTestFixture = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f };



TEST_F(ArrayListTestFixture, Addingitems)
{
	ASSERT_EQ(ArrayListTestFixture.size(), 4);
	EXPECT_EQ(ArrayListTestFixture[0], "A");
	EXPECT_EQ(ArrayListTestFixture[1], "B");
	EXPECT_EQ(ArrayListTestFixture[2], "C");
	EXPECT_EQ(ArrayListTestFixture[3], "D");
};


