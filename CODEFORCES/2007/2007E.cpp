#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, w;
ll par[200001];
ll t[200001];
int last[200001];
ll cnt[200001];
vector<int> adj[200001];

int dfs2(int v, int p) {
	last[v] = v;
	for (auto u: adj[v]) if (u != p) {
		last[v] = max(last[v], dfs2(u, v));
	}
	return last[v];
}

void solve() {
	cin >> n >> w;
	for (int i = 1; i <= n; ++i) {
		adj[i].clear();
		cnt[i] = 0;
	}
	for (int i = 2; i <= n; ++i) {
		cin >> par[i];
		adj[par[i]].push_back(i);
		adj[i].push_back(par[i]);
	}
	dfs2(1, 0);
	for (int x = 2; x <= n; ++x) {
		++cnt[x - 1];
		++cnt[last[x]];
	}

	ll mx = 0ll;
	ll st = 0ll;
	ll fcnt = n;
	for (int i = 0; i < n - 1; ++i) {
		int x; ll y; cin >> x >> y;
		mx += y;

		--cnt[last[x]]; st += y;
		if (cnt[last[x]] == 0) --fcnt;
		--cnt[x - 1]; st += y;
		if (cnt[x - 1] == 0) --fcnt;
		
		cout << st + w * fcnt - mx * fcnt << ' ';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}