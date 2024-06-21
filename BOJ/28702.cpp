#include <bits/stdc++.h>
using namespace std;

void solve() {
	string num[3];
	int ans;
	for (int i = 0; i < 3; ++i) {
		cin >> num[i];
		if ('0' <= num[i][0] && num[i][0] <= '9') {
			ans = stoi(num[i]) + 3 - i;
		}
	}
	if (ans % 3 == 0 && ans % 5 == 0) {
		cout << "FizzBuzz";
	} else if (ans % 3 == 0 && ans % 5 != 0) {
		cout << "Fizz";
	} else if (ans % 5 == 0) {
		cout << "Buzz";
	} else {
		cout << ans;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}