#include <gtest/gtest.h>
#include <unordered_hashmap.h>

#define EXECUTE_HASHMAP_TESTS 1
#if EXECUTE_HASHMAP_TESTS

// Test fixture for UnorderedHashMap
class UnorderedHashMapTest : public ::testing::Test
{
protected:
    ssuds::UnorderedHashMap<std::string, int> map;

    void SetUp() override {
        // Initialize the map with some test data
        map["Alice"] = 25;
        map["Bob"] = 42;
        map["Charlie"] = 30;
    }
};

// Test insertion and retrieval using the [] operator
TEST_F(UnorderedHashMapTest, InsertAndRetrieve) {
    EXPECT_EQ(map["Alice"], 25);
    EXPECT_EQ(map["Bob"], 42);
    EXPECT_EQ(map["Charlie"], 30);

    // Insert a new key-value pair
    map["Eve"] = 35;
    EXPECT_EQ(map["Eve"], 35);
}

// Test updating an existing value
TEST_F(UnorderedHashMapTest, UpdateValue) {
    map["Alice"] = 26;
    EXPECT_EQ(map["Alice"], 26);
}

// Test the contains method
TEST_F(UnorderedHashMapTest, Contains) {
    EXPECT_TRUE(map.contains("Alice"));
    EXPECT_TRUE(map.contains("Bob"));
    EXPECT_FALSE(map.contains("Eve"));
}

// Test the remove method
TEST_F(UnorderedHashMapTest, Remove) {
    EXPECT_TRUE(map.remove("Bob"));
    EXPECT_FALSE(map.contains("Bob"));
    EXPECT_FALSE(map.remove("Eve")); // Removing a non-existent key
}

// Test the get_size method
TEST_F(UnorderedHashMapTest, GetSize) {
    EXPECT_EQ(map.get_size(), 3);
    map["Eve"] = 35;
    EXPECT_EQ(map.get_size(), 4);
    map.remove("Alice");
    EXPECT_EQ(map.get_size(), 3);
}

// Test the ostream operator
TEST_F(UnorderedHashMapTest, OstreamOperator) {
    std::ostringstream oss;
    oss << map;
    std::string output = oss.str();
    EXPECT_NE(output.find("Alice:25"), std::string::npos);
    EXPECT_NE(output.find("Bob:42"), std::string::npos);
    EXPECT_NE(output.find("Charlie:30"), std::string::npos);
}

// Test iteration
TEST_F(UnorderedHashMapTest, Iteration) {
    std::set<std::string> keys;
    for (auto it = map.begin(); it != map.end(); ++it) {
        keys.insert((*it).key);
    }
    EXPECT_EQ(keys.size(), 3);
    EXPECT_TRUE(keys.count("Alice"));
    EXPECT_TRUE(keys.count("Bob"));
    EXPECT_TRUE(keys.count("Charlie"));
}

// Test growing the map by exceeding the load factor
TEST_F(UnorderedHashMapTest, GrowMap) {
    for (int i = 0; i < 20; ++i) {
        map["Key" + std::to_string(i)] = i;
    }
    EXPECT_EQ(map.get_size(), 23); // 3 initial + 20 new
    EXPECT_EQ(map["Key0"], 0);
    EXPECT_EQ(map["Key19"], 19);
}

// Test edge cases: empty map
TEST(UnorderedHashMapEdgeCases, EmptyMap) {
    ssuds::UnorderedHashMap<std::string, int> empty_map;
    EXPECT_EQ(empty_map.get_size(), 0);
    EXPECT_FALSE(empty_map.contains("NonExistent"));
    EXPECT_FALSE(empty_map.remove("NonExistent"));
    std::ostringstream oss;
    oss << empty_map;
    EXPECT_EQ(oss.str(), "{}");
}

// Test edge cases: collision handling
TEST(UnorderedHashMapEdgeCases, CollisionHandling) {
    ssuds::UnorderedHashMap<int, int> collision_map(4); // Small capacity to force collisions
    collision_map[1] = 10;
    collision_map[5] = 20; // Assuming hash(1) % 4 == hash(5) % 4
    EXPECT_EQ(collision_map[1], 10);
    EXPECT_EQ(collision_map[5], 20);
    EXPECT_EQ(collision_map.get_size(), 2);
}

#endif