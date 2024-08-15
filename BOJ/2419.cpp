#include <bits/stdc++.h>
using namespace std;

int n, m;
int x[301];
int cache[301][301][2];

int dis(int i, int j) { return x[j] - x[i]; }

int matchCache(int l, int r, int t, int cnt) {
	if (cnt == 0) return 0;
	if (l == 0 && r == n) return 0;
	int& ret = cache[l][r][t];
	if (ret != -1) return ret;
	int now = t ? r : l;
	ret = 0;
	if (l > 0) ret = max(ret, matchCache(l - 1, r, 0, cnt - 1) + m - cnt * dis(l - 1, now));
	if (r < n) ret = max(ret, matchCache(l, r + 1, 1, cnt - 1) + m - cnt * dis(now, r + 1));
	return ret;
}

void solve() {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) cin >> x[i];
	if (n == 0) {
		cout << 0;
		return;
	}
	x[n] = 0;
	sort(x, x + n + 1);
	int idx = lower_bound(x, x + n + 1, 0) - x;
	int ans = 0;
	for (int i = 0; i <= n; ++i) {
		memset(cache, -1, sizeof(cache));
		ans = max(ans, matchCache(idx, idx, 0, i));
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}