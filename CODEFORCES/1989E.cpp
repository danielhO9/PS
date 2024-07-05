#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 998244353;
ll cache[200001][11];
ll sum[200001][11];

void solve() {
	ll n, k; cin >> n >> k;
	for (int i = 1; i <= n; ++i) cache[i][1] = 1;
	for (int i = 1; i <= n; ++i) sum[i][1] = i;
	for (ll i = 2; i <= n; ++i) {
		for (ll j = 2; j <= k + 1; ++j) {
			cache[i][min(j, k)] += sum[i - 1][j - 1];
			cache[i][min(j, k)] %= MOD;
			if (i > 2 && i != n) cache[i][min(j, k)] -= cache[i - 2][j - 1];
			cache[i][min(j, k)] += MOD;
			cache[i][min(j, k)] %= MOD;
		}
		for (ll j = 2; j <= k; ++j) {
			sum[i][j] = sum[i - 1][j] + cache[i][j];
			sum[i][j] %= MOD;
		}
	}
	cout << cache[n][k];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}