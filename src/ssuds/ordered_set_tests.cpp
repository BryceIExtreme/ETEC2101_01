#include <gtest/gtest.h>
#include <ordered_set.h>
#include <array_list.h>
#include <string>


#define EXECUTE_ORDEREDSET_TESTS 1
#if EXECUTE_ORDEREDSET_TESTS

namespace ssuds {

    class OrderedSetTests : public ::testing::Test {
    protected:
        OrderedSet<int> intSet;
        OrderedSet<std::string> stringSet;

        void SetUp() override {
            // Initialize the integer set with some values
            intSet.insert(10);
            intSet.insert(5);
            intSet.insert(15);
            intSet.insert(3);
            intSet.insert(7);

            // Initialize the string set with some values
            stringSet.insert("apple");
            stringSet.insert("banana");
            stringSet.insert("cherry");
            stringSet.insert("date");
            stringSet.insert("elderberry");
        }
    };

    // Test insertion and size
    TEST_F(OrderedSetTests, TestInsertAndSize) {
        EXPECT_EQ(intSet.get_size(), 5);
        EXPECT_TRUE(intSet.contains(10));
        EXPECT_TRUE(intSet.contains(5));
        EXPECT_FALSE(intSet.contains(20));

        EXPECT_EQ(stringSet.get_size(), 5);
        EXPECT_TRUE(stringSet.contains("apple"));
        EXPECT_FALSE(stringSet.contains("fig"));
    }

    // Test traversal (in-order, pre-order, post-order)
    TEST_F(OrderedSetTests, TestTraversal) {
        auto inOrder = intSet.traversal(TraversalType::IN_ORDER);
        EXPECT_EQ(inOrder.size(), 5);
        EXPECT_EQ(inOrder[0], 3);
        EXPECT_EQ(inOrder[1], 5);
        EXPECT_EQ(inOrder[2], 7);
        EXPECT_EQ(inOrder[3], 10);
        EXPECT_EQ(inOrder[4], 15);

        auto preOrder = intSet.traversal(TraversalType::PRE_ORDER);
        EXPECT_EQ(preOrder.size(), 5);

        auto postOrder = intSet.traversal(TraversalType::POST_ORDER);
        EXPECT_EQ(postOrder.size(), 5);
    }

    // Test rebalance
    TEST_F(OrderedSetTests, TestRebalance) {
        intSet.rebalance();
        EXPECT_EQ(intSet.get_size(), 5);

        auto inOrder = intSet.traversal(TraversalType::IN_ORDER);
        EXPECT_EQ(inOrder[0], 3);
        EXPECT_EQ(inOrder[1], 5);
        EXPECT_EQ(inOrder[2], 7);
        EXPECT_EQ(inOrder[3], 10);
        EXPECT_EQ(inOrder[4], 15);

        EXPECT_EQ(intSet.get_height(), 3); // After rebalancing, height should be minimal
    }

    // Test height
    TEST_F(OrderedSetTests, TestHeight) {
        EXPECT_EQ(intSet.get_height(), 3); // Initial height
        intSet.insert(20);
        EXPECT_EQ(intSet.get_height(), 3); // Height increases after insertion
    }

    // Test erase
    TEST_F(OrderedSetTests, TestErase) {
        EXPECT_TRUE(intSet.contains(5));
        intSet.erase(5);
        EXPECT_FALSE(intSet.contains(5));
        EXPECT_EQ(intSet.get_size(), 4);

        auto inOrder = intSet.traversal(TraversalType::IN_ORDER);
        EXPECT_EQ(inOrder.size(), 4);
        EXPECT_EQ(inOrder[0], 3);
        EXPECT_EQ(inOrder[1], 7);
        EXPECT_EQ(inOrder[2], 10);
        EXPECT_EQ(inOrder[3], 15);
    }

    // Test get_parent
    TEST_F(OrderedSetTests, TestGetParent) {
        auto parent = intSet.get_parent(7);
        ASSERT_TRUE(parent.has_value());
        EXPECT_EQ(parent.value()->getData(), 5);

        auto noParent = intSet.get_parent(10); // Root node has no parent
        EXPECT_FALSE(noParent.has_value());
    }

    // Test get_successor
    TEST_F(OrderedSetTests, TestGetSuccessor) {
        EXPECT_EQ(intSet.get_succesor(7), 10);
        EXPECT_EQ(intSet.get_succesor(5), 7);

        EXPECT_THROW(intSet.get_succesor(20), std::runtime_error); // Value not in the tree
    }

    // Test clear
    TEST_F(OrderedSetTests, TestClear) {
        intSet.clear();
        EXPECT_EQ(intSet.get_size(), 0);
        EXPECT_FALSE(intSet.contains(10));
        EXPECT_FALSE(intSet.contains(5));
    }

    // Test InOrderIterator
    TEST_F(OrderedSetTests, TestInOrderIterator) {
        auto it = intSet.begin_in_order();
        std::vector<int> values;
        while (it.has_next()) {
            values.push_back(it.next());
        }

        EXPECT_EQ(values.size(), 5);
        EXPECT_EQ(values[0], 3);
        EXPECT_EQ(values[1], 5);
        EXPECT_EQ(values[2], 7);
        EXPECT_EQ(values[3], 10);
        EXPECT_EQ(values[4], 15);
    }
}


#endif