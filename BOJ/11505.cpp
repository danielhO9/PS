#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int N, M, K, MOD = 1000000007;

void init(vector<LL> &a, vector<LL> & tree, int node, int start, int end) {
	if (start == end) tree[node] = a[start];
	else {
		init(a, tree, node * 2, start, (start + end) / 2);
		init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
		tree[node] = tree[node * 2] * tree[node * 2 + 1];
		tree[node] %= MOD;
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
	tree[node] = tree[node * 2] * tree[node * 2 + 1];
	tree[node] %= MOD;
}

LL query(vector<LL> &tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 1;
	if (left <= start && end <= right) return tree[node];
	LL ltime = query(tree, node * 2, start, (start + end) / 2, left, right);
	LL rtime = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return (ltime * rtime) % MOD;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M >> K;
	vector<LL> arr(N);
	int h = (int)ceil(log2(N));
	int tree_size = (1 << (h + 1));
	vector<LL> tree(tree_size);
	M += K;
	for (int i = 0; i < N; ++i) cin >> arr[i];
	init(arr, tree, 1, 0, N - 1);
	LL a, b, c;
	while (M--) {
		cin >> a >> b >> c;
		if (a == 1) update(arr, tree, 1, 0, N - 1, b - 1, c);
		else cout << query(tree, 1, 0, N - 1, b - 1, c - 1) << '\n';
	}
}