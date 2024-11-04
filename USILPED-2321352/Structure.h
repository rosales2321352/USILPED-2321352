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
		void write(std::fstream& stream) {
			file::write<int>(id, stream);
			file::write<string>(name, stream);
			file::write<string>(email, stream);
			file::write<string>(phoneNumber, stream);
			file::write<string>(address, stream);
			file::write<bool>(isAdmin, stream);
			file::write<bool>(isDeleted, stream);
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
		Book() : Base(), publicationYear(-1),disponibility(false){}
		Book(int id, const string& title, const string& author, const string& gender, int publicationYear, bool disponibility) :
			Base(id), title(title), author(author), gender(gender), publicationYear(publicationYear), disponibility(disponibility) {}

		friend istream& operator>>(istream& is, Book& book)
		{
			is >> book.id;
			is >> book.author;
			is >> book.gender;
			is >> book.publicationYear;
			is >> book.disponibility;
			return is;
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
		Booking(int idUser, int idBook, const string& bookingDate, const string& returnDate, bool returned) :
			Base(id), idUser(idUser), idBook(idBook), bookingDate(bookingDate), returnDate(returnDate), returned(returned) {};
		friend istream& operator>>(istream& is, Booking& booking)
		{
			is >> booking.id;
			is >> booking.idUser;
			is >> booking.idBook;
			is >> booking.bookingDate;
			is >> booking.returnDate;
			is >> booking.returned;
			return is;
		}
	};

	
}