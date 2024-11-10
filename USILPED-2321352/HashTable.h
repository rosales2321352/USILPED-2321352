#pragma once

#include <iostream>
#include <vector>
#include <optional>

using namespace std;

namespace hash_table{
	template<typename keyT, typename valueT>
	class HashTable {
	public:
		HashTable(size_t initialSize = 8);
		~HashTable();
		void insert(const keyT& key, const valueT& value);
		optional<valueT> get(const keyT& key);
		bool remove(const keyT& key);
		bool contains(const keyT& key);
		void print(string val);

	private:
		vector<optional<pair<keyT, valueT>>> table;
		size_t numElements;
		double loadFactor();
		size_t hashFunction(const keyT& key);
		void reHash(size_t newSize);
	};


	

#pragma region Private Methods
	template<typename keyT, typename valueT>
	double HashTable<keyT, valueT>::loadFactor()
	{
		return static_cast<double>(this->numElements) / table.size();
	}

	template<typename keyT, typename valueT>
	size_t HashTable<keyT, valueT>::hashFunction(const  keyT& key)
	{
		return hash<keyT>{}(key)%table.size();
	}

	template<typename keyT, typename valueT>
	void HashTable<keyT, valueT>::reHash(size_t newSize)
	{
		auto oldTable = this->table;
		table.clear();
		table.resize(newSize);
		numElements = 0;

		for (const auto& item : oldTable)
		{
			if (item.has_value())
			{
				insert(item->first, item->second);
			}
		}
	}
#pragma endregion
#pragma region Public Methods
	template<typename keyT, typename valueT>
	HashTable<keyT, valueT>::HashTable(size_t initialSize): table(initialSize),numElements(0)
	{}

	template<typename keyT, typename valueT>
	HashTable<keyT, valueT>::~HashTable()
	{
	}
	template<typename keyT, typename valueT>
	void HashTable<keyT, valueT>::insert(const keyT& key, const valueT& value)
	{
		if (loadFactor() > 0.7)
			reHash(this->table.size() * 2);


		size_t hashIndex = hashFunction(key);
		size_t originalIndex = hashIndex;
		size_t i = 1;

		while (table[hashIndex].has_value())
		{
			if (table[hashIndex]->first == key)
			{
				table[hashIndex]->second = value;
				return;
			}

			hashIndex = (originalIndex + i * i) % this->table.size();
			i++;
		}

		table[hashIndex] = make_pair(key, value);
		numElements++;
	}

	template<typename keyT, typename valueT>
	optional<valueT> HashTable<keyT, valueT>::get(const keyT& key) 
	{
		size_t hashIndex = hashFunction(key);
		size_t originalIndex = hashIndex;
		size_t i = 1;

		while (table[hashIndex].has_value())
		{
			if (table[hashIndex]->first == key)
			{
				return table[hashIndex]->second;
			}
			hashIndex = (originalIndex + i * i) % this->table.size();
			i++;
		}

		return nullopt;
	}

	template<typename keyT, typename valueT>
	bool HashTable<keyT, valueT>::remove(const keyT& key)
	{

		size_t hashIndex = hashFunction(key);
		size_t originalIndex = hashIndex;
		size_t i = 1;

		while (table[hashIndex].has_value()) {
			if (table[hashIndex]->first == key) {
				table[hashIndex].reset(); 
				numElements--;
				return true;
			}
			hashIndex = (originalIndex + i * i) % table.size();
			i++;
		}
		return false;
	}

	
	template<typename keyT, typename valueT>
	bool HashTable<keyT, valueT>::contains(const keyT& key){
		return get(key).has_value();
	}

	


#pragma endregion

}