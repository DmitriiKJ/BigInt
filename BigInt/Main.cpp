#include <iostream>
#include "BigInt.h"
using namespace std;

int main() {
	BigInt bigNum = BigInt("846a927d92f628e928f");
	cout << bigNum.toHexString() << endl;

	return 0;
}