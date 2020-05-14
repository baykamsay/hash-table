/**
 * Author : Baykam Say
 * ID: 21802030
 * Section : 3
 * Assignment : 4
 */

using namespace std;
#include <iostream>
#include "HashTable.h"

HashTable::HashTable(const int tableSize, const CollisionStrategy option) {
	size = tableSize;
	cs = option;
	table = new Integer[size];
}

HashTable::~HashTable() {
	delete[] table;
	table = NULL;
}

// key mod table size
int HashTable::hash(int key) {
	return key % size;
}

// reverse the key
int HashTable::hash2(int key) {
	int result = 0;
	bool neg = false;

	if (key < 0) {
		key *= -1;
		neg = true;
	}

	while (key > 0) {
		result *= 10;
		result += key % 10;
		key = key / 10;
	}

	if (neg)
		result *= -1;

	return result;
}

// choose between different collision strategies
int HashTable::f(int i, int key) {
	int result;

	switch (cs)
	{
	case LINEAR:
		result = i;
		break;
	case QUADRATIC:
		result = i ^ 2;
		break;
	case DOUBLE:
		result = i * hash2(key);
		break;
	default:
		result = i;
		break;
	}
	return result;
}

int HashTable::h_i(int key, int i) {
	int result = (hash(key) + f(i, key)) % size;
	if (result < 0)
		result *= -1;
	return result;
}

int HashTable::findLocation(int key) {
	int firstLoc = h_i(key, 0);
	if (table[firstLoc].isEmpty)
		return firstLoc;

	for (int i = 1; true; i++) {
		int loc = h_i(key, i);
		if (loc == firstLoc)
			return -1;

		if (table[loc].isEmpty) {
			return loc;
		}
	}
}

bool HashTable::insert(const int item) {
	int loc = findLocation(item);

	if (loc == -1)
		return false;
	
	table[loc].data = item;
	table[loc].isEmpty = false;
	return true;
}

bool HashTable::remove(const int item) {

}