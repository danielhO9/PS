#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n; cin >> n;
	string s; cin >> s;
	if (s.front() == s.back()) {
		cout << "NO\n"; return;
	}
	cout << "YES\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}