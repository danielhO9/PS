#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, a, b;

void solve() {
	cin >> n >> a >> b;
	if (abs(a - b) % 2) {
		cout << "NO\n";
	} else {
		cout << "YES\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}