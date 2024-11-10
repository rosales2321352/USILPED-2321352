#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "File.h"

using namespace std;

namespace structure
{
	class Base {
	public:
		long pointerOfFile;
		bool isDeleted;
		int id;
		Base() :id(-1), isDeleted(false), pointerOfFile(pointerOfFile){};
		Base(int id) : id(id), isDeleted(false), pointerOfFile(pointerOfFile){};
		~Base() {}
		bool operator==(const Base& other) const {
			return id == other.id;
		}
	};

	

	class User : public Base {
	public:
		string name;
		string email;
		string phoneNumber;
		string address;
		bool isAdmin;
		User() : Base(), isAdmin(false) {}
		User(std::fstream& stream) { read(stream); }
		User(int id, const std::string& name, const std::string& email,
			const std::string& phoneNumber, const std::string& address, bool isAdmin)
			: Base(id), name(name), email(email), phoneNumber(phoneNumber), address(address), isAdmin(isAdmin) {}

		// Método para escribir el usuario en un archivo
		void write(std::fstream& stream,streampos position = NULL) {
			if(position == NULL)
				stream.seekp(position, std::ios::beg);
			file::write<int>(id, stream);
			file::write<string>(name, stream);
			file::write<string>(email, stream);
			file::write<string>(phoneNumber, stream);
			file::write<string>(address, stream);
			file::write<bool>(isAdmin, stream);
			file::write<bool>(isDeleted, stream);
			stream.seekp(0, std::ios::end);
		}
				
		// Método para leer el usuario desde un archivo
		void read(std::fstream& stream) {
			pointerOfFile = stream.tellg();
			file::read<int>(id, stream);
			file::read<string>(name, stream);
			file::read<string>(email, stream);
			file::read<string>(phoneNumber, stream);
			file::read<string>(address, stream);
			file::read<bool>(isAdmin, stream);
			file::read<bool>(isDeleted, stream);
		}

	};

	class Book : public Base
	{
	public:
		string title;
		string author;
		string gender;
		int publicationYear;
		bool disponibility;

		Book() : Base(), publicationYear(-1), disponibility(false) {}
		Book(std::fstream& stream) { read(stream); }
		Book(int id, const string& title, const string& author, const string& gender, int publicationYear, bool disponibility) :
			Base(id), title(title), author(author), gender(gender), publicationYear(publicationYear), disponibility(disponibility) {}

		void write(std::fstream& stream, streampos position = NULL) {
			if (position == NULL)
				stream.seekp(position, std::ios::beg);
			file::write<int>(id, stream);
			file::write<string>(title, stream);
			file::write<string>(author, stream);
			file::write<int>(publicationYear, stream);
			file::write<bool>(disponibility, stream);
			file::write<bool>(isDeleted, stream);
			stream.seekp(0, std::ios::end);
		}

		void read(std::fstream& stream) {
			pointerOfFile = stream.tellg();
			file::read<int>(id, stream);
			file::read<string>(title, stream);
			file::read<string>(author, stream);
			file::read<int>(publicationYear, stream);
			file::read<bool>(disponibility, stream);
			file::read<bool>(isDeleted, stream);
		}
	};

	class Booking : public Base
	{
	public:
		int idUser;
		int idBook;
		string bookingDate;
		string returnDate;
		bool returned;
		Booking() : Base(), idUser(-1), idBook(-1), returned(false) {}
		Booking(std::fstream& stream) { read(stream); }
		Booking(int id,int idUser, int idBook, const string& bookingDate, const string& returnDate, bool returned) :
			Base(id), idUser(idUser), idBook(idBook), bookingDate(bookingDate), returnDate(returnDate), returned(returned) {};

		void write(std::fstream& stream, streampos position = NULL) {
			if (position == NULL)
				stream.seekp(position, std::ios::beg);
			file::write<int>(id, stream);
			file::write<int>(idUser, stream);
			file::write<int>(idBook, stream);
			file::write<string>(bookingDate, stream);
			file::write<string>(returnDate, stream);
			file::write<bool>(returned, stream);
			file::write<bool>(isDeleted, stream);
			stream.seekp(0, std::ios::end);
		}

		// Método para leer el usuario desde un archivo
		void read(std::fstream& stream) {
			pointerOfFile = stream.tellg();
			file::read<int>(id, stream);
			file::read<int>(idUser, stream);
			file::read<int>(idBook, stream);
			file::read<string>(bookingDate, stream);
			file::read<string>(returnDate, stream);
			file::read<bool>(returned, stream);
			file::read<bool>(isDeleted, stream);
		}

	};

	
}