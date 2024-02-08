#include <bits/stdc++.h>
using namespace std;

string s;

// 97 49 -> a, 1
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	for (int i = 0; i < t; ++i) {
		cin >> s;
		for (int i = 97; i < 105; ++i) if ((int)s[0] != i) cout << (char) i << s[1] << '\n';
		for (int i = 1; i < 9; ++i) if ((int)s[1] - 48 != i) cout << s[0] << i << '\n';
	}
}