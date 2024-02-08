#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL matchCache(vector<LL>& cache, LL g, LL& n, vector<LL>& cnt) {
	LL& ret = cache[g];
	if (ret != -1) return ret;
	LL cntt = 0;
	for (LL i = g; i <= n; i += g) cntt += cnt[i];
	ret = cntt * (cntt - 1) / 2;
	for (LL i = g * 2; i <= n; i += g) ret -= matchCache(cache, i, n, cnt);
	return ret;
}

void solve() {
	LL n; cin >> n;
	LL a[n]; for (int i = 0; i < n; ++i) cin >> a[i];
	vector<LL> cnt(n + 1, 0);
	for (auto i: a) ++cnt[i];
	LL ans = n * (n - 1) / 2;
	vector<LL> cache(n + 1, -1);
	vector<bool> visited(n + 1, 0);
	for (int i = 1; i <= n; ++i) {
		if (cnt[i]) {
			for (int j = i; j <= n; j += i) {
				visited[j] = true;
			}
		}
	}

	for (int i = 1; i <= n; ++i) if (visited[i]) ans -= matchCache(cache, i, n, cnt);
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}