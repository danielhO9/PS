#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m, k;

void solve() {
	cin >> n >> m >> k;
	ll A[n][m];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			cin >> A[i][j];

	unordered_map<ll, ll> d[n];
	unordered_map<ll, ll> nd[n];
	ll c[n];
	ll dp[k + 1];
	bool vis[k + 1];
	memset(c, 0, sizeof(c));
	memset(dp, 0, sizeof(dp));
	memset(vis, 0, sizeof(vis));

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) {
			if (A[i][j] == -1)
				++c[i];
			else
				++d[i][A[i][j]];
		}
	
	ll ans = 0;
	for (int i = 0; i < n - 1; ++i) {
		for (auto [j, l] : d[i]) {
			if (d[i + 1].find(j) != d[i + 1].end()) ans += l * d[i + 1][j];
		}
	}
	for (int i = 0; i < n; ++i) {
		for (auto [j, l] : d[i]) {
			if (i > 0)
				nd[i - 1][j] += l;
			if (i + 1 < n)
				nd[i + 1][j] += l;
		}
	}

	ll pmx = 0ll, mx = 0ll, nmx = 0ll;
	ll cns = 0ll;
	for (int i = 0; i < n; ++i) {
		ll cc = i == 0 ? 0 : c[i] * c[i - 1];
		nmx = mx;
		for (auto [j, _]: nd[i]) {
			dp[j] = max(mx + c[i] * nd[i][j] - cc, max(pmx, dp[j]) + c[i] * nd[i][j]);
			nmx = max(nmx, dp[j]);
		}
		cns += cc;
		pmx = max(pmx, mx - cc);
		mx = nmx;
	}
	cout << mx + ans + cns << '\n';
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
}