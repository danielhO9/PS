#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int n;

LL solution() {
	cin >> n;
	LL cnt = 1;
	while (n > 0) {
		int d = n % 10; n /= 10;
		int mul = 0;
		for (int i = 0; i <= d; ++i) for (int j = 0; j <= d; ++j) {
			if (d - i - j >= 0) mul += 1;
		}
		cnt *= mul;
	}
	return cnt;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	for (int i = 0; i < t; ++i) cout << solution() << '\n';
}