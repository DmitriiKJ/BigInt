#include "BigInt.h"

bool isHex(std::string str)
{
	for (char ch : str) {
		switch (toupper(ch))
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
			break;
		default:
			return false;
		}
	}

	return true;
}

int hexSymbolToInt(const char ch)
{
	// 0 - 9 chars return as num
	if (isdigit(ch)) {
		int digit = atoi(&ch);
		if (digit < 0 || digit > 9) {
			throw "Incorrect symbol";
		}

		return digit;
	}

	// letter to int
	switch (ch)
	{
	case 'a':
		return 10;
	case 'b':
		return 11;
	case 'c':
		return 12;
	case 'd':
		return 13;
	case 'e':
		return 14;
	case 'f':
		return 15;
	default:
		throw "Incorrect symbol";
	}
}

int byteToHexSymbol(unsigned char byte)
{

	if ((int)byte >= 0 && (int)byte <= 9) {
		// 48 - ascii code for 0
		return (char)(byte + 48);
	}

	switch ((int)byte)
	{
	case 10:
		return 'a';
	case 11:
		return 'b';
	case 12:
		return 'c';
	case 13:
		return 'd';
	case 14:
		return 'e';
	case 15:
		return 'f';
	default:
		throw "Incorrect byte";
	}
}

BigInt::BigInt(std::string num)
{
	if (!isHex(num)) {
		throw "Num must be in hex format!";
	}
	int size = ceil((double)num.length() / 8);

	// this blocks will create element of array
	unsigned long block;

	for (int i = num.length() - 1; i >= 0; i -= 8) {
		unsigned long arrBlock = 0;
		for (int j = 0; j < 8; j++)
		{
			if (i - j < 0) {
				block = 0;
			}
			else {
				block = hexSymbolToInt(num[i - j]);
			}

			arrBlock |= (block << 4 * j);
		}
		blocks.push_back(arrBlock);
	}
}

std::string BigInt::toHexString()
{
	std::string res = "";

	for (int i = blocks.size() - 1; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			char symbol = byteToHexSymbol((unsigned char)(blocks[i] << j * 4 >> 28));
			res += symbol;
		}
	}

	return res;
}

BigInt BigInt::operator+(const BigInt& second)
{
	return BigInt();
}

BigInt BigInt::operator-(const BigInt& second)
{
	return BigInt();
}

BigInt BigInt::operator*(const BigInt& second)
{
	return BigInt();
}

BigInt BigInt::operator/(const BigInt& second)
{
	return BigInt();
}

BigInt::~BigInt()
{
}
