#include <cstdlib>
#include <stdexcept>

class Matrix {
private:
	int *data;
	size_t rows, cols;

public:
	Matrix(size_t Rows, size_t Cols);
	~Matrix();

	class Row {
	private:
		int *data;
		size_t size;

	public:
		Row(size_t Size, int *Data);
		int& operator[](size_t column);
	};

	size_t getRows();
	size_t getColumns();

	void fill(int n);
	int at(int row, int column) const;

	Row operator[](size_t row);
	Matrix& operator*=(int n);
	bool operator==(const Matrix& n);
	bool operator!=(const Matrix& n);
};