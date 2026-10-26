#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n; cin >> n;
	string s; cin >> s;
	char last = '_';
	vector<char> V;
	for (auto i: s) {
		if (i == '1') {
			V.push_back(i);
			last = i;
		} else {
			if (last != '0') V.push_back(i);
			last = i;
		}
	}
	int one = 0, zero = 0;
	for (auto i: V) {
		if (i == '1') ++one;
		else ++zero;
	}
	if (one > zero) cout << "YES\n";
	else cout << "NO\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}