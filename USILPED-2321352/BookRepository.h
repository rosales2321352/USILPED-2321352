#pragma once

#include <iostream>
#include <fstream>
#include <optional>
#include "BaseRepository.h"
#include "Database.h"
#include "HashTable.h"
#include "Structure.h"

using namespace structure;

namespace book_repository
{
	class BookRepository : public BaseRepository<structure::Book>
	{
	public:

		BookRepository(string _filename) :BaseRepository<Book>(_filename) {
			loadEntities();
		}
		optional<Book> getBook(int id);
		bool saveBook(structure::Book& book);
		bool deleteBook(structure::Book& book);
		bool updateBook(structure::Book& originalBook, structure::Book& book);
	};

	bool BookRepository::deleteBook(structure::Book& book)
	{
		return deleteEntity(book);
	}

	bool BookRepository::updateBook(structure::Book& originalBook, structure::Book& book)
	{
		return updateEntity(originalBook, book);
	}

	bool BookRepository::saveBook(structure::Book& book)
	{
		return saveEntity(book);
	}

	optional<Book> BookRepository::getBook(int id)
	{
		return hashTable.get(id);
	}
}