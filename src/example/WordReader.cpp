#include <fstream>
#include "string"
#include "WordReader.h"

// Constructor stuff
// Binary and Text mode differ in how they handle newlines.  Binary just treats
// hello                   48, 50, 53, 53, 60, 10, 11
// bye                     40, 74, 53, 10, 11
ssuds::WordReader::WordReader(std::string fname) : mFilename(fname)
{
	std::ifstream fp(mFilename, std::ios::binary);
	if (fp.is_open())
	{

	}
	// Also, you can traverse to a given byte value like this
	fp.seekg(0, std::ios::end);			// Move file "pointer" to end of file
	size_t file_len = fp.tellg();		// GET file pointer location

	// Our approach in word-reader (credit to Jim Hudson) -- this is what's in the extract_word method
	// 1. Pick a random byte location from 0...file_len-1
	// 2. Move the file pointer to that spot (fp.seekg(random_spot, std::ios::beg)
	// 3. Character by character until we get right after the newline boundary
	//        fp.seekg(-1, std::ios::cur);    // Go back one character
	//        char c = fp.peek();			  // Get current character (without acutally reading)
	// 4. Now do a getline to read that line
	//      std::string read_word;
	//      std::getline(fp, read_word);	  // Read the current word.
};
	// Destructor is where you'd close the file.
	ssuds::WordReader::~WordReader()
	{
		std::ofstream fp(mFilename);
		fp.close();
	}