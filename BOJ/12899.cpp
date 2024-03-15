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

ll query(vector<ll> &tree, int node, int start, int end, ll k) {
	if (start == end) return start;
	if (tree[node * 2] >= k) return query(tree, node * 2, start, (start + end) / 2, k);
	else return query(tree, node * 2 + 1, (start + end) / 2 + 1, end, k - tree[node * 2]);
	// if (left > end || right < start) return 0;
	// if (left <= start && end <= right) return tree[node];
	// ll lsum = query(tree, node * 2, start, (start + end) / 2, left, right);
	// ll rsum = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	// return lsum + rsum;
}

void solve() {
	int n; n = 2e6 + 1;
	// 0 ~ n - 1
	vector<ll> arr(n, 0ll);
	int h = (int)ceil(log2(n));
	int tree_size = (1 << (h + 1));
	vector<ll> tree(tree_size);
	int N; cin >> N;
	while (N--) {
		int T, X; cin >> T >> X;
		if (T == 1) {
			update(arr, tree, 1, 0, n - 1, X, arr[X] + 1);
		} else {
			ll to_erase = query(tree, 1, 0, n - 1, X);
			update(arr, tree, 1, 0, n - 1, to_erase, arr[to_erase] - 1ll);
			cout << to_erase << '\n';
		}
	}
	// init(arr, tree, 1, 0, n - 1);
	// update(arr, tree, 1, 0, n - 1, cur, 30);
	// query(tree, 1, 0, n - 1, 0, cur);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}