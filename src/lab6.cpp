// main.cpp
#include <linked_list.h>
#include "string"
#include "iostream"

int main()
{
	ssuds::LinkedList<std::string> llist;
	ssuds::LinkedList<std::string> llist2;

	llist.append("Bob");
	llist.append("Carl");
	llist.append("Doug");
	llist.insert("Christine", 2);    // Takes Doug's spot, moves him "down"
	llist.prepend("Daisy");

	// [Daisy, Bob, Carl, Christine, Doug]

	llist2.append("Edgar");
	llist2.append("Nicki");
	llist2.append("Jessie");

	std::cout << "This list consists of:" << "\n";
	for (unsigned int i = 0; i < llist.size(); i++)
	{
		std::cout << i << "\t" << llist[i] << "\n";    // Much more expensive than ArrayList
	}													// ArrayList [] operator is O(1)
														// LinkedList [] operator is O(n)


	std::cout << llist.size() << "\n";		// 4

	ssuds::LinkedList<std::string>::LinkedListIterator it = llist.begin();
	std::cout << "This iterated list consists of:" << "\n";
	while (it != llist.end())
	{
		std::string temp = *it;
		std::cout << temp << "\n";
		++it;
	}
	std::cout << "Each value of this list is:" << "\n";
	for (std::string s : llist)
		std::cout << s << "\n";

	std::cout << "\n" << "FUNCTION TESTING" << "\n";
	std::cout  << llist[2] << "\n"; //Carl
	std::cout << llist.at(2) << "\n"; //Carl
	llist.remove(3); //Christine 
	std::cout << llist.size() << "\n";

	std::cout << llist.at(3) << "\n"; //Doug
	std::cout << llist.find("Carl") << "\n"; //2

	llist2.clear();
	std::cout << llist2 << "\n";
	
	ssuds::LinkedList<std::string>::LinkedListIterator it2 = llist.begin();
	ssuds::LinkedList<std::string>::LinkedListIterator it3 = llist.begin();
	ssuds::LinkedList<std::string>::LinkedListIterator it4 = llist.begin();

	it2 = llist.find("Carl", llist.begin());
	std::cout << *it2 << "\n";

	llist.append("Neveah");
	std::cout << "This list consists of:" << "\n";
	for (unsigned int i = 0; i < llist.size(); i++)
	{
		std::cout << i << "\t" << llist[i] << "\n";
	}
	it2= llist.remove(it2);
	std::cout << *it2 << "\n";
	std::cout << "This list consists of:" << "\n";
	for (unsigned int i = 0; i < llist.size(); i++)
	{
		std::cout << i << "\t" << llist[i] << "\n";
	}
	llist.append("Neveah");
	llist.append("Neveah");
	llist.prepend("Neveah");
	llist.remove_all("Neveah", it4);
	std::cout << "This list consists of:" << "\n";
	for (unsigned int i = 0; i < llist.size(); i++)
	{
		std::cout << i << "\t" << llist[i] << "\n";
	}




}
