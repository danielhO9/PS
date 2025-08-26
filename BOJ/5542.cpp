#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 0-index
struct UF {
	vector<int> par, rk;

    UF() = default;
	UF(int _sz) {
		par.resize(_sz);
		rk.resize(_sz);
		for (int i = 0; i < _sz; ++i) par[i] = i;
	}
	int find(int x) {
		if (par[x] == x) return x;
		par[x] = find(par[x]);
		return par[x];
	}
	void union_rank(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return;
		if (rk[x] > rk[y]) swap(x, y);
		par[x] = y;
		if (rk[x] == rk[y]) ++rk[y];
	}
} uf;

struct Query {
    int idx, u, v;
};

struct Edge {
    int u, v; ll d;
};

int N, M, K, Q;
ll dis[100001], l[100000], r[100000], m[100000];
vector<pair<int, ll>> adj[100001];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M >> K >> Q;
    for (int i = 0; i < M; ++i) {
        int u, v; ll d; cin >> u >> v >> d;
        adj[u].push_back(make_pair(v, d));
        adj[v].push_back(make_pair(u, d));
    }
    for (int i = 1; i <= N; ++i) dis[i] = LLONG_MAX;
    priority_queue<pair<ll, int>> pq;
    for (int i = 0; i < K; ++i) {
        int v; cin >> v;
        dis[v] = 0;
        pq.push(make_pair(0, v));
    }
    vector<Query> query(Q);
    for (int i = 0; i < Q; ++i) {
        query[i].idx = i;
        cin >> query[i].u >> query[i].v;
    }
    while (!pq.empty()) {
        auto [d, v] = pq.top(); pq.pop();
        d *= -1;
        if (dis[v] != d) continue;
        for (auto [u, dif]: adj[v]) {
            ll nd = d + dif;
            if (dis[u] > nd) {
                pq.push(make_pair(-nd, u));
                dis[u] = nd;
            }
        }
    }
    vector<ll> diss;
    for (int i = 1; i <= N; ++i) diss.push_back(dis[i]);
    sort(diss.begin(), diss.end());
    diss.erase(unique(diss.begin(), diss.end()), diss.end());
    reverse(diss.begin(), diss.end());

    unordered_map<ll, int> dis_to_idx;
    for (int i = 0; i < diss.size(); ++i) dis_to_idx[diss[i]] = i;

    vector<pair<int, int>> edges[diss.size()];
    for (int i = 1; i <= N; ++i) for (auto [j, _]: adj[i]) edges[dis_to_idx[min(dis[i], dis[j])]].push_back(make_pair(i, j));
    
    vector<vector<int>> queries(diss.size());
    for (int i = 0; i < Q; ++i) {
        l[i] = -1, r[i] = diss.size(); --r[i];
        if (l[i] + 1 < r[i]) {
            m[i] = (l[i] + r[i]) / 2;
            queries[m[i]].push_back(i);
        }
    }
    while (true) {
        
        bool flag = true;
        for (int i = 0; i < diss.size(); ++i) if (!queries[i].empty()) flag = false;
        if (flag) break;

        uf = UF {N + 1};
        vector<vector<int>> nqueries(diss.size());

        for (int i = 0; i < diss.size(); ++i) {
            for (const auto& edge: edges[i]) uf.union_rank(edge.first, edge.second);
            for (auto j: queries[i]) {
                if (uf.find(query[j].u) == uf.find(query[j].v)) r[j] = i;
                else l[j] = i;

                if (l[j] + 1 < r[j]) {
                    m[j] = (l[j] + r[j]) / 2;
                    nqueries[m[j]].push_back(j);
                }
            }
        }
        swap(nqueries, queries);
    }
    for (int i = 0; i < Q; ++i) cout << diss[r[i]] << '\n';
}