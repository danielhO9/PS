#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
	ll lMax, rMax, max, sum;
};

Node merge(Node l, Node r) {
	Node ret;
	ret.lMax = max(l.lMax, l.sum + r.lMax);
	ret.rMax = max(r.rMax, r.sum + l.rMax);
	ret.max = max({l.max, r.max, l.rMax + r.lMax});
	ret.sum = l.sum + r.sum;
	return ret;
}

void init(vector<ll>& a, vector<Node>& tree, int node, int start, int end) {
	if (start == end) {
		tree[node] = {a[start], a[start], a[start], a[start]};
	}
	else {
		init(a, tree, node * 2, start, (start + end) / 2);
		init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}
}

void update(vector<ll>& a, vector<Node>& tree, int node, int start, int end, int index, ll val) {
	if (index < start || index > end) return;
	if (start == end) {
		a[index] = val;
		tree[node] = {val, val, val, val};
		return;
	}
	update(a, tree, node * 2, start, (start + end) / 2, index, val);
	update(a, tree, node * 2 + 1, (start + end) / 2 + 1, end, index, val);
	tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
}

Node query(vector<Node>& tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return {INT32_MIN, INT32_MIN, INT32_MIN, INT32_MIN};
	if (left <= start && end <= right) return tree[node];
	Node l = query(tree, node * 2, start, (start + end) / 2, left, right);
	Node r = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return merge(l, r);
}

void solve() {
	int N; cin >> N;
	// 0 ~ MAX_N - 1
	int MAX_N = N;
	vector<ll> arr(MAX_N); for (int i = 0; i < N; ++i) cin >> arr[i];
	int h = (int)ceil(log2(MAX_N));
	int tree_size = (1 << (h + 1));
	vector<Node> tree(tree_size);
	init(arr, tree, 1, 0, MAX_N - 1);
	int M; cin >> M;
	while (M--) {
		int i, j; cin >> i >> j; --i; --j;
		cout << query(tree, 1, 0, MAX_N - 1, i, j).max << '\n';
	}
	// update(arr, tree, 1, 0, MAX_N - 1, cur, 30);
	// query(tree, 1, 0, MAX_N - 1, 0, cur);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}