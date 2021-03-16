#include <iostream>
#include <iomanip>
#include <string>

class BigInt {
public:
	int *data, sign;
	size_t size;

	bool isZero() const;
	void removeLeadingZeros();
public:

    BigInt();
    BigInt(int val);
    BigInt(const BigInt& n);
    BigInt(BigInt&& n);
    ~BigInt();

    BigInt& operator=(const BigInt& n);
    BigInt& operator=(BigInt&& n);
    BigInt operator+(const BigInt& n) const;
    BigInt operator-(const BigInt& n) const;
    BigInt operator-() const;

    bool operator==(const BigInt& n) const;
    bool operator!=(const BigInt& n) const;
    bool operator>(const BigInt& n) const;
    bool operator<(const BigInt& n) const;
    bool operator>=(const BigInt& n) const;
    bool operator<=(const BigInt& n) const;

    friend std::ostream& operator<< (std::ostream &out, const BigInt& n);
    friend std::istream& operator>>(std::istream &in, BigInt& n);
};