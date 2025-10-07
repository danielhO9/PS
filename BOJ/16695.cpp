#include <bits/stdc++.h>
using namespace std;

// 0-index
struct UF {
	vector<int> par, rk;
    vector<tuple<int, int, int>> st;

    UF() = default;
	UF(int _sz) {
		par.resize(_sz);
		rk.resize(_sz);
		for (int i = 0; i < _sz; ++i) par[i] = i;
	}
    int time() { return st.size(); }
    void rollback(int t) {
        while (st.size() > t) {
            auto [v, p, r] = st.back(); st.pop_back();
            par[v] = p;
            rk[v] = r;
        }
    }
	int find(int x) {
		if (par[x] == x) return x;
		return find(par[x]);
	}
	void merge(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return;
        st.push_back({x, par[x], rk[x]});
        st.push_back({y, par[y], rk[y]});
		if (rk[x] > rk[y]) swap(x, y);
		par[x] = y;
		if (rk[x] == rk[y]) ++rk[y];
	}
} uf;

struct Edge {
	int u, v, s, e, lv;
};

vector<vector<Edge>> tree;
vector<pair<int, int>> queries;
vector<int> ans;

void update(int node, int start, int end, Edge e) {
    if (e.s > end || e.e < start) return;
    if (e.s <= start && end <= e.e) {
        tree[node].push_back(e);
        return;
    }
	int mid = (start + end) / 2;
    update(node * 2, start, mid, e);
    update(node * 2 + 1, mid + 1, end, e);
}

void dnc(int node, int start, int end, int lv) {
    int t = uf.time();
	for (auto i: tree[node]) if (i.lv <= lv) uf.merge(i.u, i.v);
	if (start == end) {
        if (uf.find(queries[start].first) == uf.find(queries[start].second)) ans[start] = lv;
	} else {
		int mid = (start + end) / 2;
		dnc(node * 2, start, mid, lv);
		dnc(node * 2 + 1, mid + 1, end, lv);
	}
    uf.rollback(t);
}

int N, Q;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> Q;
    int q = 0;

    uf = UF {N};
    map<pair<int, int>, int> m;
    vector<Edge> bridges;
    
    for (int i = 0; i < Q; ++i) {
        int t, x, y; cin >> t >> x >> y;
        if (t == 0) {
            int v; cin >> v;
            m[make_pair(min(x, y), max(x, y))] = bridges.size();
            bridges.push_back(Edge {x, y, (int) queries.size(), -1, v});
        } else if (t == 1) {
            int idx = m[make_pair(min(x, y), max(x, y))];
            bridges[idx].e = queries.size();
        } else {
            queries.push_back(make_pair(x, y));
            ++q;
        }
    }
    ans = vector<int>(q, -1);
    int h = (int)ceil(log2(q));
	int tree_size = (1 << (h + 1));
    tree.resize(tree_size);

    for (auto& i: bridges) {
        if (i.e == -1) i.e = queries.size();
        --i.e;
    }
    for (auto& i: bridges) {
        if (i.s <= i.e && i.s < queries.size()) update(1, 0, q - 1, i);
    }
    for (int i = 9; i >= 0; --i) dnc(1, 0, q - 1, i);
    for (int i = 0; i < q; ++i) cout << ans[i] << '\n';
}