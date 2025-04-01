#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Edge {
    int u, v; double c;
    Edge(int _u, int _v, double _c): u(_u), v(_v), c(_c) {};
    bool operator< (Edge e) const { return c < e.c; }
};

ll w, n;
ll x[1000], y[1000], r[1000];

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
    cin >> w >> n;
    for (int i = 0; i < n; ++i) cin >> x[i] >> y[i] >> r[i];
    // left: n, right: n + 1
    priority_queue<Edge> pq;
    for (int i = 0; i < n; ++i) {
        if (x[i] <= r[i]) pq.push(Edge(n, i, -0.0));
        else pq.push(Edge(n, i, - x[i] + r[i]));
        if (x[i] + r[i] >= w) pq.push(Edge(n + 1, i, -0.0));
        else  pq.push(Edge(n + 1, i, - w + x[i] + r[i]));
        for (int j = i + 1; j < n; ++j) {
            if ((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]) > (r[i] + r[j]) * (r[i] + r[j])) {
                double c = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])) - r[i] - r[j];
                pq.push(Edge(i, j, -c));
            } else pq.push(Edge(i, j, -0.0));
        }
    }
    pq.push(Edge(n, n + 1, -w));
    UF uf; uf.init(n + 2);
    double ans = 0;
    while (uf.find(n) != uf.find(n + 1) && !pq.empty()) {
        Edge cur = pq.top(); pq.pop();
        ans = -cur.c / 2;
        uf.union_path(cur.u, cur.v);
    }
    cout << fixed;
    cout.precision(6);
    cout << ans << '\n';
    
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}