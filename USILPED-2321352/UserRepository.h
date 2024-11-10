#pragma once

#include <iostream>
#include <fstream>
#include <optional>
#include "Database.h"
#include "HashTable.h"
#include "Structure.h"

using namespace structure;

namespace user_repository
{
	class UserRepository
	{
	private:
		string filename;
		hash_table::HashTable<int, structure::User> hashTable;
	public:
		
		UserRepository() {}
		UserRepository(string _filename) : filename(_filename) {
			loadUsers();
		}
		~UserRepository() {}


		void loadUsers(string _filename);
		void loadUsers();
		optional<User> getUser(int id);
		bool saveUser(structure::User& user);
		bool deleteUser(structure::User& user);
		bool updateUser(structure::User& originalUser,  structure::User& user);
		void print();
	};

	void UserRepository::loadUsers(string _filename)
	{
		this->filename = _filename;
		loadUsers();
	}
	void UserRepository::loadUsers()
	{
		bool result = false;
		std::fstream stream;
		database::Database db = database::Database(filename);
		result = db.openDatabase(stream);
		while (!stream.eof()) {
			structure::User readUser = structure::User(stream);
			if (readUser.id != -1 && !readUser.isDeleted) {
				hashTable.insert(readUser.id, readUser);
			}
		}
		result = db.closeDatabase(stream);
	}
	bool UserRepository::deleteUser(structure::User& user)
	{
		bool result = false;
		if (user.id != -1 && user.pointerOfFile != -1) {
			std::fstream stream;
			database::Database db = database::Database(filename);
			result = db.openDatabase(stream);
			if (hashTable.contains(user.id)) {
				stream.seekp(user.pointerOfFile);
				user.isDeleted = true;
				user.write(stream);
				hashTable.remove(user.id);
			}
			result = db.closeDatabase(stream);
		}
		return result;
	}
	
	bool UserRepository::updateUser(structure::User& originalUser, structure::User& user) {
		bool result = false;
		if (user.id != -1 && user.pointerOfFile != -1) {
			std::fstream stream;
			database::Database db = database::Database(filename);
			result = db.openDatabase(stream);

			if (hashTable.contains(user.id)) {
				// Colocamos el cursor en la posición del archivo del usuario original
				stream.seekp(originalUser.pointerOfFile);

				// Escribimos el usuario actualizado en la misma posición
				user.write(stream);

				// Actualizamos el puntero de archivo en el hashTable
				hashTable.insert(user.id, user);
				user.pointerOfFile = originalUser.pointerOfFile;
			}

			result = db.closeDatabase(stream);
		}
		return result;
	}

	bool UserRepository::saveUser(structure::User& user)
	{
		bool result = false;
		if (user.id != -1 && user.pointerOfFile != -1) {
			std::fstream stream;
			database::Database db = database::Database(filename);
			result = db.openDatabase(stream);
			if (!hashTable.contains(user.id) ){
				user.write(stream);
				hashTable.insert(user.id, user);
			}
			result = db.closeDatabase(stream);
		}
		return result;
	}
	void UserRepository::print()
	{
		hashTable.print();
	}

	optional<User> UserRepository::getUser(int id)
	{
		return hashTable.get(id);
	}
}