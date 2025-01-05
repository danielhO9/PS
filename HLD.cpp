#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// https://justicehui.github.io/hard-algorithm/2020/01/24/hld/

const int MAX_V = 30001;
vector<int> adj[MAX_V];

inline ll merge(ll a, ll b) { return a + b; }

struct SegmentTree {
	vector<ll> arr;
	vector<ll> tree;
	int sz;

	void init(vector<ll>& a) {
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
			init(node * 2, start, (start + end) / 2);
			init(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}
	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			arr[index] = val; // modify
			tree[node] = val; // modify
			return;
		}
		update(node * 2, start, (start + end) / 2, index, val);
		update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}
	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return 0; // modify
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return merge(lsum, rsum);
	}
	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }
	ll query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

struct HLD {
	SegmentTree seg;
	vector<int> sz, dep, par, top, in, out;
	int cnt, rt;

	void dfs1(int v, int p) {
		sz[v] = 1;
		for (auto& i: adj[v]) if (i != p) {
			dep[i] = dep[v] + 1; par[i] = v;
			dfs1(i, v); sz[v] += sz[i];
			if (sz[i] > sz[adj[v][0]]) swap(i, adj[v][0]);
		}
	}

	void dfs2(int v, int p) {
		in[v] = ++cnt;
		if (v == 1) top[v] = v;
		for (auto i: adj[v]) if (i != p) {
			top[i] = (i == adj[v][0] ? top[v] : i);
			dfs2(i, v);
		}
		out[v] = cnt;
	}

	void init(vector<ll>& arr) {
		int _sz = arr.size();
		sz.resize(_sz); dep.resize(_sz);
		par.resize(_sz); top.resize(_sz);
		in.resize(_sz); out.resize(_sz);
		cnt = 0;
		for (int i = 1; i < arr.size(); ++i) if (in[i] == 0) {
			dfs1(i, -1); dfs2(i, -1);
		}

		vector<ll> a(arr.size());
		for (int i = 0; i < arr.size(); ++i) a[in[i]] = arr[i];
		seg.init(a);
	}

	void update(int v, ll val) { seg.update(in[v], val); }

	ll query(int a, int b) {
		ll ret = 0;
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) swap(a, b);
			int st = top[a];
			ret = merge(ret, seg.query(in[st], in[a]));
			a = par[st];
		}
		if(dep[a] > dep[b]) swap(a, b);
		ret = merge(ret, seg.query(in[a], in[b]));
		return ret;
	}
};