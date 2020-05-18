/**
 * Author : Baykam Say
 * ID: 21802030
 * Section : 3
 * Assignment : 4
 */

using namespace std;
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "HashTable.h"

// create a hash table with given collision strategy and do the operations
// in the given file
void hashTableTest(int tableSize, string fileName, CollisionStrategy cs) {
	fstream input(fileName);
	HashTable t(tableSize, cs);
	cout << "--------------------------------------------------------------" << endl;
	cout << "Collision Strategy: ";
	switch (cs)
	{
	case LINEAR:
		cout << "Linear Probing";
		break;
	case QUADRATIC:
		cout << "Quadratic Probing";
		break;
	case DOUBLE:
		cout << "Double Hashing";
		break;
	default:
		break;
	}
	cout << endl;
	cout << endl;
	
	char operation;
	int number;

	while (input.good()) {
		input >> operation;
		input >> number;

		switch (operation)
		{
		case 'I':
			if (t.insert(number))
				cout << number << " inserted" << endl;
			else
				cout << number << " not inserted" << endl;
			break;
		case 'R':
			if (t.remove(number))
				cout << number << " removed" << endl;
			else
				cout << number << " not removed" << endl;
			break;
		case 'S':
			int probes;
			if (t.search(number, probes))
				cout << number << " found after " << probes << " probes" << endl;
			else
				cout << number << " not found after " << probes << " probes" << endl;
			break;
		default:
			cout << "Error: Operation " << operation << " is undefined!" << endl;
			break;
		}
	}
	cout << endl;
	t.display();
	cout << endl;
	double numSuccProbes;
	double numUnsuccProbes;

	t.analyze(numSuccProbes, numUnsuccProbes);

	cout << fixed << setprecision(4);
	cout << "Average number of probes for successful search: "
		<< numSuccProbes << endl;
	cout << "Average number of probes for unsuccessful search: "
		<< numUnsuccProbes << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << endl;
}

void generateFile(string fileName) {
	fstream file(fileName);

	for (int i = 0; i < 6; i++) {
		file << "I " << rand() % 100 << endl;
	}
}

// argv[1] -> the size of the hash table
// argv[2] -> the name of the input file
int main(int argc, char* argv[]) {
	int tableSize = stoi(argv[1]);
	string fileName = argv[2];

	//generateFile(fileName);
	
	cout << "Table size used: " << tableSize << endl;
	hashTableTest(tableSize, fileName, LINEAR);
	hashTableTest(tableSize, fileName, QUADRATIC);
	hashTableTest(tableSize, fileName, DOUBLE);

	return 0;
}