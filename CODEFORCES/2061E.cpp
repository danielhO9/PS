#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m, k;
ll a[100000];
ll b[10];
ll cache[100000][11];
ll pcnt[1 << 10];

void init() {
	for (int i = 0; i < (1 << 10); ++i) pcnt[i] = __builtin_popcount(i);
}

void solve() {
	cin >> n >> m >> k;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < m; ++i) cin >> b[i];

	for (int i = 0; i < n; ++i) for (int j = 0; j <= m; ++j) cache[i][j] = INT32_MAX;
	vector<ll> band((1 << m), (1 << 30) - 1);
	
	for (int i = 0; i < (1 << m); ++i) for (int j = 0; j < m; ++j) if ((i >> j) & 1) {
		band[i] &= b[j];
	}
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < (1 << m); ++j) {
			cache[i][pcnt[j]] = min(cache[i][pcnt[j]], a[i] & band[j]);
		}
	}
	
	for (int i = 0; i < n; ++i) for (int j = 0; j <= m; ++j) cache[i][j] = a[i] - cache[i][j];
	
	vector<ll> upd;
	for (int i = 0; i < n; ++i) for (int j = 1; j <= m; ++j) upd.push_back(cache[i][j] - cache[i][j - 1]);
	
	ll ans = 0;
	for (int i = 0; i < n; ++i) ans += a[i];
	sort(upd.begin(), upd.end());
	reverse(upd.begin(), upd.end());
	upd.resize(k);
	for (auto i: upd) ans -= i;
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	int t; cin >> t;
	while (t--) solve();
}