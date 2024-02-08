#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int N, M;

void init(vector<LL> &a, vector<LL> & tree, int node, int start, int end) {
	if (start == end) tree[node] = a[start];
	else {
		init(a, tree, node * 2, start, (start + end) / 2);
		init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
		tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
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
	tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
}

LL query(vector<LL> &tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 1e9 + 1;
	if (left <= start && end <= right) return tree[node];
	LL lmin = query(tree, node * 2, start, (start + end) / 2, left, right);
	LL rmin = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return min(lmin, rmin);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	vector<LL> arr(N);
	int h = (int)ceil(log2(N));
	int tree_size = (1 << (h + 1));
	vector<LL> tree(tree_size);
	for (int i = 0; i < N; ++i) cin >> arr[i];
	cin >> M;
	init(arr, tree, 1, 0, N - 1);
	LL a, b, c;
	while (M--) {
		cin >> a >> b >> c;
		if (a == 1) update(arr, tree, 1, 0, N - 1, b - 1, c);
		else cout << query(tree, 1, 0, N - 1, b - 1, c - 1) << '\n';
	}
}