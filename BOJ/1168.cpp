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

ll query1(vector<ll> &tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return tree[node];
	ll lsum = query1(tree, node * 2, start, (start + end) / 2, left, right);
	ll rsum = query1(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return lsum + rsum;
}

ll query2(vector<ll> &tree, int node, int start, int end, ll k) {
	if (start == end) return start;
	if (tree[node * 2] >= k) return query2(tree, node * 2, start, (start + end) / 2, k);
	else return query2(tree, node * 2 + 1, (start + end) / 2 + 1, end, k - tree[node * 2]);
	// if (left > end || right < start) return 0;
	// if (left <= start && end <= right) return tree[node];
	// ll lsum = query(tree, node * 2, start, (start + end) / 2, left, right);
	// ll rsum = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	// return lsum + rsum;
}

void solve() {
	int n, N, K; cin >> N >> K; n = N + 1;
	// 0 ~ n - 1
	vector<ll> arr(n); for (int i = 1; i <= N; ++i) arr[i] = 1;
	int h = (int)ceil(log2(n));
	int tree_size = (1 << (h + 1));
	vector<ll> tree(tree_size);
	init(arr, tree, 1, 0, n - 1);
	cout << "<"; ll value = 0ll;
	for (int i = 0; i < N; ++i) {
		ll prefix = query1(tree, 1, 0, n - 1, 0, value);
		ll suffix = query1(tree, 1, 0, n - 1, value, n - 1);
		if (suffix >= K) {
			value = query2(tree, 1, 0, n - 1, K + prefix);
			update(arr, tree, 1, 0, n - 1, value, 0);
		} else {
			value = query2(tree, 1, 0, n - 1, (K - suffix) % (suffix + prefix) == 0 ? (suffix + prefix) : (K - suffix) % (suffix + prefix));
			update(arr, tree, 1, 0, n - 1, value, 0);
		}
		cout << value;
		if (i != N - 1) cout << ", ";
	}
	// update(arr, tree, 1, 0, n - 1, cur, 30);
	// query(tree, 1, 0, n - 1, 0, cur);
	cout << ">";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}