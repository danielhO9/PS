#include <bits/stdc++.h>
using namespace std;

void solve() {
	string s; cin >> s;
	int n = s.size();
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += s[i] - '0';
	}
	if (sum % 3 != 0) {
		cout << -1;
		return;
	}
	bool flag = false;
	for (int i = 0; i < n; ++i) {
		if (s[i] == '0') flag = true;
	}
	if (!flag) {
		cout << -1;
		return;
	}
	sort(s.begin(), s.end(), [](const char& a, const char& b) {
		return a > b;
	});
	cout << s;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}