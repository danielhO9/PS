#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
			tree[node] = tree[node * 2] + tree[node * 2 + 1];
		}
	}
	void update(int node, int start, int end, int index, ll val) {
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
	void update(int index, ll val) {
		update(1, 0, sz - 1, index, val);
	}
	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return 0;
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return lsum + rsum;
	}
	ll query(int left, int right) {
		return query(1, 0, sz - 1, left, right);
	}
};

void solve() {
	int n; cin >> n;
	ll ans = 0ll;
	int t[n]; for (int i = 0; i < n; ++i) cin >> t[i];
	for (int i = 0; i < n; ++i) {
		if (t[0] > t[i]) {
			swap(t[i], t[0]);
			++ans;
		}
	}
	set<ll> s;
	for (int i = 0; i < n; ++i) s.insert(t[i]);
	int idx = 0;
	unordered_map<ll, ll> m;
	for (auto i: s) {
		m[i] = idx++;
	}

	SegmentTree seg;

	int MAX_N = idx;
	vector<ll> arr(MAX_N);
	seg.init(arr, MAX_N);
	for (int i = 0; i < n; ++i) {
		int tmp = m[t[i]];
		if (tmp != 0) {
			ans += seg.query(0, tmp - 1);
		}
		seg.update(tmp, 1);
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}

/*
6 1 4 2 100 0
1 6 4 2 100 0
0 4 5 6 2 100 1
4 0 5 6 2 100 1
5 0 4 6 2 100 1
5 4 0 6 2 100 1

6 0 4 2 100 1

6 4 0 2 100 1

6 4 2 0 100 1

100 4 2 0 6 1
100 6 2 0 4 1
100 6 4 0 2 1
100 6 4 2 0 1

100 6 4 2 1 0
*/