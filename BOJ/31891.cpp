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
		init_(1, 0, sz - 1);
	}
	void init_(int node, int start, int end) {
		if (start == end) tree[node] = arr[start];
		else {
			init_(node * 2, start, (start + end) / 2);
			init_(node * 2 + 1, (start + end) / 2 + 1, end);
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
} seg;

void solve() {
	int N; cin >> N;
	int MAX_N = N + 1;
	vector<ll> arr(MAX_N);
	vector<int> a(N);
	for (int i = 1; i <= N; ++i) arr[i] = 1;
	seg.init(arr, MAX_N);
	double ans = 0.0;
	for (int i = 0; i < N; ++i) {
		cin >> a[i];
		if (i == 0) {
			seg.update(a[i], 0);
			// cout << seg.query(a[i], N) << ' ';
			ans += 0.5 * seg.query(a[i], N);
			
		} else {
			seg.update(a[i], 0);
			// cout << seg.query(min(a[i], a[i - 1]), N) << ' ';
			ans += 0.5 * seg.query(min(a[i], a[i - 1]), N);
		}
	}
	cout << fixed;
	cout.precision(3);
	cout << ans + N;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}

/*
4 2 5 3 1
1 2 
*/