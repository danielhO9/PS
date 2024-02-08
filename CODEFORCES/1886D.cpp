#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL MOD = 998244353;

LL n, m; string s;

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
	LL lsum = query(tree, node * 2, start, (start + end) / 2, left, right);
	LL rsum = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return (lsum * rsum) % MOD;
}

void solve() {
	cin >> n >> m; cin >> s;
	vector<LL> arr(n);
	int h = (int)ceil(log2(n));
	int tree_size = (1 << (h + 1));
	vector<LL> tree(tree_size);
	for (int i = 0; i < n - 1; ++i) {
		if (s[i] == '?') arr[i] = i;
		else arr[i] = 1;
	}
	init(arr, tree, 1, 0, n - 2);
	cout << query(tree, 1, 0, n - 2, 0, n - 2) << '\n';
	while (m--) {
		int i; char c; cin >> i >> c; --i;
		update(arr, tree, 1, 0, n - 2, i, c == '?' ? i : 1);
		cout << query(tree, 1, 0, n - 2, 0, n - 2) << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}