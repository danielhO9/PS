#include <bits/stdc++.h>
using namespace std;

void f(char t, string& s) {
	if (t == 'J') {
		char tmp = s.back(); s.pop_back();
		s = tmp + s;
	} else if (t == 'C') {
		reverse(s.begin(), s.end());
		char tmp = s.back(); s.pop_back();
		reverse(s.begin(), s.end());
		s.push_back(tmp);
	} else if (t == 'E') {
		int n = s.size();
		string ns;
		for (int i = (n + 1) / 2; i < n; ++i) ns.push_back(s[i]);
		if (n % 2) ns.push_back(s[n / 2]);
		for (int i = 0; i < n / 2; ++i) ns.push_back(s[i]);
		swap(ns, s);
	} else if (t == 'A') {
		reverse(s.begin(), s.end());
	} else if (t == 'P') {
		for (auto& i: s) if ('0' <= i && i <= '9') {
			--i;
			if (i < '0') i = '9';
		}
	} else if (t == 'M') {
		for (auto& i: s) if ('0' <= i && i <= '9') {
			++i;
			if (i > '9') i = '0';
		}
	}
}

void solve() {
	string s1, s2; cin >> s1 >> s2;
	reverse(s1.begin(), s1.end());
	for (auto i: s1) {
		f(i, s2);
		// cout << s2 << '\n';
	}
	cout << s2 << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}