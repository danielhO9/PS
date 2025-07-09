#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_V = 100001;
vector<int> adj[MAX_V];

struct SegmentTree {
	vector<ll> arr;
	vector<ll> tree;
	static constexpr ll dValue = 0; // TODO
	int sz;

	ll merge(ll a, ll b) { return max(a, b); }
    SegmentTree() = default;
	SegmentTree(int sz): SegmentTree(vector<ll>(sz, dValue)) {}
	SegmentTree(const vector<ll>& a) {
		sz = a.size();
		arr = a;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
		init(1, 0, sz - 1);
	}
	void init(int node, int start, int end) {
		if (start == end) tree[node] = arr[start];
		else {
			int mid = (start + end) / 2;
			init(node * 2, start, mid);
			init(node * 2 + 1, mid + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}
	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			arr[index] = val;
			tree[node] = val;
			return;
		}
		int mid = (start + end) / 2;
		update(node * 2, start, mid, index, val);
		update(node * 2 + 1, mid + 1, end, index, val);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}
	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return dValue;
		if (left <= start && end <= right) return tree[node];
		int mid = (start + end) / 2;
		ll lsum = query(node * 2, start, mid, left, right);
		ll rsum = query(node * 2 + 1, mid + 1, end, left, right);
		return merge(lsum, rsum);
	}
	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }
	ll query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

template <class T>
struct HLD {
	T seg;
	vector<int> sz, dep, par, top, in, out;
	int cnt;

    HLD() = default;
	HLD(const vector<ll>& a): cnt(0) {
		int n = a.size();
		sz.resize(n); dep.resize(n);
		par.resize(n); top.resize(n);
		in.resize(n); out.resize(n);
		for (int i = 1; i < n; ++i) if (in[i] == 0) {
			top[i] = i;
			dfs1(i, -1);
			dfs2(i, -1);
		}
		vector<ll> arr(n);
        for (int i = 1; i < n; ++i) arr[in[i]] = a[i];
        seg = SegmentTree {arr};
	}
	void dfs1(int v, int p) {
		sz[v] = 1;
		for (auto& u: adj[v]) if (u != p) {
			dep[u] = dep[v] + 1;
			par[u] = v;
			dfs1(u, v);
			sz[v] += sz[u];
			if (sz[u] > sz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfs2(int v, int p) {
		in[v] = ++cnt;
		for (auto u: adj[v]) if (u != p) {
			top[u] = (u == adj[v][0] ? top[v] : u);
			dfs2(u, v);
		}
		out[v] = cnt;
	}
	void update(int v, ll val) { seg.update(in[v], val); }
	ll query(int a, int b) {
		ll ret = 0;
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) swap(a, b);
			int st = top[a];
			ret = seg.merge(ret, seg.query(in[st], in[a]));
			a = par[st];
		}
		if (dep[a] > dep[b]) swap(a, b);
		if (in[a] < in[b]) ret = seg.merge(ret, seg.query(in[a] + 1, in[b]));
		return ret;
	}
};

int par[MAX_V];
int N, M;
int tov[MAX_V];
ll weight[MAX_V];

void dfs(int v, int p) {
	par[v] = p;
	for (auto u: adj[v]) if (u != p) dfs(u, v);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
	vector<pair<int, int>> edge;
	for (int i = 0; i < N - 1; ++i) {
		int u, v; ll w; cin >> u >> v >> w;
		if (u > v) swap(u, v);
		adj[u].push_back(v);
		adj[v].push_back(u);
		weight[i] = w;
		edge.push_back(make_pair(u, v));
	}
	dfs(1, 0);
	for (int i = 0; i < edge.size(); ++i) {
		if (par[edge[i].first] == edge[i].second) tov[i] = edge[i].first;
		else tov[i] = edge[i].second;
	}
	vector<ll> a(N + 1);
	for (int i = 0; i < N - 1; ++i) a[tov[i]] = weight[i];
	HLD<SegmentTree> hld {a};
	cin >> M;
	while (M--) {
		ll t, u, v; cin >> t >> u >> v;
		if (t == 1) hld.update(tov[u-1], v);
		else cout << hld.query(u, v) << "\n";
	}
}