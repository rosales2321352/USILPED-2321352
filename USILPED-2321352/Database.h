#pragma once


#include <string>
#include <fstream>

namespace database{
	class Database
	{
	public:

		Database();
		Database(std::string filename);
		~Database();
		
		bool openDatabase(std::fstream &stream);
		bool closeDatabase(std::fstream& stream);
		void setFileName(std::string filename);

	private:
		std::string filename;
		
	};
}