#include <bits/stdc++.h>
using namespace std;

string s;

int solution() {
	cin >> s;
	int a = 0; int b = 0;
	for (auto i: s) {
		if (i == '0') ++a;
		else ++b;
	}
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] == '0') --b;
		else --a;
		if (a < 0 || b < 0) {
			return (int) s.length() - i;
		}
	}
	return 0;
	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) cout << solution() << '\n';
}