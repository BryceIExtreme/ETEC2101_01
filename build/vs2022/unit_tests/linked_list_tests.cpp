#include <gtest/gtest.h>
#include <linked_list.h>


#define EXECUTE_LINKED_LIST_TESTS 1
#if EXECUTE_LINKED_LIST_TESTS


class LinkedListTestFixture : public ::testing::Test
{
protected:
	void SetUp() override
	{
		llist2.append(1.0f);
		llist2.append(2.0f);
		llist2.append(3.0f);
		llist2.insert(4.4f, 1);
		
	}

	void TearDown() override
	{

	}


	ssuds::LinkedList<float> llist1;
	ssuds::LinkedList<float> llist2;
	ssuds::LinkedList<int> llist3;
	ssuds::LinkedList<float>::LinkedListIterator it2;
};


TEST_F(LinkedListTestFixture, InitialSizeMethod)
{
	EXPECT_EQ(llist1.size(), 0);
	EXPECT_EQ(llist2.size(), 4);
	EXPECT_EQ(llist3.size(), 0);
}

TEST_F(LinkedListTestFixture, ClearandCopy)
{
	ssuds::LinkedList<float> temp_list = llist2;
	EXPECT_EQ(temp_list.size(), 4);
	temp_list.clear();
	EXPECT_EQ(temp_list.size(), 0);
}

TEST_F(LinkedListTestFixture, AddingThings)
{
	llist1.append(3.0f);
	llist1.prepend(1.0f);
	llist1.insert(2.0f, 1);
	EXPECT_EQ(llist1.at(0), 1.0f);
	EXPECT_EQ(llist1.at(1), 2.0f);
	EXPECT_EQ(llist1.at(2), 3.0f);

}

TEST_F(LinkedListTestFixture, FindingThings)
{
	int location = llist2.find(3.0f);
	EXPECT_EQ(location, 3);

}

ssuds::LinkedList<float> move_func()
{
	ssuds::LinkedList<float> result;
	result.append(3.1f);
	result.append(4.2f);
	result.append(5.3f);
	result.append(6.4f);
	return result;
}

TEST_F(LinkedListTestFixture, MovingThings)
{
	ssuds::LinkedList<float> my_arr = move_func();
	EXPECT_EQ(my_arr.size(), 4);
	EXPECT_EQ(my_arr[0], 3.1f);
	EXPECT_EQ(my_arr[1], 4.2f);
	my_arr.remove(2);
	EXPECT_EQ(my_arr.size(), 3);

}

TEST_F(LinkedListTestFixture, RemovingThings)
{
	ssuds::LinkedList<float> llist4 = llist2;
	llist4.insert(6.6f, 2);
	llist4.remove(1);
	EXPECT_EQ(llist4.at(1), 6.6f);

}

TEST_F(LinkedListTestFixture, RemoveandFindIteratorStyle)
{
	ssuds::LinkedList<float>::LinkedListIterator it2 = llist2.begin();
	it2 = llist2.find(2.0f, llist2.begin());
	llist2.remove(it2);
	EXPECT_EQ(llist2.at(2), 3.0f);

}

TEST_F(LinkedListTestFixture, RemoveAll)
{
	ssuds::LinkedList<float> llist4 = llist2;
	ssuds::LinkedList<float>::LinkedListIterator it2 = llist4.begin();
	for (int i = 0; i < 5; i++)
	{
		llist4.append(7.0f);
	}
	llist4.remove_all(7.0f, it2);
	EXPECT_EQ(llist4.size(), 4);

}

TEST_F(LinkedListTestFixture, InitializerListConstructor)
{
	ssuds::LinkedList<int> test{ 5, 8, 9, 3, 1, 2, 7, 0 };
	ASSERT_EQ(test.size(), 8);
	EXPECT_EQ(test[0], 5);
	EXPECT_EQ(test[1], 8);
	EXPECT_EQ(test[2], 9);
	EXPECT_EQ(test[3], 3);
	EXPECT_EQ(test[4], 1);
	EXPECT_EQ(test[5], 2);
	EXPECT_EQ(test[6], 7);
	EXPECT_EQ(test[7], 0);
}

#endif