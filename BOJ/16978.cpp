#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void init(vector<LL> &a, vector<LL> & tree, int node, int start, int end) {
	if (start == end) tree[node] = a[start];
	else {
		init(a, tree, node * 2, start, (start + end) / 2);
		init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
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
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

LL query(vector<LL> &tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return tree[node];
	LL lsum = query(tree, node * 2, start, (start + end) / 2, left, right);
	LL rsum = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return lsum + rsum;
}

void solve() {
	int n; cin >> n;
	vector<LL> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
	int h = (int)ceil(log2(n));
	int tree_size = (1 << (h + 1));
	vector<LL> tree(tree_size);
	init(arr, tree, 1, 0, n - 1);
	int m; cin >> m;
	vector<pair<int, LL>> off1; off1.push_back({0, arr[0]});
	vector<vector<pair<pair<int, int>, int>>> off2; off2.push_back({});
	vector<LL> ans(m, -1);
	for (int i = 0; i < m; ++i) {
		int what; cin >> what;
		if (what == 1) {
			int ind; LL v; cin >> ind >> v; --ind;
			off1.push_back({ind, v});
			off2.push_back({});
		} else {
			int k, l, r; cin >> k >> l >> r; --l; --r;
			off2[k].push_back({{l, r}, i}); 
		}
	}
	for (int i = 0; i < off1.size(); ++i) {
		auto upd = off1[i];
		update(arr, tree, 1, 0, n - 1, upd.first, upd.second);
		for (auto que: off2[i]) {
			ans[que.second] = query(tree, 1, 0, n - 1, que.first.first, que.first.second);
		}
	}
	for (auto i: ans) if (i > 0) cout << i << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}