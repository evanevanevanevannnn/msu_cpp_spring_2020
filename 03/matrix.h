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
		const int& operator[](size_t column) const;
	};

	size_t getRows() const;
	size_t getColumns() const;

	void fill(int n);

	Row operator[](size_t row);
	const Row operator[](size_t row) const;

	Matrix& operator*=(int n);
	bool operator==(const Matrix& n) const;
	bool operator!=(const Matrix& n) const;
};