#include "BigInt.h"

BigNum::BigNum()
{
    num = nullptr;
    size = 0;
}

void BigNum::setHex(string str)
{
    size_t t = 0;
    HexStringToByteArray(str, t);
}

string BigNum::getHex() const
{
    string hexString;
    if (num != nullptr)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 3; j >= 0; j--)
            {
                uint8_t byteValue = (num[i] >> (j * 8)) & 0xFF;
                ostringstream oss;
                oss << hex << setfill('0') << setw(2) << static_cast<int>(byteValue);
                hexString += oss.str();
            }
        }
        int zero = 0;
        for (int i = hexString.length() - 1; i >= 0; i--)
        {
            if (hexString[i] == '0')
            {
                zero++;
            }
            else
            {
                break;
            }
        }
        hexString = hexString.substr(0, hexString.length() - zero);
    }
    // Якщо всі байти були нулі, повернемо "0"
    if (hexString.empty()) {
        return "0";
    }
    return hexString;
}

BigNum BigNum::operator+(BigNum right)
{
    BigNum result;
    result.size = max(this->size, right.size) + 1;
    result.num = new unsigned int[result.size];

    unsigned long long carry = 0;

    for (int i = this->size - 1, i1 = right.size - 1; i >= 0 || i1 >= 0 || carry != 0; i--, i1--)
    {
        unsigned long long sum = carry;

        if (i >= 0)
        {
            sum += static_cast<unsigned long long>(this->num[i]);
        }
        if (i1 >= 0)
        {
            sum += static_cast<unsigned long long>(right.num[i1]);
        }

        result.num[i] = static_cast<unsigned int>(sum);
        carry = static_cast<unsigned int>(sum >> 32);
    }

    return result;
}

BigNum BigNum::operator-(BigNum right)
{
    return BigNum();
}

//BigNum BigNum::shiftR(int n) Десь щось не так
//{
//    BigNum result;
//
//    result.size = this->size;
//    result.num = new unsigned int[result.size];
//
//    int shiftInsideByte = n % 32;
//
//    int shiftOutsideBytes = n / 32;
//
//    for (int i = 0; i < result.size; i++) 
//    {
//        result.num[i] = 0;
//    }
//
//    for (int i = 0; i < result.size; i++) 
//    {
//        unsigned int currentByte = this->num[i];
//
//        unsigned int shiftedBits = 0;
//        if (i + 1 < this->size) 
//        {
//            shiftedBits = this->num[i + 1] << (32 - shiftInsideByte);
//        }
//
//        result.num[i] = (currentByte >> shiftInsideByte) | shiftedBits;
//    }
//
//    while (result.size > 0 && result.num[result.size - 1] == 0) {
//        result.size--;
//    }
//
//    return result;
//}
//
//BigNum BigNum::shiftL(int n)
//{
//    BigNum result;
//
//    result.size = this->size + (n / 32);
//    if (n % 32 != 0) 
//    {
//        result.size++;
//    }
//    result.num = new unsigned int[result.size];
//
//    for (int i = 0; i < result.size; i++) 
//    {
//        result.num[i] = 0;
//    }
//
//    for (int i = 0; i < this->size; i++) 
//    {
//        unsigned int currentByte = this->num[i];
//
//        for (int j = 0; j < 32; j++) 
//        {
//            if ((currentByte & (1u << (31 - j))) != 0) 
//            {
//                int position = i * 32 + j + n;
//                int resultByte = position / 32;
//                int resultBit = position % 32;
//                result.num[resultByte] |= 1u << (31 - resultBit);
//            }
//        }
//    }
//
//    return result;
//}

string BigNum::MOD()
{
    return string();
}

void BigNum::combineBytes(uint8_t* u, size_t sizeByteArray)
{
    if (num != nullptr)
    {
        delete[] num;
    }
    size = static_cast<long>(ceil(sizeByteArray / 4.0));
    num = new unsigned int[size];

    for (int i = 0; i < size; i++)
    {
        num[i] = 0;
        for (int k = 0; k < 4; k++)
        {
            int byteIndex = i * 4 + (3 - k);
            if (byteIndex < sizeByteArray)
            {
                num[i] |= static_cast<uint32_t>(u[byteIndex]) << (k * 8);
            }
        }
    }
    delete[] u;
}

//Перетвореня рядка до масиву байтів
void BigNum::HexStringToByteArray(string& hexString, size_t& t)
{
    if (hexString.length() % 2 != 0)
    {
        hexString = "0" + hexString;
    }
    t = (hexString.length()) / 2;
    uint8_t* byteArray = new uint8_t[t];


    for (size_t i = 0; i < t; i++) {
        std::string byteString = hexString.substr(i * 2, 2);
        byteArray[i] = static_cast<uint8_t>(std::stoul(byteString, nullptr, 16));
    }
    combineBytes(byteArray, t);
}

BigNum INV(BigNum num1)
{
    BigNum result;

    result.size = num1.size;
    result.num = new unsigned int[result.size];

    for (int i = 0; i < result.size; i++)
    {
        result.num[i] = ~num1.num[i];
    }

    return result;
}

BigNum XOR(BigNum  num1, BigNum num2)
{
    BigNum result;

    result.size = max(num1.size, num2.size) + 1;
    result.num = new unsigned int[result.size];

    unsigned int carry = 0;

    for (int i = result.size - 1, i1 = num1.size - 1, i2 = num2.size - 1; i >= 0 || i1 >= 0 || i2 >= 0; i--, i1--, i2--)
    {
        unsigned int value1 = (i1 >= 0) ? num1.num[i1] : 0;
        unsigned int value2 = (i2 >= 0) ? num2.num[i2] : 0;

        result.num[i] = value1 ^ value2 ^ carry;

        carry = ((value1 & value2) | ((value1 ^ value2) & carry)) >> 31;
    }

    if (result.num[0] == 0)
    {
        result.size--;
        unsigned int* newNum = new unsigned int[result.size];
        for (int i = 0; i < result.size; i++) {
            newNum[i] = result.num[i + 1];
        }
        delete[] result.num;
        result.num = newNum;
    }

    return result;
}

BigNum OR(BigNum num1, BigNum num2)
{
    BigNum result;

    result.size = max(num1.size, num2.size);
    result.num = new unsigned int[result.size];

    for (int i = 0; i < result.size; i++)
    {
        result.num[i] = num1.num[i] | num2.num[i];
    }

    return result;
}

BigNum AND(BigNum num1, BigNum num2)
{
    BigNum result;

    result.size = min(num1.size, num2.size);
    result.num = new unsigned int[result.size];

    for (int i = 0; i < result.size; i++)
    {
        result.num[i] = num1.num[i] & num2.num[i];
    }

    return result;
}
