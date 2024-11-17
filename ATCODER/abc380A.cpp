#include <bits/stdc++.h>
using namespace std;

void solve() {
	string s; cin >> s;
	int cnt = 0;
	for (auto i: s) {
		if (i == '1') ++cnt;
	}
	if (cnt != 1) {
		cout << "No";
		return;
	}
	cnt = 0;
	for (auto i: s) {
		if (i == '2') ++cnt;
	}
	if (cnt != 2) {
		cout << "No";
		return;
	}
	cnt = 0;
	for (auto i: s) {
		if (i == '3') ++cnt;
	}
	if (cnt != 3) {
		cout << "No";
		return;
	}
	cout << "Yes";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}