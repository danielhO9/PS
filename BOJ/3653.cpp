#include <bits/stdc++.h>
using namespace std;

int n, m, arr[200000], tree[524288];
unordered_map<int, int> M;

void init(int node, int start, int end) {
	if (start == end) tree[node] = arr[start];
	else {
		init(node * 2, start, (start + end) / 2);
		init(node * 2 + 1, (start + end) / 2 + 1, end);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
}

void update(int node, int start, int end, int index, int val) {
	if (index < start || index > end) return;
	if (start == end) {
		arr[index] = val;
		tree[node] = val;
		return;
	}
	update(node * 2, start, (start + end) / 2, index, val);
	update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int query(int node, int start, int end, int left, int right) {
	if (end < left || right < start) return 0;
	if (left <= start && end <= right) return tree[node];
	int lsum = query(node * 2, start, (start + end) / 2, left, right);
	int rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return lsum + rsum;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t; int num;
	for (int i = 0; i < t; ++i) {
		memset(tree, 0, sizeof(tree));
		memset(arr, 0, sizeof(arr));
		M.clear();
		cin >> n >> m;
		for (int j = 0; j < n; ++j) {
			M[n - j] = j;
			arr[j] = 1;
		}
		init(1, 0, n + m - 1);
		for (int j = 0; j < m; ++j) {
			cin >> num;
			update(1, 0, n + m - 1, M[num], 0);
			cout << query(1, 0, n + m - 1, M[num], n + m - 1) << " ";
			M[num] = n + j;
			update(1, 0, n + m - 1, M[num], 1);
		}
		cout << '\n';
	}
}