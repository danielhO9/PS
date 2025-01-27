#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SegmentTree {
	vector<ll> arr;
	vector<ll> tree;
	int sz;

	inline ll merge(ll a, ll b) { return max(a, b); }

	void init(vector<ll> &a) {
		sz = a.size();
		arr = a;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
		init(1, 0, sz - 1);
	}

	void init(int node, int start, int end) {
		if (start == end)
			tree[node] = arr[start];
		else {
			init(node * 2, start, (start + end) / 2);
			init(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}

	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end)
			return;
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
		if (left > end || right < start)
			return -1; // modify
		if (left <= start && end <= right)
			return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return merge(lsum, rsum);
	}

	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }

	ll query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

int n;
vector<int> adj[400001];
vector<int> widx[400001];
int w[400001], l[400001], r[400001];
int cnt;

void dfs(int v, int p) {
	l[v] = ++cnt;
	for (auto u : adj[v])
		if (u != p) {
			dfs(u, v);
		}
	r[v] = cnt;
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i)
		adj[i].clear();
	for (int i = 1; i <= n; ++i)
		cin >> w[i];
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	cnt = -1;
	dfs(1, 0);
	// for (int i = 1; i <= n; ++i) {
	// 	cout << l[i] << ' ' << r[i] << '\n';
	// }
	vector<int> ans;
	vector<ll> arr(n, -1);
	SegmentTree seg;
	seg.init(arr);
	for (int i = 1; i <= n; ++i)
		widx[w[i]].push_back(i);
	for (int curw = n; curw >= 1; --curw) {
		if (widx[curw].empty())
			continue;
		int sz = widx[curw].size();
		vector<int> res;
		for (int i = 0; i < sz; ++i) {
			// cout << widx[curw][i] << '\n';
			ll lll = l[widx[curw][i]], rrr = r[widx[curw][i]];
			// cout << lll << ' ' << rrr << ' ';
			ll val = -1;
			if (0 <= lll - 1)
				val = max(val, seg.query(0, lll - 1));
			if (rrr + 1 <= n - 1)
				val = max(val, seg.query(rrr + 1, n - 1));
			// cout << val << '\n';
			if (val == -1)
				res.push_back(0);
			else if (val == 0)
				res.push_back(1);
			else
				res.push_back(0);
		}
		for (int i = 0; i < sz; ++i) {
			seg.update(l[widx[curw][i]], res[i]);
			if (res[i] == 1)
				ans.push_back(widx[curw][i]);
		}
	}
	cout << ans.size() << ' ';
	for (auto i: ans) cout << i << ' ';
	cout << '\n';

	for (int i = 1; i <= n; ++i)
		widx[w[i]].clear();
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
}