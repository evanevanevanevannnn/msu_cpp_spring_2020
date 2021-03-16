#include <cstdlib>
#include "bigint.h"

static const int base = 1000 * 1000 * 1000;
static const int log_base = 9;

BigInt::BigInt() {
	data = nullptr;
	sign = 0;
	size = 0;
}

BigInt::BigInt(int val) {
	sign = (val < 0);
	val = std::abs(val);

	data = (int *)malloc(2 * sizeof(int));

	if (!data)
		throw std::bad_alloc();

	data[0] = val % base;
	data[1] = val / base;

	size = 2;

	removeLeadingZeros();
}

BigInt::BigInt(const BigInt& n) {
	sign = n.sign;
	size = n.size;

	data = (int *)malloc(size * sizeof(int));

	if (!data)
		throw std::bad_alloc();

	for (int i = 0; i < size; ++i)
		data[i] = n.data[i];
}

BigInt::BigInt(BigInt&& n) {
	sign = n.sign;
	size = n.size;

	data = n.data;

	n.data = nullptr;
	n.sign = 0;
	n.size = 0;
}

BigInt::~BigInt() {
	free(data);
}

BigInt& BigInt::operator=(const BigInt& n) {
	sign = n.sign;
	size = n.size;

	int *ptr = (int *)malloc(size * sizeof(int));

	if (!ptr)
		throw std::bad_alloc();
	free(data);
	
	data = ptr;
	for (int i = 0; i < size; ++i)
		data[i] = n.data[i];

	return (*this);
}

BigInt& BigInt::operator=(BigInt&& n) {
	sign = n.sign;
	size = n.size;

	free(data);
	data = n.data;

	n.data = nullptr;
	n.sign = 0;
	n.size = 0;
}

BigInt BigInt::operator+(const BigInt& n) const {
	BigInt res;

	if (sign ^ n.sign)
		res = (*this) - -n;
	else {
		res.size = std::max(size, n.size) + 1;
		res.sign = sign;

		res.data = (int *)malloc(res.size * sizeof(int));

		if (!res.data)
			throw std::bad_alloc();

		int carry = 0;
		for (int i = 0; i < res.size; ++i) {
			int curr = (i < size ? data[i] : 0) + (i < n.size ? n.data[i] : 0) + carry;
			res.data[i] = curr % base;
			carry = curr / base;
		}

		res.removeLeadingZeros();
	}

	return res;
}

BigInt BigInt::operator-(const BigInt& n) const {
	BigInt res;

	if (sign ^ n.sign)
		res = (*this) + -n;
	else {
		res.sign = sign;

		const BigInt *l = this, *r = &n;
		if (*l < *r) {
			res.sign ^= 1;

			const BigInt *t = l;
			l = r;
			r = t;
		}

		res.size = l->size;
		res.data = (int *)malloc(res.size * sizeof(int));

		if (!res.data)
			throw std::bad_alloc();

		int carry = 0;
		for (int i = l->size; i >= 0; --i) {
			res.data[i] = l->data[i] - (carry + r->data[i]);

			carry = res.data[i] < 0;

			if (carry)
				res.data[i] += base;
		}

		res.removeLeadingZeros();
	}

	return res;
}

BigInt BigInt::operator-() const {
	BigInt res(*this);
	res.sign ^= 1;
	return res;
}

bool BigInt::operator==(const BigInt& n) const {
	if (sign ^ n.sign && !(isZero() && n.isZero()))
		return 0;
	if (size != n.size)
		return 0;
	for (int i = 0; i < size; ++i)
		if (data[i] != n.data[i])
			return 0;

	return 1;
}

bool BigInt::operator!=(const BigInt& n) const {
	return !(*this == n);
}

bool BigInt::operator>(const BigInt& n) const {
	if (sign ^ n.sign)
		return sign == 0;
	else {
		if (size != n.size)
			return (size > n.size) ^ sign; 

		for (int i = size; i >= 0; --i)
			if (data[i] != n.data[i])
				return (data[i] > n.data[i]) ^ sign;

		return 0;
	}
}

bool BigInt::operator<(const BigInt& n) const {
	return -(*this) > -n;
}

bool BigInt::operator>=(const BigInt& n) const {
	return !(*this < n);
}

bool BigInt::operator<=(const BigInt& n) const {
	return !(*this > n);
}

std::ostream& operator<<(std::ostream& out, const BigInt& n) {
	if (n.sign && !n.isZero())
		out << '-';

	out << n.data[n.size - 1];

	for (int i = n.size - 2; i >= 0; --i)
		out << std::setw(log_base) << std::setfill('0') << n.data[i];

	return out;
}

std::istream& operator>>(std::istream& in, BigInt& n) {
	std::string s;
	in >> s;

	if (s[0] == '-') {
		n.sign = 1;
		s = s.substr(0, s.size() - 1);
	}
	else
		n.sign = 0;

	n.size = (s.size() + 8) / 9;
	int *new_data = (int *)malloc(n.size * sizeof(int));

	if (!new_data)
		throw std::bad_alloc();
	
	free(n.data);
	n.data = new_data;

	for (int i = 0; i < n.size; ++i) {
		int start = std::max((size_t)0, s.size() - (i + 1) * 9 - 1),
			len = s.size() - i * 9 - start;
		n.data[i] = std::stoi(s.substr(start, len));
	}

	return in;
}

void BigInt::removeLeadingZeros() {
	while (data[size - 1] == 0 && size > 1)
		--size;

	data = (int *)realloc(data, size * sizeof(int));
}

bool BigInt::isZero() const {
	return size == 1 && data[0] == 0;
}
