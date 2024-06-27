#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
	if (a < b) swap(a, b);
	if (b == 0) return a;
	return gcd(b, a % b);
}

void solve() {
	int n, m, k; cin >> n >> m >> k;
	ll a[n][m]; for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> a[i][j];
	int snow[n][m];
	for (int i = 0; i < n; ++i){
		string s; cin >> s;
		for (int j = 0; j < m; ++j) snow[i][j] = (s[j] == '1');
	}
	ll dif = 0;
	ll sum[n][m];
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
		if (snow[i][j]) dif += a[i][j];
		else dif -= a[i][j];
		sum[i][j] = snow[i][j];
	}
	dif = abs(dif);
	if (dif == 0) {
		cout << "YES\n";
		return;
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 1; j < m; ++j) {
			sum[i][j] += sum[i][j - 1];
		}
	}
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < m; ++j) sum[i][j] += sum[i - 1][j];
	}
	set<ll> S;
	for (int i = 0; i <= n - k; ++i) for (int j = 0; j <= m - k; ++j) {
		ll ret = sum[i + k - 1][j + k - 1];
		if (i != 0) ret -= sum[i - 1][j + k - 1];
		if (j != 0) ret -= sum[i + k - 1][j - 1];
		if (i != 0 && j != 0) ret += sum[i - 1][j - 1];
		if (abs(2 * ret - k * k) != 0) S.insert(abs(2 * ret - k * k));
	}
	if (S.empty()) {
		cout << "NO\n";
		return;
	}
	ll g = *S.begin();
	for (auto i: S) g = gcd(g, i);
	if (dif % g == 0) {
		cout << "YES\n";
	} else cout << "NO\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}