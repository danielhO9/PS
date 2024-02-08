#include <bits/stdc++.h>
using namespace std;

int cal(int x) {
	string s = to_string(x);
	int ret = 0;
	for (auto i: s) {
		ret += i - '0';
	}
	return ret;
}

void solve() {
	int x, k; cin >> x >> k;
	while (true) {
		if (cal(x) % k == 0) {
			cout << x << '\n';
			return;
		}
		++x;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}