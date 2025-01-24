#include <iostream>
#include "BigInt.h"
using namespace std;

int main() {
	/*BigInt bigNum = BigInt("846a927d92f628e928f");
	cout << bigNum.toHexString() << endl;*/

	// 6983033291595
	BigInt bigNum1 = BigInt("659dd38034b");
	cout << "First: " << bigNum1.toHexString() << endl;

	// 42073146227298
	BigInt bigNum2 = BigInt("2643eaef7a62af474");
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

	// 6983033291595 + 42073146227298 = 49056179518893 (2643eb5518362f7bf)
	BigInt bigNum3 = bigNum1 + bigNum2;
	cout << "Sum: " << bigNum3.toHexString() << endl;
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

	return 0;
}