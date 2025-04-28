#include <unordered_map>// std::unordered_map -- like our hashing-based (like Lab9)
// exactly the same methods/interface -- just slightly different big-O running times
#include <string>
#include <iostream>

int main(int argc, char** argv)
{
	// Maps are very similar to python DICTIONARIES.  Each element of the sequence is a
	// KEY-VALUE PAIR.  You get the value by giving a key.  There is no notion of an index
	// like the other sequence types.
	std::unordered_map<std::string, float> mmap;	// keys are strings, values are floats
	mmap["bob"] = 11.3f;		// A new pair
	mmap["sue"] = 13.9f;		// Second one
	mmap["carl"] = 15.6f;
	mmap["abe"] = 0.1f;
	mmap["doug"] = 16.3f;
	mmap["bob"] = 12.1f;		// Editing the value of an exising key

	std::cout << "mmap has " << mmap.size() << " items\n";			// 5
	std::cout << "mmap[bob] is " << mmap["bob"] << "\n";
	std::cout << "mmap[weird] is " << mmap["weird"] << "\n";		// This mistaken get causes an add????
	std::cout << "mmap has " << mmap.size() << " items\n";			// 6 -- see why?

	std::cout << "iterating through my map\n";
	std::unordered_map<std::string, float>::iterator it = mmap.begin();
	while (it != mmap.end())
	{
		std::pair<std::string, float> p;
		p = *it;

		std::cout << "\tkey=" << p.first << " and value=" << p.second << "\n";

		++it;
	}

	// Finding a value
	it = mmap.find("carl");
	if (it != mmap.end())
		std::cout << "carl found with a value of " << it->second << "\n";
	else
		std::cout << "carl not found\n";
	it = mmap.find("xyz");
	if (it != mmap.end())
		std::cout << "xyz found with a value of " << it->second << "\n";
	else
		std::cout << "xyz not found\n";


	// Removing from a map (here, I'm iterating and deleting some values)
	it = mmap.begin();
	while (it != mmap.end())
	{
		if (it->first == "weird")
			it = mmap.erase(it);
		else
			++it;
	}
	std::cout << "for-each loop after removing:\n";
	for (std::pair<std::string, float> temp_p : mmap)
	{
		std::cout << "\tkey=" << temp_p.first << " and value=" << temp_p.second << "\n";
	}
}
