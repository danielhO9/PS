#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
	ll lmx, rmx, mx, sm;

	Node() = default;
	Node(ll x, ll sz) {
		if (x > 0) lmx = rmx = mx = sm = x * sz;
		else {
			lmx = rmx = mx = 0;
			sm = x * sz;
		}
	}
};

struct SegmentTree {
	vector<ll> arr;
	vector<ll> lazy;
	vector<Node> tree;
	static constexpr ll dValue = 10001;
	int sz;

	inline Node merge(const Node& l, const Node& r) {
		Node ret{};
		ret.lmx = max(l.lmx, l.sm + r.lmx);
		ret.rmx = max(r.rmx, r.sm + l.rmx);
		ret.mx = max({l.mx, r.mx, l.rmx + r.lmx});
		ret.sm = l.sm + r.sm;
		return ret;
	}
	SegmentTree() = default;
	SegmentTree(const vector<ll>& a) {
		sz = a.size();
		arr = a;
		int h = (int) ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<Node>(tree_size);
		lazy = vector<ll>(tree_size, dValue);
		init(1, 0, sz - 1);
	}
	void init(int node, int start, int end) {
		if (start == end) tree[node] = Node {arr[start], 1};
		else {
			int mid = (start + end) / 2;
			init(node * 2, start, mid);
			init(node * 2 + 1, mid + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}
	void update_lazy(ll node, ll start, ll end) {
		if (lazy[node] != dValue) {
			tree[node] = Node {lazy[node], end - start + 1};
			if (start != end) {
				lazy[node * 2] = lazy[node];
				lazy[node * 2 + 1] = lazy[node];
			}
			lazy[node] = dValue;
		}
	}
	void update_range(ll node, ll start, ll end, ll left, ll right, ll diff) {
		update_lazy(node, start, end);
		if (left > end || right < start) return;
		if (left <= start && end <= right) {
			tree[node] = Node {diff, end - start + 1};
			if (start != end) {
				lazy[node * 2] = diff;
				lazy[node * 2 + 1] = diff;
			}
			return;
		}
		int mid = (start + end) / 2;
		update_range(node * 2, start, mid, left, right, diff);
		update_range(node * 2 + 1, mid + 1, end, left, right, diff);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}
	Node query(int node, int start, int end, int left, int right) {
		update_lazy(node, start, end);
		if (left > end || right < start) return Node {0, 1};
		if (left <= start && end <= right) return tree[node];
		int mid = (start + end) / 2;
		Node l = query(node * 2, start, mid, left, right);
		Node r = query(node * 2 + 1, mid + 1, end, left, right);
		return merge(l, r);
	}
	void update_range(int left, int right, ll val) { update_range(1, 0, sz - 1, left, right, val); }
	Node query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

const int MAX_V = 100001;
vector<int> adj[MAX_V];

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
        seg = T {arr};
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
	void update(int a, int b, ll w) {
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) swap(a, b);
			int st = top[a];
			seg.update_range(in[st], in[a], w);
			a = par[st];
		}
		if (dep[a] > dep[b]) swap(a, b);
		seg.update_range(in[a], in[b], w);
	}
	Node query(int a, int b) {
		vector<Node> l, r;
		while (top[a] != top[b]) {
			if (dep[top[a]] > dep[top[b]]) {
				int st = top[a];
				l.push_back(seg.query(in[st], in[a]));
				swap(l.back().lmx, l.back().rmx);
				a = par[st];
			} else {
				int st = top[b];
				r.push_back(seg.query(in[st], in[b]));
				b = par[st];
			}
		}
		if (dep[a] < dep[b]) l.push_back(seg.query(in[a], in[b]));
		else {
			l.push_back(seg.query(in[b], in[a]));
			swap(l.back().lmx, l.back().rmx);
		}
		Node ret {0, 1};
		for (auto i: l) ret = seg.merge(ret, i);
		reverse(r.begin(), r.end());
		for (auto i: r) ret = seg.merge(ret, i);
		// for (auto i: l) cout << i.lmx << ' ' << i.rmx << ' ' << i.mx << ' ' << i.sm << '\n';
		// for (auto i: r) cout << i.lmx << ' ' << i.rmx << ' ' << i.mx << ' ' << i.sm << '\n';	
		return ret;
	}
};

/*
3 -3 9 -4 0
3 -3 9 9 9
9 9 9 -3 3
*/

int N, M;
constexpr ll SegmentTree::dValue;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	vector<ll> a(N + 1);
	for (int i = 1; i <= N; ++i) cin >> a[i];
	for (int i = 0; i < N - 1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	HLD<SegmentTree> hld {a};
	cin >> M;
	while (M--) {
		int t, u, v; cin >> t >> u >> v;
		if (t == 1) cout << hld.query(u, v).mx << '\n';
		else {
			ll w; cin >> w;
			hld.update(u, v, w);
		}
	}
	// for (int i = 1; i <= N; ++i) cout << hld.seg.query(hld.in[i], hld.in[i]).sm << ' ';
}