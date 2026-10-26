#include <bits/stdc++.h>
using namespace std;

struct Query {
	int idx;
	bool shrink;
};

int n, q;
int dis[20][20];
vector<Query> events;
int cache[1 << 20][20];
const int MAX = 987654321;
int lst[20];

int matchCache(int mask, int idx) {
	int& ret = cache[mask][idx];
	if (ret != -1) return ret;
	if (!((mask >> idx) & 1)) {
		ret = MAX;
		return ret;
	}
	if (mask == (1 << idx)) {
		ret = 1;
		return ret;
	}
	int nmask = (mask ^ (1 << idx));
	ret = MAX;
	for (int i = 0; i < n; ++i) if ((nmask >> i) & 1) {
		ret = min(ret, matchCache(nmask, i) + dis[i][idx]);
	}
	return ret;
}

void solve() {
	cin >> n >> q;
	for (int i = 0; i < q; ++i) {
		int idx; char c; cin >> idx >> c; --idx;
		if (c == '+') events.push_back({idx, false});
		else events.push_back({idx, true});
	}
	for (auto i: events) if (!i.shrink) ++lst[i.idx];
	
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) if (i != j) {
		int cur = 0;
		dis[i][j] = 1;
		for (auto k: events) {
			if (k.idx == i && !k.shrink) --cur;
			if (k.idx == j && k.shrink) ++cur;
			if (cur < 0) {
				++cur;
				++dis[i][j];
			}
		}
	}
	// for (int i = 0; i < n; ++i) {
	// 	for (int j = 0; j < n; ++j) cout << dis[i][j] << ' ';
	// 	cout << '\n';
	// }
	memset(cache, -1, sizeof(cache));
	// for (int i = 0; i < n; ++i) {
	// 	for (int j = 0; j < (1 << n); ++j) {
	// 		if (matchCache(j, i) == MAX) cout << "MAX ";
	// 		else cout << matchCache(j, i) << ' ';
	// 	}
	// 	cout << '\n';
	// }
	int ans = MAX;
	for (int i = 0; i < n; ++i) {
		ans = min(ans, lst[i] + matchCache((1 << n) - 1, i));
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}