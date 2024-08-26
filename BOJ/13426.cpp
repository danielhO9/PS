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
			tree[node] = tree[node * 2] + tree[node * 2 + 1];
		}
	}
	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			arr[index] += val;
			tree[node] += val;
			return;
		}
		update(node * 2, start, (start + end) / 2, index, val);
		update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
	void update(int index, ll val) {
		update(1, 0, sz - 1, index, val);
	}
	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return 0;
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return lsum + rsum;
	}
	ll query(int left, int right) {
		return query(1, 0, sz - 1, left, right);
	}
} seg;

int N, K;
int V[1001];
vector<int> adj[1001];
int ans = 1e6;
bool used[1001];

void dfs(int v, int val, int cnt) {
	// cout << v << ' ' << val << ' ' << cnt << '\n';
	int dif = 0;
	if (V[v] >= 2) dif = seg.query(1, V[v] - 1);
	if (val + dif >= ans) return;
	seg.update(V[v], 1);
	used[v] = true;
	if (cnt + 1 >= K) {
		ans = min(ans, val + dif);
	}
	for (auto u: adj[v]) if (!used[u]) {
		dfs(u, val + dif, cnt + 1);
	}
	used[v] = false;
	seg.update(V[v], -1);
}

void solve() {
	cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for (int i = 1; i <= N; ++i) cin >> V[i];
	int MAX_N = 1001;
	vector<ll> arr(MAX_N);
	seg.init(arr, MAX_N);
	for (int i = 1; i <= N; ++i) dfs(i, 0, 0);
	if (ans == 1e6) cout << -1;
	else cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}