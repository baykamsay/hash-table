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
	table = new int*[size];
	for (int i = 0; i < size; i++) {
		table[i] = NULL;
	}
}

HashTable::~HashTable() {
	for (int i = 0; i < size; i++) {
		delete table[i];
		table[i] = NULL;
	}
	delete[] table;
	table = NULL;
}

int HashTable::hash(int key) {
	return key % size;
}

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