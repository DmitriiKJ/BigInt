#pragma once

#include <vector>
#include <string>
#include <cmath>

bool isHex(std::string str);

int hexSymbolToInt(char ch);

class BigInt
{
private:
	std::vector<unsigned long> blocks;

public:

	BigInt(std::string num = "0");

	std::string toHexString();

	BigInt operator+(const BigInt& second);
	BigInt operator-(const BigInt& second);
	BigInt operator*(const BigInt& second);
	BigInt operator/(const BigInt& second);

	~BigInt();
};

