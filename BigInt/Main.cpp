#include <iostream>
#include "BigInt.h"
using namespace std;

int main() {
	/*BigInt bigNum = BigInt("846a927d92f628e928f");
	cout << bigNum.toHexString() << endl;*/

	BigInt zero = BigInt();
	cout << "Zero: " << zero.toHexString() << endl;

	// 6983033291595
	BigInt bigNum1 = BigInt("659dd38034b");
	cout << "First: " << bigNum1.toHexString() << endl;

	// 42073146227298
	BigInt bigNum2 = BigInt("2643eaef7a62");
	cout << "Second: " << bigNum2.toHexString() << endl;

	// Compare
	if (bigNum1 > bigNum2) {
		cout << "First num more than second" << endl;
	}

	if (bigNum1 < bigNum2) {
		cout << "First num less than second" << endl;
	}

	if (bigNum1 == bigNum2) {
		cout << "First num and second are equal" << endl;
	}

	if (bigNum1 != bigNum2) {
		cout << "First num and second aren't equal" << endl;
	}
	cout << endl;

	// 6983033291595 + 42073146227298 = 49056179518893 (2C9DC8277DAD)
	BigInt bigNum3 = bigNum1 + bigNum2;
	cout << "Sum: " << bigNum3.toHexString() << endl;
	cout << endl;

	// 42073146227298 - 6983033291595 = 35090112935703 (1FEA0DB77717)
	BigInt bigNum4 = bigNum2 - bigNum1;
	cout << "Subtract: " << bigNum4.toHexString() << endl;
	cout << endl;

	// 6983033291595 * 42073146227298 = 293798180787366508982960310 (f3062f4b49fac2020800b6)
	BigInt bigNum5 = bigNum2 * bigNum1;
	cout << "Mult: " << bigNum5.toHexString() << endl;
	cout << endl;

	// 42073146227298 / 6983033291595 = 6
	BigInt bigNum6 = bigNum2 / bigNum1;
	cout << "Subtract: " << bigNum6.toHexString() << endl;
	cout << endl;

	// Test for other functions
	
	// 15
	BigInt eq1 = BigInt("f");
	cout << "First: " << eq1.toHexString() << endl;

	// 15
	BigInt eq2 = BigInt("f");
	cout << "Second: " << eq2.toHexString() << endl;

	// Compare
	if (eq1 >= eq2) {
		cout << "First num more than second or equals" << endl;
	}

	if (eq1 <= eq2) {
		cout << "First num less than second or equals" << endl;
	}

	if (eq1 == eq2) {
		cout << "First num and second are equal" << endl;
	}

	if (eq1 != eq2) {
		cout << "First num and second aren't equal" << endl;
	}
	
	cout << endl;

	// 15 * 4 = 60 (3ñ)
	cout << "Shift: " << eq1.toHexString() << " << 2 = " << (eq1 << 2).toHexString() << endl;

	// 12301370187 / 4 = 3 075 342 546 (b74e00d2)
	cout << "Shift: " << BigInt("2dd38034b").toHexString() << " >> 2 = " << (BigInt("2dd38034b") >> 2).toHexString() << endl;

	return 0;
}