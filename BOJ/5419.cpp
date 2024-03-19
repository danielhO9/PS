#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void init(vector<ll> &a, vector<ll> & tree, int node, int start, int end) {
	if (start == end) tree[node] = a[start];
	else {
		init(a, tree, node * 2, start, (start + end) / 2);
		init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
}

void update(vector<ll> &a, vector<ll>& tree, int node, int start, int end, int index, ll val) {
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

ll query(vector<ll> &tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return tree[node];
	ll lsum = query(tree, node * 2, start, (start + end) / 2, left, right);
	ll rsum = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return lsum + rsum;
}

void solve() {
	int n; cin >> n;
	vector<pair<int, int>> V(n);
	for (int i = 0; i < n; ++i) cin >> V[i].first >> V[i].second;
	vector<int> ord(n), xord(n); for (int i = 0; i < n; ++i) { ord[i] = i; xord[i] = i; }
	sort(ord.begin(), ord.end(), [&V](int& a, int& b) {
		if (V[a].second == V[b].second) { return V[a].first < V[b].first; }
		return V[a].second > V[b].second;
	});
	sort(xord.begin(), xord.end(), [&V](int& a, int& b) {
		if (V[a].first == V[b].first) { return V[a].second > V[b].second; }
		return V[a].first < V[b].first;
	});
	vector<int> xval(n); for (int i = 0; i < n; ++i) xval[xord[i]] = i;
	// 0 ~ n - 1
	vector<ll> arr(n);
	int h = (int)ceil(log2(n));
	int tree_size = (1 << (h + 1));
	vector<ll> tree(tree_size);
	ll ans = 0;
	for (int i = 0; i < n; ++i) {
		int here = ord[i];
		ans += query(tree, 1, 0, n - 1, 0, xval[here] - 1);
		update(arr, tree, 1, 0, n - 1, xval[here], 1);
	}
	cout << ans << '\n';
	// init(arr, tree, 1, 0, n - 1);
	// update(arr, tree, 1, 0, n - 1, cur, 30);
	// query(tree, 1, 0, n - 1, 0, cur);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}