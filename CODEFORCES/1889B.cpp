#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve () {
	LL n, c; cin >> n >> c;
	LL a[n + 1]; for (int i = 1; i <= n; ++i) cin >> a[i];
	vector<pair<LL, LL>> V;
	for (LL i = 1; i <= n; ++i) V.push_back({i * c - a[i], i});
	sort(V.begin(), V.end());
	for (auto [i, j]: V) {
		if (j == 1) continue;
		if (a[j] + a[1] < j * c) { cout << "No\n"; return; }
		a[1] += a[j];
	}
	cout << "Yes\n"; return;
}

int main () {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while (t--) solve();
}