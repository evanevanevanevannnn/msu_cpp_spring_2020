#include "matrix.h"

Matrix::Matrix(size_t Rows, size_t Cols):
		rows(Rows), cols(Cols) {
	data = (int *)malloc(rows * cols * sizeof(int));

	if (data == nullptr)
		throw std::bad_alloc();
}

Matrix::Row::Row(size_t Size, int *Data):
		size(Size), data(Data) {}

int& Matrix::Row::operator[](size_t column) {
	if (column >= size)
		throw std::out_of_range("std::out_of_range");

	return data[column];
}

size_t Matrix::getRows() {
	return rows;
}

size_t Matrix::getColumns() {
	return cols;
}

void Matrix::fill(int n) {
	for (size_t i = 0, size = rows * cols; i < size; ++i)
		data[i] = n;
}

int Matrix::at(size_t row, size_t column) const {
	return this->data[row * cols + column];
}

Matrix::Row Matrix::operator[](size_t row) {
	if (row >= rows)
		throw std::out_of_range("std::out_of_range");

	return Matrix::Row(cols, data + row * cols);
}

Matrix& Matrix::operator*=(int n) {
	for (size_t i = 0, size = rows * cols; i < size; ++i)
		data[i] *= n;

	return *this;
}

bool Matrix::operator==(const Matrix& n) {
	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < cols; ++j)
			if (data[i * cols + j] != n.at(i, j))
				return false;
	return true;
}

bool Matrix::operator!=(const Matrix& n) {
	return !(*this == n);
}

Matrix::~Matrix() {
	free(data);
}