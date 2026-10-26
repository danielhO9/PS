#include <bits/stdc++.h>
using namespace std;

string s;

void solution() {
	cin >> s;
	for (int i = 1; i < s.length(); ++i) {
		if (s[i] != '0') {
			if (stoi(s.substr(0, i)) < stoi(s.substr(i, (int)s.length() - i))) {
				cout << s.substr(0, i) << " " << s.substr(i, (int)s.length() - i) << '\n';
				return;
			} else {
				cout << -1 << '\n';
				return;
			}
		}
	}
	cout << -1 << '\n';
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solution();
}