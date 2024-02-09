#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void init(vector<LL> &a, vector<LL> & tree, int node, int start, int end) {
	if (start == end) tree[node] = a[start];
	else {
		init(a, tree, node * 2, start, (start + end) / 2);
		init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
}

void update(vector<LL> &a, vector<LL>& tree, int node, int start, int end, int index, LL val) {
	if (index < start || index > end) return;
	if (start == end) {
		a[index] = val;
		tree[node] = val;
		return;
	}
	update(a, tree, node * 2, start, (start + end) / 2, index, val);
	update(a, tree, node * 2 + 1, (start + end) / 2 + 1, end, index, val);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

LL query(vector<LL> &tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return tree[node];
	LL lsum = query(tree, node * 2, start, (start + end) / 2, left, right);
	LL rsum = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return lsum + rsum;
}

void dfs(int v, int p, vector<vector<int>>& adj, int& cnt, vector<int>& in, vector<int>& out, vector<LL>& dep) {
	in[v] = ++cnt; dep[v] = dep[p] + 1;
	for (auto u: adj[v]) if (u != p) dfs(u, v, adj, cnt, in, out, dep);
	out[v] = cnt;
}

void solve() {
	int n, c; cin >> n >> c;
	vector<vector<int>> adj(n + 1);
	for (int i = 0; i < n - 1; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<LL> dep(n + 1);
	vector<int> in(n + 1), out(n + 1); int cnt = -1;
	dfs(c, 0, adj, cnt, in, out, dep);
	vector<LL> arr(n);
	int h = (int)ceil(log2(n));
	int tree_size = (1 << (h + 1));
	vector<LL> tree(tree_size);
	int q; cin >> q;
	for (int i = 0; i < q; ++i) {
		int what; cin >> what;
		if (what == 1) {
			int A; cin >> A;
			update(arr, tree, 1, 0, n - 1, in[A], arr[in[A]] + 1);
		} else {
			int A; cin >> A;
			LL q = query(tree, 1, 0, n - 1, in[A], out[A]);
			cout << q * dep[A] << '\n';
		}
	}
	// update(arr, tree, 1, 0, n - 1, cur, 30);
	// query(tree, 1, 0, n - 1, 0, cur);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}