#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct LazyPropagation {
	vector<ll> arr;
	vector<pair<ll, ll>> tree;
	vector<ll> lazy;
	ll sz;

	inline ll agg(ll a, ll b) { return a + b; }

	void init(vector<ll>& a) {
		sz = a.size();
		arr = a;
		ll h = (ll)ceil(log2(sz));
		ll tree_size = (1 << (h + 1));
		tree = vector<pair<ll, ll>>(tree_size);
		lazy = vector<ll>(tree_size);
		init_(1, 0, sz - 1);
	}

	void init_(ll node, ll start, ll end) {
		if (start == end) tree[node] = {arr[start], 1};
		else {
			init_(node * 2, start, (start + end) / 2);
			init_(node * 2 + 1, (start + end) / 2 + 1, end);

			if (tree[node * 2].first == tree[node * 2 + 1].first) {
				tree[node] = {tree[node * 2].first, tree[node * 2].second + tree[node * 2 + 1].second};
			} else tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
		}
	}

	void update_lazy(ll node, ll start, ll end) {
		if (lazy[node] != 0) {
			tree[node].first += lazy[node];
			if (start != end) {
				lazy[node * 2] = agg(lazy[node * 2], lazy[node]); // modify
				lazy[node * 2 + 1] = agg(lazy[node * 2 + 1], lazy[node]); // modify
			}
			lazy[node] = 0;
		}
	}

	void update_range(ll node, ll start, ll end, ll left, ll right, ll diff) {
		update_lazy(node, start, end);
		if (left > end || right < start) {
			return;
		}
		if (left <= start && end <= right) {
			tree[node].first += diff;
			if (start != end) {
				lazy[node * 2] = agg(lazy[node * 2], diff); // modify
				lazy[node * 2 + 1] = agg(lazy[node * 2 + 1], diff); // modify
			}
			return;
		}
		update_range(node * 2, start, (start + end) / 2, left, right, diff);
		update_range(node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff);
		if (tree[node * 2].first == tree[node * 2 + 1].first) {
			tree[node] = {tree[node * 2].first, tree[node * 2].second + tree[node * 2 + 1].second};
		} else tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
	}

	void update(ll left, ll right, ll val) { update_range(1, 0, sz - 1, left, right, val); }

	pair<ll, ll> query(ll node, ll start, ll end, ll left, ll right) {
		update_lazy(node, start, end);
		if (left > end || right < start) return {LLONG_MAX, 1}; // modify
		if (left <= start && end <= right) return tree[node];
		auto lsum = query(node * 2, start, (start + end) / 2, left, right);
		auto rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		if (tree[node * 2].first == tree[node * 2 + 1].first) {
			return {tree[node * 2].first, tree[node * 2].second + tree[node * 2 + 1].second};
		} else return min(tree[node * 2], tree[node * 2 + 1]);
	}

	pair<ll, ll> query(ll left, ll right) { return query(1, 0, sz - 1, left, right); }
} seg;

int N, Q;
vector<int> adj[100001];
int in[100001], out[100001], par[100001];
int way[100001];
int cur;

void dfs(int v, int p) {
	in[v] = ++cur;
	par[v] = p;
	for (auto u: adj[v]) if (u != p) {
		dfs(u, v);
	}
	out[v] = cur;
}

vector<tuple<int, int, int>> q;

void solve() {
	cin >> N;
	for (int i = 0; i < N - 1; ++i) {
		int U, V; string w;
		cin >> U >> w >> V;
		adj[U].push_back(V);
		adj[V].push_back(U);
		q.push_back({U, w == "--" ? 0 : (w == "->" ? 1 : -1), V});
	}
	cur = -1;
	dfs(1, 0);

	vector<ll> arr(N, 0);
	seg.init(arr);

	for (auto i: q) {
		int u = get<0>(i);
		int w = get<1>(i);
		int v = get<2>(i);
		if (par[u] == v) {
			swap(u, v); w *= -1; // par[v] = u, u -> v
		}
		way[v] = w;
		if (way[v] == 1) {
			seg.update(in[v], out[v], 1);
		} else if (way[v] == -1) {
			// seg.update(0, N - 1, 1);
			// seg.update(in[v], out[v], -1);
			seg.update(0, in[v] - 1, 1);
			seg.update(out[v] + 1, N - 1, 1);
		}

	}

	int Q; cin >> Q;
	while (Q--) {
		int u, v, w; string tmp;
		cin >> u >> tmp >> v;
		if (tmp == "--") w = 0;
		else if (tmp == "->") w = 1;
		else w = -1;
		
		if (par[u] == v) {
			swap(u, v); w *= -1;
		}
		if (way[v] == -1) {
			seg.update(0, in[v] - 1, -1);
			seg.update(out[v] + 1, N - 1, -1);
		} else if (way[v] == 1) {
			seg.update(in[v], out[v], -1);
		}

		way[v] = w;
		if (way[v] == 1) {
			seg.update(in[v], out[v], 1);
			// cout << in[v] << ' ' << out[v] << ' ' << 1 << '\n';
		}else if (way[v] == -1) {
			seg.update(0, in[v] - 1, 1);
			seg.update(out[v] + 1, N - 1, 1);
		}
		auto res = seg.query(0, N - 1);
		if (res.first == 0) cout << res.second << '\n';
		else cout << 0 << '\n';
	}
	

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}