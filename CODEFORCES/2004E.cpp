#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll g[10000001];

void init() {
	memset(g, -1, sizeof(g));
	g[0] = 0; g[1] = 1; g[2] = 0;
	for (int i = 2; i <= 1e7; i += 2) g[i] = 0;
	ll val = 2;
	for (int i = 3; i < 1e7; ++i) {
		if (g[i] != -1) continue;
		for (int j = i; j < 1e7; j += i) if (g[j] == -1) g[j] = val;
		++val;
	}
}

void solve() {
	int n; cin >> n;
	ll a[n];
	for (int i = 0; i < n; ++i) cin >> a[i];
	ll ans = 0ll;
	for (auto i: a) {
		ans ^= g[i];
	}
	if (ans) cout << "Alice\n";
	else cout << "Bob\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	int t; cin >> t;
	while (t--) solve();
}