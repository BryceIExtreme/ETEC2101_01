#include "person.h"
namespace example
{
	class PersonDatabase
	{
	private:

		Person* my_array;			// This WILL hold (eventually)
		//   an array of Person objects.
		unsigned int my_array_size;	// The size of the my_array array
		//Person my_data[100];		// No! Can't go over
									// 100 entries

		std::string my_file_name;

	public:
		// This method should open the file, probably
		// reading in one person per line like this
		// 101 John Doe 42 13.5
		// 102 Sally Smith 18 19.75
		PersonDatabase(std::string fname);

		~PersonDatabase();

		// Adds a person
		void add_person(example::Person p);
		bool remove_person(int remove_id);
	};
}
