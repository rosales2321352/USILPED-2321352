#pragma once

#include <iostream>
#include <fstream>
#include <optional>
#include "BaseRepository.h"
#include "Database.h"
#include "HashTable.h"
#include "Structure.h"

using namespace structure;

namespace booking_repository
{
	class BookingRepository : public BaseRepository<structure::Booking>
	{
	public:

		BookingRepository(string _filename) :BaseRepository<Booking>(_filename) {
			loadEntities();
		}
		optional<Booking> getBook(int id);
		bool saveBooking(structure::Booking& booking);
		bool deleteBooking(structure::Booking& booking);
		bool updateBooking(structure::Booking& originalBooking, structure::Booking& booking);
	};

	bool BookingRepository::deleteBooking(structure::Booking& booking)
	{
		return deleteEntity(booking);
	}

	bool BookingRepository::updateBooking(structure::Booking& originalBooking, structure::Booking& booking)
	{
		return updateEntity(originalBooking, booking);
	}

	bool BookingRepository::saveBooking(structure::Booking& booking)
	{
		return saveEntity(booking);
	}

	optional<Booking> BookingRepository::getBook(int id)
	{
		return hashTable.get(id);
	}
}