#include <cstdlib>
#include <stdexcept>

class Matrix {
private:
	int *data;
	size_t rows, cols;

public:
	Matrix(size_t Rows, size_t Cols);

	class Row {
	private:
		int *data;
		size_t size;

	public:
		Row(size_t Size, int *Data);
		int& operator[](const size_t& n);
	};

	int getRows();
	int getColumns();

	void fill(const int& n);

	Row operator[](const size_t& n);
	Matrix operator*=(const int& n);
	bool operator==(Matrix n);
	bool operator!=(Matrix n);
};