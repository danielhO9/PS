#include <bits/stdc++.h>
using namespace std;

int cache[100], n;
vector<pair<int, int>> V;

int matchCache(int x) {
	int& ret = cache[x];
	if (ret != -1) return ret;
	ret = 1;
	for (int i = x + 1; i < n; ++i) {
		if (V[x].second < V[i].second) ret = max(ret, 1 + matchCache(i));
	}
	return ret;
}

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int a, b; cin >> a >> b;
		V.push_back({a, b});
	}
	sort(V.begin(), V.end());
	memset(cache, -1, sizeof(cache));
	int ans = 0;
	for (int i = 0; i < n; ++i) ans = max(ans, matchCache(i));
	cout << n - ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}