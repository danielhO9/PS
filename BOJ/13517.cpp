#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_V = 100001;
vector<pair<int, ll>> adj[MAX_V];
int dep[MAX_V];
ll dis[MAX_V];
vector<vector<int>> f;
int N, M;
int val[MAX_V];
unordered_map<int, int> toIdx;
int toVal[MAX_V];

struct Node {
	int l, r;
	ll val;
};

struct PST {
	vector<Node> tree = {{0, 0, 0}, {0, 0, 0}};
	vector<int> root;
	int sz;
	int ridx;

	void init(int sz_) {
		sz = sz_;
		ridx = 1;
		root.resize(sz);
		root[0] = 1;
	}
	void changeRoot(int idx) { ridx = root[idx]; }
	void setRoot(int idx) {
        root[idx] = tree.size();
		tree.push_back({tree[ridx].l, tree[ridx].r, tree[ridx].val});
		ridx = root[idx];
	}
	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		tree[node].val += val;
		if (start == end) return;
		int mid = (start + end) / 2;
		if (index <= mid) {
			int lidx = tree[node].l;
			tree[node].l = tree.size();
			tree.push_back({tree[lidx].l, tree[lidx].r, tree[lidx].val});
			update(tree[node].l, start, mid, index, val);
		}
		if (index > mid) {
			int ridx = tree[node].r;
			tree[node].r = tree.size();
			tree.push_back({tree[ridx].l, tree[ridx].r, tree[ridx].val});
			update(tree[node].r, mid + 1, end, index, val);
		}
	}
	void update(int rt, int index, ll val) {
		update(root[rt], 0, sz - 1, index, val);
	}
	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return 0;
		if (left <= start && end <= right) return tree[node].val;
		ll lsum = query(tree[node].l, start, (start + end) / 2, left, right);
		ll rsum = query(tree[node].r, (start + end) / 2 + 1, end, left, right);
		return lsum + rsum;
	}
	ll query(int rt, int left, int right) {
		return query(root[rt], 0, sz - 1, left, right);
	}
	ll query2(int x, int y, int lca, int lcap, int left, int right, int k) {
		// cout << left << ' ' << right << '\n';
		if (left == right) return left;
		ll tmp = tree[tree[x].l].val + tree[tree[y].l].val - tree[tree[lca].l].val - tree[tree[lcap].l].val;
		if (tmp >= k) return query2(tree[x].l, tree[y].l, tree[lca].l, tree[lcap].l, left, (left + right) / 2, k);
		else return query2(tree[x].r, tree[y].r, tree[lca].r, tree[lcap].r, (left + right) / 2 + 1, right, k - tmp);
	}
	ll query2(int x, int y, int lca, int lcap, int k) {
		return query2(root[x], root[y], root[lca], root[lcap], 0, sz - 1, k);
	}
} seg;

void dfs(int v, int p, ll d) {
    f[0][v] = p;
    if (p == -1) {
        dep[v] = 0; dis[v] = 0ll;
    } else {
        dep[v] = dep[p] + 1; dis[v] = dis[p] + d;
    }
    for (auto [u, nd]: adj[v]) if (u != p) dfs(u, v, nd);
}

int lca(int u, int v) {
	const int h = f.size();
    if (dep[u] < dep[v]) swap(u, v);
    int dif = dep[u] - dep[v];
	for (int i = 0; i < h; ++i) if ((dif >> i) & 1) {
		u = f[i][u];
	}
    if (u != v) {
        for (int i = h - 1; i >= 0; --i) {
            if (f[i][u] != -1 && f[i][u] != f[i][v]) {
                u = f[i][u]; v = f[i][v];
            }
        }
        u = f[0][u];
    }
    return u;
}

void init(int v = MAX_V) {
	const int h = f.size();
	// root: 1
    dfs(1, -1, 0ll);
	for (int i = 1; i < h; ++i) {
		for (int j = 0; j < v; ++j) {
			if (f[i - 1][j] == -1) f[i][j] = -1;
			else f[i][j] = f[i - 1][f[i - 1][j]];
		}
	}
}

void dfs2(int v, int p) {
	seg.changeRoot(p);
	seg.setRoot(v);
	seg.update(v, val[v], 1);
	for (auto [u, _]: adj[v]) if (u != p) dfs2(u, v);
}

void solve() {
	seg.init(1e5 + 1);
	cin >> N;
	for (int i = 1; i <= N; ++i) cin >> val[i];
	for (int i = 0; i < N - 1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back({v, 1});
		adj[v].push_back({u, 1});
	}
	int h = (int)ceil(log2(N + 1)); ++h;
	f = vector<vector<int>>(h, vector<int>(N + 1));
	init(N + 1);
	int idx = 0;
	set<int> s;
	for (int i = 1; i <= N; ++i) s.insert(val[i]);
	for (auto i: s) {
		toVal[idx] = i;
		toIdx[i] = idx;
		++idx;
	}
	for (int i = 1; i <= N; ++i) val[i] = toIdx[val[i]];
	dfs2(1, 0);
	cin >> M;
	while (M--) {
		int X, Y, K; cin >> X >> Y >> K;
		int lc = lca(X, Y), lcap = 0;
		if (lc != 1) lcap = f[0][lc];
		cout << toVal[seg.query2(X, Y, lc, lcap, K)] << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}