/**
 * Author : Baykam Say
 * ID: 21802030
 * Section : 3
 * Assignment : 4
 */

using namespace std;
#include <iostream>
#include <iomanip>
#include <fstream>
#include "HashTable.h"

const string FILE_NAME = "input.txt";
const int TABLE_SIZE = 997;
const CollisionStrategy COLLISION_STRATEGY = DOUBLE;

int main() {
	fstream input(FILE_NAME);
	HashTable t(TABLE_SIZE, COLLISION_STRATEGY);
	
	cout << "Collision Strategy: " << COLLISION_STRATEGY << endl;

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

	t.display();

	double numSuccProbes;
	double numUnsuccProbes;
	
	t.analyze(numSuccProbes, numUnsuccProbes);

	cout << fixed << setprecision(4);
	cout << "Average number of probes for successful search: " 
		<< numSuccProbes << endl;
	cout << "Average number of probes for unsuccessful search: "
		<< numUnsuccProbes << endl;

	//fstream file("input.txt");
	//for (int i = 0; i < 700; i++) {
	//	file << "I " << rand() % 10000 << endl;
	//}
	return 0;
}