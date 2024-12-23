#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
// https://justicehui.github.io/hard-algorithm/2020/01/24/hld/

const int MAX_V = 500001;
const ll MOD = (1ll << 32);
vector<int> adj[MAX_V];

inline ll agg(ll a, ll b) { return (a + b) % MOD; }

struct LazyPropagation {
	vector<ll> arr;
	vector<ll> tree;
	vector<ll> lazy_a, lazy_b;
	ll sz;

	void init(vector<ll>& a) {
		sz = a.size();
		arr = a;
		ll h = (ll)ceil(log2(sz));
		ll tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
		lazy_a = vector<ll>(tree_size, 1);
		lazy_b = vector<ll>(tree_size, 0);
		init_(1, 0, sz - 1);
	}

	void init_(ll node, ll start, ll end) {
		if (start == end) tree[node] = arr[start];
		else {
			init_(node * 2, start, (start + end) / 2);
			init_(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = agg(tree[node * 2], tree[node * 2 + 1]);
		}
	}

	void update_lazy(ll node, ll start, ll end) {
		if (lazy_a[node] != 1 || lazy_b[node] != 0) {
			tree[node] = (tree[node] * lazy_a[node] + (end - start + 1) * lazy_b[node]) % MOD; // modify
			if (start != end) {
				lazy_a[node * 2] = lazy_a[node * 2] * lazy_a[node] % MOD; // modify
				lazy_b[node * 2] = ((lazy_b[node * 2] * lazy_a[node]) % MOD + lazy_b[node]) % MOD;
				lazy_a[node * 2 + 1] = lazy_a[node * 2 + 1] * lazy_a[node] % MOD; // modify
				lazy_b[node * 2 + 1] = ((lazy_b[node * 2 + 1] * lazy_a[node] % MOD) + lazy_b[node]) % MOD;
			}
			lazy_a[node] = 1;
			lazy_b[node] = 0;
		}
	}

	void update_range(ll node, ll start, ll end, ll left, ll right, ll diff_a, ll diff_b) {
		update_lazy(node, start, end);
		if (left > end || right < start) {
			return;
		}
		if (left <= start && end <= right) {
			tree[node] = (tree[node] * diff_a + (end - start + 1) * diff_b) % MOD; // modify
			if (start != end) {
				lazy_a[node * 2] = lazy_a[node * 2] * diff_a % MOD; // modify
				lazy_b[node * 2] = ((lazy_b[node * 2] * diff_a) % MOD + diff_b) % MOD;
				lazy_a[node * 2 + 1] = lazy_a[node * 2 + 1] * diff_a % MOD; // modify
				lazy_b[node * 2 + 1] = ((lazy_b[node * 2 + 1] * diff_a % MOD) + diff_b) % MOD;
			}
			return;
		}
		update_range(node * 2, start, (start + end) / 2, left, right, diff_a, diff_b);
		update_range(node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff_a, diff_b);
		tree[node] = agg(tree[node * 2], tree[node * 2 + 1]);
	}

	void update(ll left, ll right, ll val_a, ll val_b) { update_range(1, 0, sz - 1, left, right, val_a, val_b); }

	ll query(ll node, ll start, ll end, ll left, ll right) {
		update_lazy(node, start, end);
		if (left > end || right < start) return 0; // modify
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return agg(lsum, rsum);
	}

	ll query(ll left, ll right) { return query(1, 0, sz - 1, left, right); }
} seg;

struct HLD {
	LazyPropagation seg;
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

	void update(int a, int b, ll val_a, ll val_b) {
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) swap(a, b);
			int st = top[a];
			seg.update(in[st], in[a], val_a, val_b);
			a = par[st];
		}
		if(dep[a] > dep[b]) swap(a, b);
		seg.update(in[a], in[b], val_a, val_b);
	}

	void update_subtree(int v, ll val_a, ll val_b) { 
		// cout << "update subtree: " << in[v] << ' ' << out[v] << '\n';
		seg.update(in[v], out[v], val_a, val_b); }

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

	ll query_subtree(int v) { return seg.query(in[v], out[v]); };
};

int N, Q;

void solve() {
	cin >> N >> Q;
	for (int i = 0; i < N - 1; ++i) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	vector<ll> a(N + 1, 0ll);
	HLD hld; hld.init(a);
	while (Q--) {
		int t; ll x, y, v;
		cin >> t;
		if (t == 1) {
			cin >> x >> v;
			hld.update_subtree(x, 1, v);
		}
		if (t == 2) {
			cin >> x >> y >> v;
			hld.update(x, y, 1, v);
		}
		if (t == 3) {
			cin >> x >> v;
			hld.update_subtree(x, v, 0);
		}
		if (t == 4) {
			cin >> x >> y >> v;
			hld.update(x, y, v, 0);
		}
		if (t == 5) {
			cin >> x;
			cout << hld.query_subtree(x) << '\n';
		}
		if (t == 6) {
			cin >> x >> y;
			cout << hld.query(x, y) << '\n';
		}
		// for (int i = 1; i <= N; ++i) cout << hld.query(i, i) << ' ';
		// cout << '\n';
		// cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}