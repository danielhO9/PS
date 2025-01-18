#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;
ll a[100000];

struct SegmentTree {
	vector<ll> arr;
	vector<ll> tree;
	int sz;

	inline ll merge(ll a, ll b) { return a + b; }

	void init(vector<ll>& a) {
		sz = a.size();
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
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}

	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			arr[index] += val; // modify
			tree[node] += val; // modify
			return;
		}
		update(node * 2, start, (start + end) / 2, index, val);
		update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}

	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return 0; // modify
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return merge(lsum, rsum);
	}

	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }

	ll query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	ll tans = 0;
	for (int num = 1; num <= 10; ++num) {
		ll ans = n * (n - 1) / 2;
		for (int j = 0; j < 2; ++j) {
			SegmentTree seg_odd, seg_even;

			vector<ll> odd(2 * n + 1), even(2 * n + 1), arr(n);

			if (j == 0) arr[0] = (a[0] > num);
			else arr[0] = (a[0] < num);
			for (int i = 1; i < n; ++i) arr[i] = arr[i - 1] + (j == 0 ? a[i] > num : a[i] < num);
			for (int i = 0; i < n; ++i) arr[i] -= (i + 2) / 2;
			for (int i = 0; i < n; ++i) arr[i] += n;

			for (int i = 0; i < n; ++i) {
				if (i % 2) ++odd[arr[i]];
				else ++even[arr[i]];
			}
			seg_odd.init(odd), seg_even.init(even);

			ll oval = 0, eval = 0;

			for (int i = 0; i < n; ++i) {
				if (j == 0) {
					if (i % 2 == 0) {
						seg_even.update(arr[i], -1);
					} else {
						seg_odd.update(arr[i], -1);
					}
				} else {
					if (i % 2 == 0) {
						seg_even.update(arr[i], -1);
					} else {
						seg_odd.update(arr[i], -1);
					}
				}
				ans -= seg_odd.query(n + oval, 2 * n);
				ans -= seg_even.query(n + eval, 2 * n);
				if (j == 0) {
					if (a[i] > num) {
						++oval; ++eval;
					}
					if (i % 2 == 0) {
						--eval;
					} else {
						--oval;
					}
				} else {
					if (a[i] < num) {
						++oval; ++eval;
					}
					if (i % 2 == 0) {
						--eval;
					} else {
						--oval;
					}
				}
			}
		}
		unordered_map<ll, ll> m;
		++m[0];
		ll psum = 0;
		for (int i = 0; i < n; ++i) {
			if (a[i] == num) psum += n;
			else if (a[i] > num) psum += 1;
			else psum -= 1;
			++m[psum];
		}
		ll tmp = 0;
		for (auto [_, i]: m) {
			// cout << i << ' ';
			tmp += i * (i - 1) / 2;
		}
		// cout << tmp << "\n";
		
		tans += ans + tmp;
	}
	cout << tans + n << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}