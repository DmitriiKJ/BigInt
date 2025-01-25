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

char byteToHexSymbol(unsigned char byte)
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

// Each of blocks will be dismantled by 4 bits and converted to hex format
std::string BigInt::toHexStringFromData(std::vector<unsigned long> blocks)
{
	std::string res = "";
	// We don't need print 0 at the start
	bool isStart = true;

	for (int i = blocks.size() - 1; i >= 0; i--) {
		for (int j = 0; j < LongSize / 4; j++) {
			char symbol = byteToHexSymbol((unsigned char)(blocks[i] << j * 4 >> LongSize - 4));
			if (isStart)
			{
				if (symbol == '0') {
					continue;
				}
				else {
					isStart = !isStart;
				}
			}
			res += symbol;
		}
	}

	if (res.empty()) {
		return "0";
	}

	return res;
}

std::string BigInt::toHexString()
{
	return toHexStringFromData(blocks);
}

bool BigInt::operator<(const BigInt& second) const
{
	// If count of blocks equals we can only compare the last one (it has the biggest part of number)
	if (this->blocks.size() < second.blocks.size()) return true;
	else if (this->blocks.size() > second.blocks.size()) return false;
	else {
		return this->blocks[this->blocks.size() - 1] < second.blocks[second.blocks.size() - 1];
	}
}

bool BigInt::operator<=(const BigInt& second) const
{
	// If count of blocks equals we can only compare the last one (it has the biggest part of number)
	if (this->blocks.size() < second.blocks.size()) return true;
	else if (this->blocks.size() > second.blocks.size()) return false;
	else {
		// Has the same logic with operator < but <=
		return this->blocks[this->blocks.size() - 1] <= second.blocks[second.blocks.size() - 1];
	}
}

bool BigInt::operator>(const BigInt& second) const
{
	// If not <= than >
	return !this->operator<=(second);
}

bool BigInt::operator>=(const BigInt& second) const
{
	// If not < than >=
	return !this->operator<(second);
}

bool BigInt::operator==(const BigInt& second) const
{
	if(this->blocks.size() == second.blocks.size()) {
		return this->blocks[this->blocks.size() - 1] == second.blocks[second.blocks.size() - 1];
	}
	
	return false;
}

bool BigInt::operator!=(const BigInt& second) const
{
	return !this->operator==(second);
}


BigInt BigInt::operator+(const BigInt& second) const
{
	std::vector<unsigned long> resBlocks;

	int size = std::max(this->blocks.size(), second.blocks.size());

	// If we need to carry a bit from the previous block to the next
	bool carry = false;

	for (int i = 0; i < size; i++)
	{
		unsigned long num1 = this->blocks.size() > i ? this->blocks[i] : 0;
		unsigned long num2 = second.blocks.size() > i ? second.blocks[i] : 0;
		// Added two blocks or 0 if one of bigInts has more blocks than another
		unsigned long thisBlock = num1 + num2;

		resBlocks.push_back(thisBlock);

		// Added bit if need
		if (carry) {
			resBlocks[i]++;
		}

		// If the result of the sum of two blocks / 2 less than both of added blocks or equal 0 with the carry bit we need to carry a bit to the next block (this indicates an overflow) 
		unsigned long half = thisBlock / 2;
		if (((half) < num1 && (half) < num2) || (resBlocks[i] == 0 && carry)) {
			carry = true;
		}
		else {
			carry = false;
		}

	}

	// If we have't blocks but still have the bit we need to carry - block with 1 (carry bit) will be added 
	if (carry) {
		resBlocks.push_back(1);
	}

	BigInt res = BigInt();
	res.blocks = resBlocks;
	return res;
}

BigInt BigInt::operator-(const BigInt& second) const
{
	// At this time BigInt works only with possitive numbers
	if (this->operator<(second)) {
		throw "Negative numbers is not enable";
	}

	std::vector<unsigned long> resBlocks;

	// We know that (this) num more than second 
	int size = this->blocks.size();

	// If we need to carry a bit to the previous block from the next
	bool carry = false;

	for (int i = 0; i < size; i++)
	{
		unsigned long num1 = this->blocks[i];
		unsigned long num2 = second.blocks.size() > i ? second.blocks[i] : 0;

		// Subtracted two blocks or 0 if one of bigInts has more blocks than another
		unsigned long thisBlock = num1 - num2;

		if (carry) {
			thisBlock--;
		}

		resBlocks.push_back(thisBlock);

		// Indicates of underflow
		if (num1 < num2 || (thisBlock + 1 == 0 && carry)) {
			carry = true;
		}
		else {
			carry = false;
		}
	}

	// Remove all 0 blocks at the end of resBlocks
	while (resBlocks[resBlocks.size() - 1] == 0) {
		resBlocks.erase(resBlocks.begin() + resBlocks.size() - 1);
	}

	BigInt res = BigInt();
	res.blocks = resBlocks;
	return res;
}

BigInt BigInt::operator*(const BigInt& second) const
{
	BigInt res = BigInt("0");


	// If we find the largest and the smallest value we can reduce the numver of iteration
	std::vector<unsigned long> biggest = this->operator>=(second) ? this->blocks : second.blocks;

	std::vector<unsigned long> smallest = this->operator<(second) ? this->blocks : second.blocks;

	BigInt tmp;
	tmp.blocks = biggest;

	// We go through all the bits in the smallest number and if we have the bit 1 - we add the shifted biggest number (we shift the value at each iteration)
	for (int i = 0; i < smallest.size(); i++)
	{
		for (int j = LongSize - 1; j >= 0; j--)
		{
			if (((smallest[i] << j) >> (LongSize - 1)) == 1) {
				res = res + tmp;
			}
			// At each step we need to shift biggest value as in long multiplication.
			tmp = tmp << 1;
		}
	}

	return res;
}

BigInt BigInt::operator/(const BigInt& second) const
{
	return BigInt();
}

BigInt BigInt::operator<<(int n) const
{
	if (n < 0) {
		throw "Incorrect amount of shift steps";
	}

	BigInt res;
	res.blocks = blocks;
	std::vector<unsigned long> resBlocks;

	// We can't lose most significant bit
	bool carry = false;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < res.blocks.size(); j++)
		{
			// If carry is true - last block is overflow, we need to add 1
			resBlocks.push_back((res.blocks[j] << 1) + (carry ? 1 : 0));

			// If resBlocks[j] less than was in res.blocks[j] - overflow
			if (resBlocks[j] < res.blocks[j]) {
				carry = true;
			}
			else {
				carry = false;
			}
		}

		if (carry) {
			resBlocks.push_back(1);
		}

		res.blocks = resBlocks;
		resBlocks.clear();
	}

	return res;
}
