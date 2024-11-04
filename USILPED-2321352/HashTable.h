#pragma once

#include <iostream>


template <typename T>
class HashItem{
public:
	HashItem();
	~HashItem();
	char* key;
	T* value;

};

template <typename T>
HashItem<T>::HashItem()
{}

template <typename T>
HashItem<T>::~HashItem()
{}



template <typename T>
class HashTable
{
public:
	HashTable();
	~HashTable();
	HashItem** items;
	int size;
	int count;
};

template <typename T>
HashTable<T>::HashTable()
{}

template <typename T>
HashTable<T>::~HashTable()
{}