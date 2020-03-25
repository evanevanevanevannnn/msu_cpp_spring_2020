#include <iostream>
#include <cassert>
#include <random>

#include "matrix.h"

using namespace std;

ostream& operator<<(ostream& os, Matrix m) {
	for (int i = 0; i < m.getRows(); ++i) {
		for (int j = 0; j < m.getColumns(); ++j)
			os << m[i][j] << ' ';
		os << '\n';
	}

	return os;
}

int main() {
	const size_t rows = 5;
	const size_t cols = 3;

	Matrix m(rows, cols);

	assert(m.getRows() == 5);
	assert(m.getColumns() == 3);

	m.fill(10);

	assert(m[rand() % 5][rand() % 3] == 10);

	m[1][2] = 5;
	assert(m[1][2] == 5);

	double x = m[4][1];

	m *= 3;
	m[1][2] = 30;
	assert(m[rand() % 5][rand() % 3] == 30);

	Matrix m1(rows, cols);
	m1.fill(30);

	assert(m == m1);

	m[2][1] = 25;
	m1[2][1] = 45;
	cout << "m:\n" << m << "\nm1:\n" << m1 << '\n';

	try {
		Matrix m2(10000000, 10000000);//shouldn't alloc
	} catch(const bad_alloc& e) {
		cout << e.what() << "\ncaught bad alloc exception\n\n";
	}

	try {
		int y = m[10][10];
	} catch(const out_of_range& e) {
		cout << e.what() << "\ncaught out of range exception\n\n";
	}

	cout << "tests passed\n";
	return 0;
}