#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace structure
{
	struct User {
		int id;
		string name;
		string email;
		string phoneNumber;
		string address;
		bool isAdmin;
	};

	struct Book
	{
		int id;
		string title;
		string author;
		string gender;
		int publicationYear;
		bool disponibility;
	};

	struct Booking
	{
		int idBooking;
		int idUser;
		int idBook;
		string bookingDate;
		string returnDate;
		bool returned;
	};

	
}