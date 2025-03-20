#include <fstream>
#include <string>

namespace ssuds
{
	class WordReader
	{
	protected:
		std::string mFilename;

	public:
		WordReader(std::string fname);
		

		~WordReader();

		void getWord();

	};
}
