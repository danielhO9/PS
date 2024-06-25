#include <bits/stdc++.h>
using namespace std;

vector<int> adj[100001];
int p[100001], col[100001], par[100001];
deque<pair<int, int>> query;
set<int> S[100001];

int find(int x) {
	if (par[x] == x) return x;
	par[x] = find(par[x]);
	return par[x];
}

void Union(int x, int y) {
	x = find(x); y = find(y);
	par[x] = y;
}

void solve() {
	int N, Q; cin >> N >> Q;
	vector<int> ans;
	p[1] = 0; for (int i = 2; i <= N; ++i) cin >> p[i];
	for (int i = 1; i <= N; ++i) cin >> col[i];
	for (int i = 1; i <= N; ++i) {
		par[i] = i;
		S[i].insert(col[i]);
	}
	for (int i = 0; i < N + Q - 1; ++i) {
		int t, a; cin >> t >> a;
		query.push_front({t, a});
	}
	for (auto i: query) {
		if (i.first == 1) {
			int a = i.second, b = p[a];
			a = find(a), b = find(b);
			if (S[a].size() > S[b].size()) swap(a, b);
			for (auto j: S[a]) S[b].insert(j);
			S[a].clear();
			Union(a, b);
		} else {
			ans.push_back(S[find(i.second)].size());
		}
	}
	for (int i = (int) ans.size() - 1; i >= 0; --i) cout << ans[i] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}