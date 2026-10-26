#include <bits/stdc++.h>
using namespace std;

void init(vector<int> &a, vector<int> & tree, int node, int start, int end) {
	if (start == end) tree[node] = a[start];
	else {
		init(a, tree, node * 2, start, (start + end) / 2);
		init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
		tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
	}
}

void update(vector<int> &a, vector<int>& tree, int node, int start, int end, int index, int val) {
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

int query(vector<int> &tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 30;
	if (left <= start && end <= right) return tree[node];
	int lsum = query(tree, node * 2, start, (start + end) / 2, left, right);
	int rsum = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return min(lsum, rsum);
}

void solve() {
	int n, m; cin >> n >> m;
	string s, t; cin >> s >> t;
	bool visited[26];
	for (int i = 0; i < m; ++i) visited[t[i] - 'a'] = true;
	deque<int> index[26];
	for (int i = 0; i < n; ++i) {
		if (visited[s[i] - 'a']) index[s[i] - 'a'].push_back(i);
	}
	vector<int> arr(n);
	int h = (int)ceil(log2(n));
	int tree_size = (1 << (h + 1));
	vector<int> tree(tree_size);
	for (int i = 0; i < n; ++i) {
		if (visited[s[i] - 'a']) arr[i] = s[i] - 'a';
		else arr[i] = 30;
	}
	init(arr, tree, 1, 0, n - 1);
	for (int i = 0; i < m; ++i) {
		if (index[t[i] - 'a'].empty()) {
			cout << "NO" << '\n';
			return;
		}
		int cur = index[t[i] - 'a'].front();
		int val = query(tree, 1, 0, n - 1, 0, cur);
		if (val == t[i] - 'a') {
		} else {
			for (int j = 0; j < cur; ++j) {
				if (arr[j] < arr[cur]) {
					index[arr[j]].pop_front();
					update(arr, tree, 1, 0, n - 1, j, 30);
				}
			}
		}
		index[t[i] - 'a'].pop_front();
		update(arr, tree, 1, 0, n - 1, cur, 30);
	}
	cout << "YES" << '\n';
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}