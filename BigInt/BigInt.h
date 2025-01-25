#pragma once

#include <vector>
#include <string>
#include <cmath>

const int LongSize = sizeof(long) * 8;

bool isHex(std::string str);
int hexSymbolToInt(char ch);
char byteToHexSymbol(unsigned char byte);

class BigInt
{
private:
	std::vector<unsigned long> blocks;

	std::string toHexStringFromData(std::vector<unsigned long> blocks);

public:

	BigInt(std::string num = "0");

	std::string toHexString();

	// Compare operators
	bool operator<(const BigInt& second) const;
	bool operator<=(const BigInt& second) const;
	bool operator>(const BigInt& second) const;
	bool operator>=(const BigInt& second) const;
	bool operator==(const BigInt& second) const;
	bool operator!=(const BigInt& second) const;

	// Math operators
	BigInt operator+(const BigInt& second) const;
	BigInt operator-(const BigInt& second) const;
	BigInt operator*(const BigInt& second) const;
	BigInt operator/(const BigInt& second) const;

	// Shift
	BigInt operator<<(int n) const;
	BigInt operator>>(int n) const;

	BigInt& operator=(const BigInt second);

	// Other
	bool isZero() const;
};

