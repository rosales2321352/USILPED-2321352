#pragma once

#include <iostream>
#include <fstream>
#include <optional>
#include "BaseRepository.h"
#include "Database.h"
#include "HashTable.h"
#include "Structure.h"

using namespace structure;

namespace user_repository
{
	class UserRepository: public BaseRepository<structure::User>
	{
	public:

		UserRepository(string _filename):BaseRepository<User>(_filename) {
			loadEntities();
		}
		optional<User> getUser(int id);
		bool saveUser(structure::User& user);
		bool deleteUser(structure::User& user);
		bool updateUser(structure::User& originalUser, structure::User& user);
	};

	bool UserRepository::deleteUser(structure::User& user)
	{
		return deleteEntity(user);
	}

	bool UserRepository::updateUser(structure::User& originalUser, structure::User& user)
	{
		return updateEntity(originalUser, user);
	}

	bool UserRepository::saveUser(structure::User& user)
	{
		return saveEntity(user);
	}
	
	optional<User> UserRepository::getUser(int id)
	{
		return hashTable.get(id);
	}
}