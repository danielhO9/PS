#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, K;
ll t[2000];
ll x[2000];
vector<pair<ll, ll>> v;
ll cache[2000][1 << 12];
ll rem[1 << 12];

void init() {
	for (int j = 0; j < (1 << K); ++j) {
		ll tmp = 0ll;
		bool flag = false;
		for (int i = K - 1; i >= 0; --i) {
			if (flag && (j >> i) & 1) tmp += (i + 1);
			if (!((j >> i) & 1)) flag = true;
		}
		rem[j] = tmp;
	}
}

ll matchCache(int n, int mask) {
	ll& ret = cache[n][mask];
	if (ret != LLONG_MIN) return ret;
	if (mask == 0) return ret = 0ll;
	if (__builtin_popcount(mask) > n + 1) return ret = 0;
	if (n == 0) {
		if (__builtin_popcount(mask) == 1) {
			for (int i = K - 1; i >= 0; --i) if ((mask >> i) & 1) return ret = v[n].second * (i + 1);
		} else return ret = 0;
	}
	ret = max(ret, matchCache(n - 1, mask) - rem[mask] * (v[n].first - v[n - 1].first));
	for (int i = 0; i < K; ++i) if ((mask >> i) & 1) {
		ret = max(ret, matchCache(n - 1, mask ^ (1 << i)) + v[n].second * (i + 1) - rem[mask ^ (1 << i)] * (v[n].first - v[n - 1].first));
	}
	return ret;
}

void solve() {
	cin >> N >> K;
	init();
	for (int i = 0; i < N; ++i) cin >> t[i] >> x[i];
	for (int i = 0; i < N; ++i) v.push_back({t[i], x[i]});
	sort(v.begin(), v.end());
	for (int i = 0; i < N; ++i) for (int j = 0; j < (1 << K); ++j) cache[i][j] = LLONG_MIN;
	ll ans = 0ll;
	ll tmp = 0ll;
	for (int i = K - 1; i >= 0; --i) {
		tmp += (1 << i);
		ans = max(ans, matchCache(N - 1, tmp));
		// cout << matchCache(N - 1, tmp) << ' ';
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}