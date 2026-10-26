#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
vector<int> adj[100001];
int one[100001];
int par[100001];

void dfs(int v, int p) {
	par[v] = p;
	for (auto u: adj[v]) if (u != p) {
		dfs(u, v);
	}
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) adj[i].clear();
	for (int i = 0; i < n - 1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(1, 0);
	string tmp; cin >> tmp;
	for (int i = 1; i <= n; ++i) {
		if (tmp[i - 1] == '?') one[i] = 2;
		else one[i] = tmp[i - 1] - '0';
	}
	int ans = 0;
	vector<int> cnt(3, 0);
	int tcnt = 0;
	for (int i = 2; i <= n; ++i) {
		if (adj[i].size() == 1 && adj[i][0] == par[i]) {
			++cnt[one[i]];
		} else {
			if (one[i] == 2) ++tcnt;
		}
	}
	if (one[1] == 2) {
		if (cnt[0] == cnt[1]) {
			ans += cnt[0];
			if (tcnt % 2) ans += (cnt[2] + 1) / 2;
			else ans += cnt[2] / 2;
		} else {
			ans += max(cnt[0], cnt[1]);
			ans += cnt[2] / 2;
		}

	} else {
		ans += cnt[1 - one[1]];
		ans += (cnt[2] + 1) / 2;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}