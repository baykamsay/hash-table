/**
 * Author : Baykam Say
 * ID: 21802030
 * Section : 3
 * Assignment : 4
 */

using namespace std;
#include <iostream>
#include "HashTable.h"

int main() {
	
	HashTable t(11, LINEAR);
	t.insert(20);
	t.insert(30);
	t.insert(2);
	t.insert(10);
	t.insert(13);
	t.insert(25);
	t.insert(9);
	t.insert(24);
	t.display();

	double succ;
	double unsucc;
	t.analyze(succ, unsucc);
	cout << succ << " " << unsucc << endl;

	return 0;
}