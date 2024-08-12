#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n; cin >> n;
	int p[n]; for (int i = 0; i < n; ++i) cin >> p[i];
	for (int i = 0; i < n; ++i) cout << p[i] % n + 1 << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}