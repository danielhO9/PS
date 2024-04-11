#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void init(vector<ll>& a, vector<ll>& tree, int node, int start, int end) {
	if (start == end) tree[node] = a[start];
	else {
		init(a, tree, node * 2, start, (start + end) / 2);
		init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
		tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
	}
}

void update(vector<ll>& a, vector<ll>& tree, int node, int start, int end, int index, ll val) {
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

ll query(vector<ll>& tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return LLONG_MAX;
	if (left <= start && end <= right) return tree[node];
	ll lsum = query(tree, node * 2, start, (start + end) / 2, left, right);
	ll rsum = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return min(lsum, rsum);
}

void solve() {
	int N; cin >> N;
	vector<int> ord(N + 1); for (int i = 1; i <= N; ++i) cin >> ord[i];
	vector<int> t1(N + 1);
	for (int i = 0; i < N; ++i) {
		int r; cin >> r;
		t1[r] = i + 1;
	}
	vector<int> t2(N + 1);
	for (int i = 0; i < N; ++i) {
		int r; cin >> r;
		t2[r] = i + 1;
	}
	// 0 ~ MAX_N - 1
	int MAX_N = N + 1;
	int ans = 0;
	vector<ll> arr(MAX_N, LLONG_MAX);
	int h = (int)ceil(log2(MAX_N));
	int tree_size = (1 << (h + 1));
	vector<ll> tree(tree_size);
	init(arr, tree, 1, 0, MAX_N - 1);
	for (int i = 1; i <= N; ++i) {
		int stu = ord[i];
		update(arr, tree, 1, 0, MAX_N - 1, t1[stu], t2[stu]);
		if (query(tree, 1, 0, MAX_N - 1, 0, t1[stu]) == t2[stu]) ++ans;
	}
	cout << ans;
	// update(arr, tree, 1, 0, MAX_N - 1, cur, 30);
	// query(tree, 1, 0, MAX_N - 1, 0, cur);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}