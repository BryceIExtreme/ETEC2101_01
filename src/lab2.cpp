// lab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using namespace std;
#include <array_list.h>			// Kind of like vector

int main(int argc, char** argv)
{
	ssuds::ArrayList<int> ilist;
	ilist.append(42);
	ilist.append(43);
	ilist.append(44);
	ilist.prepend(41);
	ilist.prepend(40);

	for (int i = 0; i < ilist.get_size(); i++)
		std::cout << "ilist[" << i << "] = " << ilist.at(i) << "\n";

	// [40, 41, 42, 43, 44]
	ilist.append(40);
	ilist.append(43);
	ilist.append(99);
	ilist.append(43);
	ilist.append(98);
	// [40, 41, 42, 43, 44, 40, 43, 99, 43, 98]
	int test = ilist.find(43);			// Should return 3
	test = ilist.find(43, 4);			// Should return 6
	test = ilist.find(43, 7);			// Should return 8
	test = ilist.find(43, 9);			// Should return -1
	test = ilist.find(104);				// Should return -1
	test = ilist.at(3);                 //Should return 43
	ilist.insert(23, 0);               
	test = ilist.at(0);                 //Should return 23
	ilist.insert(69, 5);
	test = ilist.at(5);                 //Should return 69


	ilist.output(std::cout);			// [40, 41, 42, 43, 44, 40, 43, 99, 43, 98]
	std::ofstream fout("test.txt");
	ilist.output(fout);

	ilist.remove(3);
	ilist.remove_all(40);


}
