#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SegmentTree {
	vector<ll> arr;
	vector<ll> tree;
	int sz;

	void init(vector<ll>& a, int sz_) {
		sz = sz_;
		arr = a;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
		init_(1, 0, sz - 1);
	}
	void init_(int node, int start, int end) {
		if (start == end) tree[node] = arr[start];
		else {
			init_(node * 2, start, (start + end) / 2);
			init_(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
		}
	}
	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			arr[index] = val;
			tree[node] = val;
			return;
		}
		update(node * 2, start, (start + end) / 2, index, val);
		update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
		tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
	}
	void update(int index, ll val) {
		update(1, 0, sz - 1, index, val);
	}
	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return 0;
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return max(lsum, rsum);
	}
	ll query(int left, int right) {
		return query(1, 0, sz - 1, left, right);
	}
} seg;

const int MAX_V = 200001;
int sz[MAX_V], dep[MAX_V], par[MAX_V], top[MAX_V], in[MAX_V], out[MAX_V];
vector<int> adj[MAX_V];

void dfs1(int v = 1, int p = 0) {
	sz[v] = 1;
	for (auto& i: adj[v]) if (i != p) {
		dep[i] = dep[v] + 1; par[i] = v;
		dfs1(i, v); sz[v] += sz[i];
		if (sz[i] > sz[adj[v][0]]) swap(i, adj[v][0]);
	}
}

int pv = -1;
void dfs2(int v = 1, int p = 0) {
	in[v] = ++pv;
	if (v == 1) top[v] = v;
	for (auto i: adj[v]) if (i != p) {
		top[i] = i == adj[v][0] ? top[v] : i;
		dfs2(i, v);
	}
	out[v] = pv;
}

ll query(int a, int b) {
    ll ret = 0;
    while(top[a] ^ top[b]){
        if(dep[top[a]] < dep[top[b]]) swap(a, b);
        int st = top[a];
        ret = max(ret, seg.query(in[st], in[a]));
        a = par[st];
    }
    if(dep[a] > dep[b]) swap(a, b);
    ret = max(ret, seg.query(in[a] + 1, in[b]));
    return ret;
}

void solve() {
	int N; cin >> N;
	vector<tuple<int, int, int>> c;

	for (int i = 0; i < N - 1; ++i) {
		int u, v, w; cin >> u >> v >> w;
		adj[u].push_back(v);
		adj[v].push_back(u);
		c.push_back(make_tuple(u, v, w));
	}

	dfs1(); dfs2();
	vector<ll> arr(N + 1);
	int etov[N];
	for (int i = 0; i < c.size(); ++i) {
		int u = get<0>(c[i]), v = get<1>(c[i]), w = get<2>(c[i]);
		if (dep[u] < dep[v]) swap(u, v);
		arr[in[u]] = w;
		etov[i + 1] = u;
	}
	seg.init(arr, N + 1);

	int M; cin >> M;
	while (M--) {
		int t; cin >> t;
		if (t == 1) {
			int i, c; cin >> i >> c;
			seg.update(in[etov[i]], c);
		} else {
			int u, v; cin >> u >> v;
			cout << query(u, v) << '\n';
		}
	}

}