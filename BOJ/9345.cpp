#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void init(vector<ll> &a, vector<ll> & tree, int node, int start, int end, int& type) {
	if (start == end) tree[node] = a[start];
	else {
		init(a, tree, node * 2, start, (start + end) / 2, type);
		init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end, type);
		if (type == 0) tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
		else tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
	}
}

void update(vector<ll>& tree, int node, int start, int end, int index, ll val, int& type) {
	if (index < start || index > end) return;
	if (start == end) {
		tree[node] = val;
		return;
	}
	update(tree, node * 2, start, (start + end) / 2, index, val, type);
	update(tree, node * 2 + 1, (start + end) / 2 + 1, end, index, val, type);
	if (type == 0) tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
	else tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}

ll query(vector<ll> &tree, int node, int start, int end, int left, int right, int& type) {
	if (left > end || right < start) {
		if (type == 0) return LLONG_MAX;
		else return LLONG_MIN;
	}
	if (left <= start && end <= right) return tree[node];
	ll lsum = query(tree, node * 2, start, (start + end) / 2, left, right, type);
	ll rsum = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right, type);
	if (type == 0) return min(lsum, rsum);
	else return max(lsum, rsum);
}

void solve() {
	int N, K; cin >> N >> K;
	// 0 ~ n - 1
	vector<ll> arr(N); for (int i = 0; i < N; ++i) arr[i] = i;
	int h = (int)ceil(log2(N));
	int tree_size = (1 << (h + 1));
	vector<vector<ll>> tree(2, vector<ll>(tree_size));
	for (int i = 0; i < 2; ++i) init(arr, tree[i], 1, 0, N - 1, i);
	while (K--) {
		int Q, A, B; cin >> Q >> A >> B;
		if (Q == 0) {
			for (int i = 0; i < 2; ++i) {
				update(tree[i], 1, 0, N - 1, A, arr[B], i);
				update(tree[i], 1, 0, N - 1, B, arr[A], i);
			}
			swap(arr[A], arr[B]);
		} else {
			int temp = 0;
			ll min_ = query(tree[0], 1, 0, N - 1, A, B, temp);
			temp = 1;
			ll max_ = query(tree[1], 1, 0, N - 1, A, B, temp);
			if (min_ != A || max_ != B) {
				cout << "NO\n";
			} else {
				cout << "YES\n";
			}
		}
	}
	// update(arr, tree, 1, 0, n - 1, cur, 30);
	// query(tree, 1, 0, n - 1, 0, cur);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}