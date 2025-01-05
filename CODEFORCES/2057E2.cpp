#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, m, q;
int dis[400][401][401];

struct UF {
	int sz;
	vector<int> par;

	void init(int _sz) {
		sz = _sz;
		par.resize(sz);
		for (int i = 0; i < sz; ++i) par[i] = i;
	}

	int find(int x) {
		if (par[x] == x) return x;
		par[x] = find(par[x]);
		return par[x];
	}

	void union_path(int x, int y) {
		x = find(x); y = find(y);
		par[x] = y;
	}
};

void solve() {
	cin >> n >> m >> q;
	vector< pair< int, pair<int, int> > > edge;
	
	for (int i = 0; i < n; ++i) for (int j = 1; j <= n; ++j) for (int k = 1; k <= n; ++k) dis[i][j][k] = n;
	for (int i = 1; i <= n; ++i) dis[0][i][i] = 0;

	for (int i = 0; i < m; ++i) {
		int a, b; ll c;
		cin >> a >> b >> c;
		edge.push_back(make_pair(c, make_pair(a, b)));
		dis[0][a][b] = 1;
		dis[0][b][a] = 1;
	}
	for (int k = 1; k <= n; ++k) {
		for (int s = 1; s <= n; ++s) for (int e = 1; e <= n; ++e) {
			dis[0][s][e] = min(dis[0][s][e], dis[0][s][k] + dis[0][k][e]);
		}
	}

	sort(edge.begin(), edge.end());
	UF uf; uf.init(n + 1);
	vector< pair< int, pair<int, int> > > redge;
	for (auto i: edge) {
		if (uf.find(i.second.first) == uf.find(i.second.second)) continue;
		uf.union_path(i.second.first, i.second.second);
		redge.push_back(i);
	}
	assert(redge.size() == n - 1);

	for (int k = 1; k < n; ++k) {
		int a = redge[k - 1].second.first;
		int b = redge[k - 1].second.second;
		for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
			dis[k][i][j] = min(min(dis[k - 1][i][j], dis[k - 1][i][a] + dis[k - 1][b][j]), dis[k - 1][i][b] + dis[k - 1][a][j]);
		}
	}
	while (q--) {
		int a, b, k; cin >> a >> b >> k;
		int l = -1, r = n - 1, mid;
		while (l + 1 < r) {
			mid = (l + r) / 2;
			if (dis[mid][a][b] < k) r = mid;
			else l = mid;
		}
		cout << redge[l].first << ' ';
	}
	// for (int i = 0; i < n; ++i) cout << redge[i].first << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}