#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int x; cin >> x;
	if (x % 33) {
		cout << "NO\n";
	} else cout << "YES\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}