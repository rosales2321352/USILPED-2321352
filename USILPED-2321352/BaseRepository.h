#pragma once
#include <iostream>
#include <fstream>
#include <optional>
#include "Database.h"
#include "HashTable.h"
#include "Structure.h"

template<typename T>
class BaseRepository {
private:
	string filename;
protected:
	hash_table::HashTable<int, T> hashTable;
	void loadEntities(string _filename);
	void loadEntities();
	bool saveEntity(T& entity);
	bool deleteEntity(T& entity);
	bool updateEntity(T& original, T& _new);
public:

	BaseRepository(string _filename) : filename(_filename) {
		loadEntities();
	}
	~BaseRepository() {}
};

template<typename T>
void BaseRepository<T>::loadEntities(string _filename)
{
	this->filename = _filename;
	loadEntities();
}
template<typename T>
void BaseRepository<T>::loadEntities()
{
	bool result = false;
	std::fstream stream;
	database::Database db = database::Database(filename);
	result = db.openDatabase(stream);
	while (!stream.eof()) {
		T readEntity = T(stream);
		if (readEntity.id != -1 && !readEntity.isDeleted) {
			hashTable.insert(readEntity.id, readEntity);
		}
	}
	result = db.closeDatabase(stream);
}
template<typename T>
bool BaseRepository<T>::deleteEntity(T& entity)
{
	bool result = false;
	if (entity.id != -1 && entity.pointerOfFile != -1) {
		std::fstream stream;
		database::Database db = database::Database(filename);
		result = db.openDatabase(stream);
		if (hashTable.contains(entity.id)) {
			stream.seekp(entity.pointerOfFile);
			entity.isDeleted = true;
			entity.write(stream);
			hashTable.remove(entity.id);
		}
		result = db.closeDatabase(stream);
	}
	return result;
}
template<typename T>
bool BaseRepository<T>::updateEntity(T& original, T& _new)
{
	bool result = false;
	if (_new.id != -1 && _new.pointerOfFile != -1) {
		std::fstream stream;
		database::Database db = database::Database(filename);
		result = db.openDatabase(stream);
		if (hashTable.contains(_new.id)) {
			original.isDeleted = true;
			original.write(stream, original.pointerOfFile);
			_new.pointerOfFile = stream.tellp();
			_new.write(stream);
			hashTable.insert(_new.id, _new);
		}
		result = db.closeDatabase(stream);
	}
	return result;
}
template<typename T>
bool BaseRepository<T>::saveEntity(T& entity)
{
	bool result = false;
	if (entity.id != -1 && entity.pointerOfFile != -1) {
		std::fstream stream;
		database::Database db = database::Database(filename);
		result = db.openDatabase(stream);
		if (!hashTable.contains(entity.id)) {
			entity.write(stream);
			hashTable.insert(entity.id, entity);
		}
		result = db.closeDatabase(stream);
	}
	return result;
}
