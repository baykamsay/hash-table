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

int HashTable::findEmptyLocation(int key) {
	int firstLoc = h_i(key, 0);
	if (table[firstLoc].status == OCCUPIED && table[firstLoc].data == key)
		return -1;
	if (table[firstLoc].status != OCCUPIED)
		return firstLoc;

	for (int i = 1; true; i++) {
		int loc = h_i(key, i);
		if (loc == firstLoc || (table[loc].status == OCCUPIED && table[loc].data == key))
			return -1;

		if (table[loc].status != OCCUPIED) {
			return loc;
		}
	}
}

bool HashTable::insert(const int item) {
	int loc = findEmptyLocation(item);

	if (loc == -1)
		return false;
	
	table[loc].data = item;
	table[loc].status = OCCUPIED;
	return true;
}

bool HashTable::remove(const int item) {
	int firstLoc = h_i(item, 0);
	if (table[firstLoc].status == EMPTY)
		return false;

	if (table[firstLoc].data == item) {
		table[firstLoc].data = 0;
		table[firstLoc].status = DELETED;
		return true;
	}
	
	for (int i = 1; true; i++) {
		int loc = h_i(item, i);
		if (firstLoc == loc || table[loc].status == EMPTY)
			return false;
		if (table[loc].data == item) {
			table[loc].data = 0;
			table[loc].status = DELETED;
			return true;
		}
	}
}

bool HashTable::search(const int item, int& numProbes) {
	numProbes = 1;
	int firstLoc = h_i(item, 0);

	if (table[firstLoc].status == EMPTY)
		return false;
	if (table[firstLoc].data == item)
		return true;

	for (int i = 1; true; i++) {
		numProbes++;
		int loc = h_i(item, i);
		if (firstLoc == loc || table[loc].status == EMPTY)
			return false;
		if (table[loc].data == item)
			return true;
	}
}

void HashTable::display() {
	for (int i = 0; i < size; i++) {
		cout << i << ": ";
		if (table[i].status == OCCUPIED)
			cout << table[i].data;
		cout << endl;
	}
}

void HashTable::analyze(double& numSuccProbes, double& numUnsuccProbes) {
	int totSuccProbes = 0;
	int probes = 0;
	int occupiedPlaces = 0;

	for (int i = 0; i < size; i++) {
		if (table[i].status == OCCUPIED) {
			search(table[i].data, probes);
			occupiedPlaces++;
			totSuccProbes += probes;
		}
	}
	numSuccProbes = (double) totSuccProbes / occupiedPlaces;
	// add exception for double hashing
	int totUnsuccProbes = 0;

	for (int i = 0; i < size; i++) {
		int j = i;
		while (search(j, probes))
			j += size;
		totUnsuccProbes += probes;
	}
	numUnsuccProbes = (double) totUnsuccProbes / size;
}