// main.cpp
#include <ordered_set.h>
#include <string>
#include <stdexcept>
#include <ostream>
#include "iostream"
#include "array_list.h"

int main(int argc, char** argv)
{
	ssuds::OrderedSet<float> fset;
	fset.insert(3.7f);
	fset.insert(1.9f);
	fset.insert(2.3f);
	fset.insert(1.9f);		// duplicate!
	fset.insert(0.1f);

	std::cout << fset.contains(1.9f) << "\n";		// true (1)
	std::cout << fset.contains(8.8f) << "\n";		// falst (0)

	ssuds::ArrayList<float> pre_order = fset.traversal(ssuds::TraversalType::PRE_ORDER);
	//             3.7
	//            / 
	//           1.9
	//           / \
	//         0.1  2.3
	// [3.7, 1.9, 0.1, 2.3]

	ssuds::ArrayList<float> in_order = fset.traversal(ssuds::TraversalType::IN_ORDER);
	// [0.1, 1.9, 2.3, 3.7]
}