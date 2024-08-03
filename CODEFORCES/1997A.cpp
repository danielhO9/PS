#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	string s; cin >> s;
	bool flag = false;
	cout << s[0];
	for (int i = 1; i < s.size(); ++i) {
		if (s[i] == s[i - 1] && !flag) {
			if (s[i] == 'a') cout << 'b';
			else cout << 'a';
			flag = true;
		}
		cout << s[i];
		
	}
	if (!flag) {
		if (s.back() == 'a') cout << 'b';
		else cout << 'a';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}