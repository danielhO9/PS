#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int N, M;

void init(vector<LL> &a, vector<LL> & tree, int node, int start, int end) {
	if (start == end) tree[node] = start;
	else {
		init(a, tree, node * 2, start, (start + end) / 2);
		init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
		if (a[tree[node * 2]] < a[tree[node * 2 + 1]]) tree[node] = tree[node * 2];
		else if (a[tree[node * 2]] > a[tree[node * 2 + 1]]) tree[node] = tree[node * 2 + 1];
		else tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
	}
}

void update(vector<LL> &a, vector<LL>& tree, int node, int start, int end, int index, LL val) {
	if (index < start || index > end) return;
	if (start == end) {
		a[index] = val;
		return;
	}
	update(a, tree, node * 2, start, (start + end) / 2, index, val);
	update(a, tree, node * 2 + 1, (start + end) / 2 + 1, end, index, val);
	if (a[tree[node * 2]] < a[tree[node * 2 + 1]]) tree[node] = tree[node * 2];
	else if (a[tree[node * 2]] > a[tree[node * 2 + 1]]) tree[node] = tree[node * 2 + 1];
	else tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
}

LL query(vector<LL> &a, vector<LL> &tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return -1;
	if (left <= start && end <= right) return tree[node];
	LL l = query(a, tree, node * 2, start, (start + end) / 2, left, right);
	LL r = query(a, tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	if (l == -1 && r == -1) return -1;
	if (l == -1 || r == -1) return l + r + 1;
	if (a[l] < a[r]) return l;
	else if (a[l] > a[r]) return r;
	else return min(l, r);
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
		else cout << query(arr, tree, 1, 0, N - 1, b - 1, c - 1) + 1 << '\n';
	}
}