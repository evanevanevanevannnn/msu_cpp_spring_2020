#include "matrix.h"

Matrix::Matrix(size_t Rows, size_t Cols):
		rows(Rows), cols(Cols) {
	data = (int *)malloc(rows * cols * sizeof(int));

	if (data == nullptr)
		throw std::bad_alloc();
}

Matrix::Row::Row(size_t Size, int *Data):
		size(Size), data(Data) {}

int& Matrix::Row::operator[](const size_t& n) {
	if (n >= size)
		throw std::out_of_range("std::out_of_range");

	return data[n];
}

int Matrix::getRows() {
	return rows;
}

int Matrix::getColumns() {
	return cols;
}

void Matrix::fill(const int& n) {
	for (int i = 0, size = rows * cols; i < size; ++i)
		data[i] = n;
}

Matrix::Row Matrix::operator[](const size_t& n) {
	if (n >= rows)
		throw std::out_of_range("std::out_of_range");

	return Matrix::Row(cols, data + n * cols);
}

Matrix Matrix::operator*=(const int& n) {
	for (int i = 0, size = rows * cols; i < size; ++i)
		data[i] *= n;

	return *this;
}

bool Matrix::operator==(Matrix n) {
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			if (data[i * cols + j] != n[i][j])
				return false;
	return true;
}

bool Matrix::operator!=(Matrix n) {
	return !(*this == n);
}