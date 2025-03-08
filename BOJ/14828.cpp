#include <bits/stdc++.h>
using namespace std;

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

int C;
int adj[4000];
int L[4000], D[4000], dif[1000];
bool vis[1000];

int f(int s, int e) {
	return (L[e] + 24 - ((L[s] + D[s]) % 24)) % 24;
}

void solve() {
	cin >> C;
	for (int i = 0; i < C; ++i) vis[i] = false;
	for (int i = 0; i < 4 * C; ++i) adj[i] = 4 * C;
	int cnt = 0;
	for (int i = 0; i < 2 * C; ++i) {
		int u = (i / 2) * 4 + (i % 2) + 2;
		int e, l, d; cin >> e >> l >> d; --e;
		if (vis[e]) e = 4 * e + 1;
		else vis[e] = true, e = 4 * e;
		adj[u] = e;
		L[u] = l, D[u] = d;
		L[e] = l, D[e] = d;
		cnt += d;
	}
	int v[4];
	for (int i = 1; i < C; ++i) {
		for (int j = 0; j < 4; ++j) v[j] = 4 * i + j;
		int f1 = f(v[1], v[3]) + f(v[0], v[2]);
		swap(v[0], v[1]);
		int f2 = f(v[1], v[3]) + f(v[0], v[2]);
		dif[i] = abs(f1 - f2);
		if (f2 > f1) swap(v[0], v[1]);
		adj[v[0]] = v[2];
		adj[v[1]] = v[3];
		cnt += min(f1, f2);
	}
	int ans = INT32_MAX;
	for (int t = 0; t < 4; ++t) {
		adj[t % 2] = 2 + t / 2;
		adj[!(t % 2)] = 4 * C;
		int tans = cnt;
		tans += f(t % 2, 2 + t / 2);
		tans += L[2 + !(t / 2)];

		UF uf; uf.init(4 * C);
		for (int i = 0; i < C; ++i) for (int j = 0; j < 4; ++j) {
			if (adj[i * 4 + j] != 4 * C) {
				uf.union_path(i * 4 + j, adj[i * 4 + j]);
			}
		}
		vector<pair<int, pair<int, int > > > e;
		for (int i = 1; i < C; ++i) if (uf.find(4 * i) != uf.find(4 * i + 1)) e.push_back(make_pair(dif[i], make_pair(uf.find(4 * i), uf.find(4 * i + 1))));
		sort(e.begin(), e.end());
		for (pair<int, pair<int, int > >& i: e) {
			if (uf.find(i.second.first) != uf.find(i.second.second)) {
				tans += i.first;
				uf.union_path(i.second.first, i.second.second);
			}
		}
		bool flag = true;
		
		for (int j = 0; j < 3; ++j) if (uf.find(j) != uf.find(j + 1)) {
			flag = false;
		}
		if (flag) ans = min(ans, tans);

		
	}
	cout << ans << '\n';

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	for (int i = 1; i <= t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}
}