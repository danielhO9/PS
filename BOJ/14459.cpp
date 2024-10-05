#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
int l[100001], r[100001];
int linv[100001];
vector<int> idx[100001];

struct SegmentTree {
	vector<ll> arr;
	vector<ll> tree;
	int sz;

	void init(vector<ll>& a, int sz_) {
		sz = sz_;
		arr = a;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
		init(1, 0, sz - 1);
	}
	void init(int node, int start, int end) {
		if (start == end) tree[node] = arr[start];
		else {
			init(node * 2, start, (start + end) / 2);
			init(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
		}
	}
	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			arr[index] = max(arr[index], val);
			tree[node] = max(tree[node], val);
			return;
		}
		update(node * 2, start, (start + end) / 2, index, val);
		update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
		tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
	}
	void update(int index, ll val) {
		update(1, 0, sz - 1, index, val);
	}
	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return 0;
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return max(lsum, rsum);
	}
	ll query(int left, int right) {
		return query(1, 0, sz - 1, left, right);
	}
} seg;

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> l[i];
	for (int i = 0; i < N; ++i) cin >> r[i];
	for (int i = 0; i < N; ++i) linv[l[i]] = i;

	for (int i = 0; i < N; ++i) {
		for (int j = r[i] - 4; j <= r[i] + 4; ++j) {
			if (1 <= j && j <= N) {
				idx[linv[j]].push_back(i);
			}
		}
	}
	for (int i = 0; i < N; ++i) sort(idx[i].begin(), idx[i].end());
	// for (int i = 0; i < N; ++i) {
	// 	for (auto j: idx[i]) cout << j << ' ';
	// 	cout << '\n';
	// }
	int MAX_N = N + 10;
	vector<ll> arr(MAX_N);
	seg.init(arr, MAX_N);
	for (int i = N - 1; i >= 0; --i) {
		for (auto j: idx[i]) {
			ll tmp = seg.query(j + 1, N);
			seg.update(j, tmp + 1);
		}
	}
	cout << seg.query(0, N - 1);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}