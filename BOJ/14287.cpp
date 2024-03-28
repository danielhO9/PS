#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void init(vector<ll>& a, vector<ll>& tree, int node, int start, int end) {
	if (start == end) tree[node] = a[start];
	else {
		init(a, tree, node * 2, start, (start + end) / 2);
		init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
}

void update(vector<ll>& a, vector<ll>& tree, int node, int start, int end, int index, ll val) {
	if (index < start || index > end) return;
	if (start == end) {
		a[index] += val;
		tree[node] += val;
		return;
	}
	update(a, tree, node * 2, start, (start + end) / 2, index, val);
	update(a, tree, node * 2 + 1, (start + end) / 2 + 1, end, index, val);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(vector<ll>& tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return tree[node];
	ll lsum = query(tree, node * 2, start, (start + end) / 2, left, right);
	ll rsum = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return lsum + rsum;
}

int in[100001], out[100001], cnt = -1;
vector<int> adj[100001];
void dfs(int v, int p) {
	in[v] = ++cnt;
	for (int u: adj[v]) if (u != p) dfs(u, v);
	out[v] = cnt;
}

void solve() {
	int n, m; cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		int p; cin >> p;
		if (p == -1) continue;
		adj[i].push_back(p);
		adj[p].push_back(i);
	}
	dfs(1, 0);
	int MAX_N = n + 1;
	vector<ll> arr(MAX_N);
	int h = (int)ceil(log2(MAX_N));
	int tree_size = (1 << (h + 1));
	vector<ll> tree(tree_size);
	while (m--) {
		int what; cin >> what;
		if (what == 1) {
			ll i, w; cin >> i >> w;
			update(arr, tree, 1, 0, MAX_N - 1, in[i], w);
		} else {
			int i; cin >> i;
			cout << query(tree, 1, 0, MAX_N - 1, in[i], out[i]) << '\n';
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}