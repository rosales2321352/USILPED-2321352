#include <iostream>
#include <fstream>
#include <string>
#include "Database.h"
#include "File.h"


database::Database::Database()
{
}

database::Database::Database(std::string filename)
{
	this->filename = filename;
}

database::Database::~Database()
{
}

void database::Database::setFileName(std::string filename)
{
	this->filename = filename;
}

bool database::Database::openDatabase(std::fstream& stream)
{
	stream.open(filename, std::fstream::in | std::fstream::out | std::fstream::binary | std::fstream::app);
	return stream.is_open();
}

bool database::Database::closeDatabase(std::fstream& stream)
{
	if (stream.is_open())
	{
		stream.close();
		return true;
	}

	return false;
}


