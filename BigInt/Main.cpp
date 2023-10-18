#include "BigInt.h"

int main()
{
    BigNum a, b;
    a.setHex("51bf608414ad5726a3c1bec098f77b1b54ffb2787f8d528a74c1d7fde6470ea4");
    b.setHex("403db8ad88a3932a0b7e8189aed9eeffb8121dfac05c3512fdb396dd73f6331c");
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << a.getHex() << endl;
    cout << b.getHex() << endl;
    BigNum ab = XOR(a, b);
    cout << ab.getHex() << endl;
    cout << "-------------------------------------" << endl;
    //==================
    a.setHex("5a7b3d1a"); // 0101 1010 0111 1011 0011 1101 0001 1010
    cout << a.getHex() << endl;
    BigNum c = INV(a);
    cout << c.getHex() << endl; // 1010 0101 1000 0100 1100 0010 1110 0101
    // При переводі до бінарної системи инверсію видно
    cout << "-------------------------------------" << endl;
    a.setHex("74");
    b.setHex("5");
    BigNum d = OR(a, b);
    cout << d.getHex() << endl;
    cout << "-------------------------------------" << endl;
    BigNum f = AND(a, b);
    cout << f.getHex() << endl;
    cout << "-------------------------------------" << endl;
    /*a.setHex("100");
    BigNum shiftR = a.shiftR(3);
    cout << shiftR.getHex() << endl;
    cout << "-------------------------------------" << endl;
    BigNum shiftL = a.shiftL(1);
    cout << shiftL.getHex() << endl;
    cout << "-------------------------------------" << endl;*/

    return 0;
}