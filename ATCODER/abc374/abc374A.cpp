#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	string s; cin >> s;
	int n = s.size();
	if (n < 3) {
		cout << "No";
		return;
	}
	if (s[n - 1] == 'n' && s[n - 2] == 'a' && s[n - 3] == 's') {
		cout << "Yes";
	} else cout << "No";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}