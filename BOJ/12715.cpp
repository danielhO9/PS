#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1000000007;
ll n, m;
ll X, Y, Z;
ll A[1000];
ll B[1000];
ll cache[1000];

void solve() {
	cin >> n >> m >> X >> Y >> Z;
	for (int i = 0; i < m; ++i) cin >> A[i];
	for (int i = 0; i < n; ++i) {
		B[i] = A[i % m];
		A[i % m] = (X * A[i % m] + Y * (i + 1)) % Z;
	}
	ll ans = 0;
	for (int i = 0; i < n; ++i) {
		cache[i] = 1;
		for (int j = 0; j < i; ++j) if (B[j] < B[i]) {
			cache[i] += cache[j]; cache[i] %= MOD;
		}
		ans += cache[i];
		ans %= MOD;
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	for (int i = 1; i <= t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
		cout << '\n';
	}
}