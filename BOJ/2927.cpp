#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// https://justicehui.github.io/hard-algorithm/2020/01/24/hld/

const int MAX_V = 30001;
vector<int> adj[MAX_V];

inline ll agg(ll a, ll b) { return a + b; }

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
			tree[node] = agg(tree[node * 2], tree[node * 2 + 1]);
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
		tree[node] = agg(tree[node * 2], tree[node * 2 + 1]);
	}
	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }
	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return 0; // modify
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return agg(lsum, rsum);
	}
	ll query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

// root: 1
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
			ret = agg(ret, seg.query(in[st], in[a]));
			a = par[st];
		}
		if(dep[a] > dep[b]) swap(a, b);
		ret = agg(ret, seg.query(in[a], in[b]));
		return ret;
	}
};

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

struct Query {
	int t, a, b;
};

int N, Q;
vector<Query> q;
vector<string> ans;

void solve() {
	cin >> N;
	vector<ll> a(N + 1);
	for (int i = 1; i <= N; ++i) cin >> a[i];
	UF uf; uf.init(N + 1);
	cin >> Q;
	for (int i = 0; i < Q; ++i) {
		int t, a, b;
		string tmp; cin >> tmp >> a >> b;
		if (tmp == "bridge") {
			t = 0;
			if (uf.find(a) == uf.find(b)) {
				ans.push_back("no");
			} else {
				ans.push_back("yes");
				adj[a].push_back(b);
				adj[b].push_back(a);
				uf.union_path(a, b);
			}
		} else if (tmp == "penguins") {
			t = 1;
			ans.push_back("");
		}
		else {
			t = 2;
			if (uf.find(a) != uf.find(b)) {
				ans.push_back("impossible");
			} else {
				ans.push_back("");
			}
		}
		q.push_back({t, a, b});
	}
	HLD hld;
	hld.init(a);
	for (int i = 0; i < Q; ++i) {
		if (q[i].t == 0) {
			cout << ans[i] << '\n';
			continue;
		}
		if (q[i].t == 1) hld.update(q[i].a, q[i].b);
		else {
			if (ans[i] == "") ans[i] = to_string(hld.query(q[i].a, q[i].b));
			cout << ans[i] << '\n';
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}