#include "long_num.hpp"

using bav::LongNumber;
		
LongNumber::LongNumber() {
	length = 0;
    sign = 1;
    numbers = new int[1];
    numbers[0] = 0;
}

LongNumber::LongNumber(int length, int sign) {
	this->length = length;
    this->sign = sign;
    numbers = new int[length];
    for (int i = 0; i < length; i++) {
        numbers[i] = 0;
    }
}

LongNumber::LongNumber(const char* const str) {
	sign = 1;
    int start = 0;

    if (str[0] == '-') {
        sign = -1;
        start++;
    }

    length = get_length(str) - start;
    numbers = new int[length];

    for (int i = 0; i < length; i++) {
        numbers[i] = str[start + i] - '0';
    }
}

LongNumber::LongNumber(const LongNumber& x) {
	length = x.length;
    sign = x.sign;
    numbers = new int[length];

    for (int i = 0; i < length; i++) {
        numbers[i] = x.numbers[i];
    }
}

LongNumber::LongNumber(LongNumber&& x) {
	length = x.length;
    sign = x.sign;
    numbers = x.numbers;

    x.length = 0;
    x.numbers = nullptr;
}

LongNumber::~LongNumber() {
	delete[] numbers;
}

LongNumber& LongNumber::operator = (const char* const str) {
	*this = LongNumber(str);
    return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
	if (this == &x) {
        return *this;
    }

    delete[] numbers;

    length = x.length;
    sign = x.sign;
    numbers = new int[length];

    for (int i = 0; i < length; i++) {
        numbers[i] = x.numbers[i];
    }

    return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
	if (this == &x) {
        return *this;
    }

    delete[] numbers;

    length = x.length;
    sign = x.sign;
    numbers = x.numbers;

    x.length = 0;
    x.numbers = nullptr;

    return *this;
}

bool LongNumber::operator == (const LongNumber& x) const {
	if (length != x.length || sign != x.sign) {
        return false;
    }

    for (int i = 0; i < length; i++) {
        if (numbers[i] != x.numbers[i]) {
            return false;
        }
    }

    return true;
}

bool LongNumber::operator != (const LongNumber& x) const {
	return !(*this == x);
}

bool LongNumber::operator > (const LongNumber& x) const {
	if (sign != x.sign) {
        return sign > x.sign;
    }

    if (length != x.length) {
        return sign * length > sign * x.length;
    }

    for (int i = 0; i < length; i++) {
        if (numbers[i] != x.numbers[i]) {
            return sign * numbers[i] > sign * x.numbers[i];
        }
    }

    return false;
}

bool LongNumber::operator < (const LongNumber& x) const {
	return !(*this > x) && *this != x;
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
	
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
	// TODO
}

LongNumber LongNumber::operator * (const LongNumber& x) const {
	// TODO
}

LongNumber LongNumber::operator / (const LongNumber& x) const {
	// TODO
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
	// TODO
}

bool LongNumber::is_negative() const noexcept {
	// TODO
}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const noexcept {
	// TODO
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace bav {
	std::ostream& operator << (std::ostream &os, const LongNumber& x) {
		// TODO
	}
}