/**
 * Author : Baykam Say
 * ID: 21802030
 * Section : 3
 * Assignment : 4
 */

#ifndef __HASHTABLE_H
#define __HASHTABLE_H

enum CollisionStrategy {LINEAR, QUADRATIC, DOUBLE};
struct Integer {
	int data = 0;
	bool isEmpty = true;
};

class HashTable {
public:
	HashTable(const int tableSize, const CollisionStrategy option);
	~HashTable();
	bool insert(const int item);
	bool remove(const int item);
	bool search(const int item, int& numProbes);
	void display();
	void analyze(int& numSuccProbes, int& numUnsuccProbes);
private:
	int hash(int key); // hash function (mod in this case)
	int hash2(int key); // second hash function for double hashing
	int f(int i, int key); // collision resolution strategy
	int h_i(int key, int i); // as seen in hw4 pdf
	int findLocation(int key);

	CollisionStrategy cs;
	int size;
	Integer* table;
};
#endif // !__HASHTABLE_H
