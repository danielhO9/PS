#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAX = 987654321;

struct Point {
	ll x, y, z;
};

struct Edge {
	int s, e;
	ll t, d;
};

Point pts[120];
Edge par[120];
ll dis[120];
vector<Edge> edges;
int n, N;

ll dis_pt(int s, int e) {
	// cout << s << ' ' << e << ' ' << round(sqrt((pts[s].x - pts[e].x) * (pts[s].x - pts[e].x) + (pts[s].y - pts[e].y) * (pts[s].y - pts[e].y) + (pts[s].z - pts[e].z) * (pts[s].z - pts[e].z))) << '\n';
	return ceil(sqrt((pts[s].x - pts[e].x) * (pts[s].x - pts[e].x) + (pts[s].y - pts[e].y) * (pts[s].y - pts[e].y) + (pts[s].z - pts[e].z) * (pts[s].z - pts[e].z)));
}

int needUpdate() {
	int ret;
	for (int i = 0; i < N; ++i) {
		ret = -1;
		for (auto e: edges) {
			if (dis[e.e] > max(dis[e.s], e.t) + e.d) {
				dis[e.e] = max(dis[e.s], e.t) + e.d;
				ret = e.e;
				par[e.e] = e;
			}
		}
	}
	return ret;
}

void update(int v) {
	int x = v;
	for (int i = 0; i < N; ++i) x = par[x].s;
	// cout << x << ' ' << dis[x] <<  '\n';
	vector<int> path;
	ll dif = MAX;
	for (int cur = x; ; cur = par[cur].s) {
		path.push_back(cur);
		dif = min(dif, dis[par[cur].s] - par[cur].t);
		if (cur == x && path.size() > 1) break;
	}
	path.pop_back();
	// for (auto i: path) cout << i << ' ';
	// cout << '\n';
	for (auto i: path) dis[i] -= dif;
}

void solve() {
	cin >> pts[0].x >> pts[0].y >> pts[0].z >> pts[1].x >> pts[1].y >> pts[1].z >> n;
	edges.clear();
	memset(par, -1, sizeof(par));
	for (int i = 0; i < n; ++i) {
		cin >> pts[2 * i + 2].x >> pts[2 * i + 2].y >> pts[2 * i + 2].z >> pts[2 * i + 3].x >> pts[2 * i + 3].y >> pts[2 * i + 3].z;
		ll t, d; cin >> t >> d;
		edges.push_back({2 * i + 2, 2 * i + 3, t, d});
	}
	N = 2 * n + 2;
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) if (i != j) {
		edges.push_back({i, j, -MAX, dis_pt(i, j)});
	}
	for (int i = 0; i < N; ++i) dis[i] = MAX;
	dis[0] = 0ll;
	while (true) {
		int v = needUpdate();
		if (v == -1) break;
		update(v);
	}
	cout << dis[1] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}

/*
1
0 0 0 100 0 0
2
1 1 0 1 2 0 -100 -2
0 1 0 100 1 0 -150 10
*/