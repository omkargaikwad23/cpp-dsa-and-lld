#include <iostream>

using namespace std;

int main() {
	int x = 2;
	int div_num = 0;
	cin >> x;
	for (int i = 1; i * i <= x; i++) {
		if (x % i == 0) {
			div_num += i * i == x ? 1 : 2;
		}
	}
	cout << div_num << '\n';
}