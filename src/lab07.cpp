#include "ordered_set.h"
#include <iostream>
#include <string>
#include <array_list.h>

int main() 
{

    // Create an OrderedSet of integers
    ssuds::OrderedSet<int> intSet;

    // Test insert
    std::cout << "Inserting values into the OrderedSet...\n";
    intSet.insert(10);
    intSet.insert(5);
    intSet.insert(15);
    intSet.insert(3);
    intSet.insert(7);
    intSet.insert(10); // Duplicate, should not be inserted

    // Test contains
    std::cout << "Testing contains:\n";
    std::cout << "Contains 10: " << intSet.contains(10) << "\n"; // true
    std::cout << "Contains 20: " << intSet.contains(20) << "\n"; // false

    // Test traversal (Pre-order, In-order, Post-order)
    std::cout << "Testing traversal:\n";
    auto preOrder = intSet.traversal(ssuds::TraversalType::PRE_ORDER);
    std::cout << "Pre-order: " << preOrder << "\n";

    auto inOrder = intSet.traversal(ssuds::TraversalType::IN_ORDER);
    std::cout << "In-order: " << inOrder << "\n";

    auto postOrder = intSet.traversal(ssuds::TraversalType::POST_ORDER);
    std::cout << "Post-order: " << postOrder << "\n";

    // Test erase
    std::cout << "Testing erase:\n";
    intSet.erase(5);
    std::cout << "After erasing 5, In-order: " << intSet.traversal(ssuds::TraversalType::IN_ORDER) << "\n";

    // Test get_size
    std::cout << "Size of the OrderedSet: " << intSet.get_size() << "\n";

    // Test get_height
    std::cout << "Height of the OrderedSet: " << intSet.get_height() << "\n";

    // Test rebalance
    std::cout << "Testing rebalance:\n";
    intSet.rebalance();
    std::cout << "After rebalancing, In-order: " << intSet.traversal(ssuds::TraversalType::IN_ORDER) << "\n";
    std::cout << "After rebalancing, Size: " << intSet.get_size() << "\n";

    // Test get_parent
    std::cout << "Testing get_parent:\n";
    auto parent = intSet.get_parent(7);
    if (parent.has_value()) {
        std::cout << "Parent of 7: " << parent.value()->getData() << "\n";
    }
    else {
        std::cout << "Parent of 7 not found.\n";
    }

    // Test get_succesor
    std::cout << "Testing get_succesor:\n";
    try {
        std::cout << "Successor of 7: " << intSet.get_succesor(7) << "\n";
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Test clear
    std::cout << "Testing clear:\n";
    intSet.clear();
    std::cout << "After clearing, size: " << intSet.get_size() << "\n";

    // Test InOrderIterator
    std::cout << "Testing InOrderIterator:\n";
    intSet.insert(10);
    intSet.insert(5);
    intSet.insert(15);
    intSet.insert(3);
    intSet.insert(7);

    auto it = intSet.begin_in_order();
    while (it.has_next()) {
        std::cout << it.next() << " ";
    }
    std::cout << "\n";

    return 0;
}