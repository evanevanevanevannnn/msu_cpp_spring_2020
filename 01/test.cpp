#include <iostream>

#include "allocator.h"

using namespace std;

int main() {
	cout << "\n__________test__________\n";

	MakeAllocator(20);

	char *first = alloc(10),
		 *second = alloc(10),
		 *third = alloc(1);

	if (!isAllocated()) { //failed malloc check
		if (first != nullptr ||
			second != nullptr ||
			third != nullptr) {
			cout << "test failed\n";
			return 0;
		}
		else 
			cout << "test 1 success\n";
	}
	else
		cout << "test 1 success\n";
	
	if (first == nullptr || //not failed malloc check
		second == nullptr ||
		third != nullptr) {
		cout << "test failed\n";
		return 0;
	}
	else
		cout << "test 2 success\n";

	if (second - first != 10) { //correct offset check
		cout << "test failed\n";
		return 0;
	}
	else
		cout << "test 3 success\n";

	reset();

	char *fourth = alloc(1),
		 *fifth = alloc(20),
		 *sixth  = alloc(19);

	if (fourth == nullptr || fourth != first) { //reset checker
		cout << "test failed\n";
		return 0;
	}
	else
		cout << "test 4 success\n";

	if (fifth != nullptr || //+-1 offset checker
		sixth == nullptr) {
		cout << "test failed\n";
		return 0;
	}
	else
		cout << "test 5 success\n";

	MakeAllocator(1500000000); //should fail unless you have 1.5TB of RAM

	first = alloc(100);
	second = alloc(1);
	third = alloc(10000);

	if (!isAllocated()) {
		if (first != nullptr ||
			second != nullptr ||
			third != nullptr) {
				cout << "test failed\n";
				return 0;
		}
		else
			cout << "success\n";
	}

	cout << "tests passed\n\n";
	return 0;
}