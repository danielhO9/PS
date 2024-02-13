#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL MOD = 1e9 + 7;

void update(vector<LL>& tree, int node, int start, int end, int index, LL dif) {
	if (index < start || index > end) return;
	if (start == end) {
		tree[node] += dif; tree[node] %= MOD;
		return;
	}
	update(tree, node * 2, start, (start + end) / 2, index, dif);
	update(tree, node * 2 + 1, (start + end) / 2 + 1, end, index, dif);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
	tree[node] %= MOD;
}

LL query(vector<LL> &tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return tree[node];
	LL lsum = query(tree, node * 2, start, (start + end) / 2, left, right);
	LL rsum = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return (lsum + rsum) % MOD;
}

void solve() {
	int n; cin >> n;
	vector<LL> arr(n);
	for (int i = 0; i < n; ++i) {
		cin >> arr[i]; --arr[i];
	}
	int h = (int)ceil(log2(n));
	int tree_size = (1 << (h + 1));
	vector<LL> tree[11];
	for (int i = 0; i < 11; ++i) tree[i].resize(tree_size);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 11; ++j) {
			if (j == 0) update(tree[0], 1, 0, n - 1, arr[i], 1);
			else {
				LL dif = query(tree[j - 1], 1, 0, n - 1, 0, arr[i] - 1);
				update(tree[j], 1, 0, n - 1, arr[i], dif);
			}
		}
	}
	cout << query(tree[10], 1, 0, n - 1, 0, n - 1);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}