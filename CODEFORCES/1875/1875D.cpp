#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL matchCache(vector<vector<LL>>& cache, LL v, LL t, vector<pair<LL, LL>>& V) {
	LL& ret = cache[v][t];
	if (ret != -1) return ret;
	ret = V[v].first * (V[t].second - 1);
	ret += V[t].first;
	if (t == 0) return V[v].first * (V[t].second - 1);
	LL temp = LLONG_MAX;
	for (LL i = 0; i < t; ++i) {
		temp = min(temp, matchCache(cache, t, i, V));
	}
	ret += temp;
	return ret;
}

void solve() {
	LL n; cin >> n;
	LL a[n]; for (int i = 0; i < n; ++i) cin >> a[i];
	vector<LL> cnt(n, 0);
	for (int i = 0; i < n; ++i) if (a[i] < n) ++cnt[a[i]];
	LL maxv;
	for (LL i = 0; i < n; ++i) if (cnt[i] == 0) {
		maxv = i; break;
	}
	if (maxv == 0) {
		cout << 0 << '\n';
		return;
	}
	vector<pair<LL, LL>> V;
	for (LL i = 0; i < maxv; ++i) {
		if (V.empty()) V.push_back({i, cnt[i]});
		else {
			if (V.back().second > cnt[i]) V.push_back({i, cnt[i]});
		}
	}
	V.push_back({maxv, 0});
	vector<vector<LL>> cache(V.size(), vector<LL>(V.size(), -1));
	LL ans = LLONG_MAX;
	for (LL i = 0; i < (LL)V.size() - 1; ++i) ans = min(ans, matchCache(cache, (LL)V.size() - 1, i, V));
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}