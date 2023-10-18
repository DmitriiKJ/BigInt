#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class BigNum
{
public:
	unsigned int* num;
	long size;

	BigNum();

	void setHex(string str);
	string getHex()const;

	BigNum operator + (BigNum right);
	BigNum operator - (BigNum right);

	BigNum shiftR(int n);
	BigNum shiftL(int n);
	string MOD();

	void combineBytes(uint8_t* u, size_t sizeByteArray);
	void HexStringToByteArray(string& hexString, size_t& t);
};

BigNum INV(BigNum num1);
BigNum XOR(BigNum num1, BigNum num2);
BigNum OR(BigNum num1, BigNum num2);
BigNum AND(BigNum num1, BigNum num2);

