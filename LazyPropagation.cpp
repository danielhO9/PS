#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct LazyPropagation {
	vector<ll> arr;
	vector<ll> tree;
	vector<ll> lazy;
	ll sz;

	void init(vector<ll>& a, ll sz_) {
		sz = sz_;
		arr = a;
		ll h = (ll)ceil(log2(sz));
		ll tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
		lazy = vector<ll>(tree_size);
		init_(1, 0, sz - 1);
	}
	void init_(ll node, ll start, ll end) {
		if (start == end) tree[node] = arr[start];
		else {
			init_(node * 2, start, (start + end) / 2);
			init_(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = tree[node * 2] + tree[node * 2 + 1];
		}
	}
	void update_lazy(ll node, ll start, ll end) {
		if (lazy[node] != 0) {
			tree[node] += (end - start + 1) * lazy[node];
			if (start != end) {
				lazy[node * 2] += lazy[node];
				lazy[node * 2 + 1] += lazy[node];
			}
			lazy[node] = 0;
		}
	}
	void update_range(ll node, ll start, ll end, ll left, ll right, ll diff) {
		update_lazy(node, start, end);
		if (left > end || right < start) {
			return;
		}
		if (left <= start && end <= right) {
			tree[node] += (end - start + 1) * diff;
			if (start != end) {
				lazy[node * 2] += diff;
				lazy[node * 2 + 1] += diff;
			}
			return;
		}
		update_range(node * 2, start, (start + end) / 2, left, right, diff);
		update_range(node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
	void update(ll left, ll right, ll val) {
		update_range(1, 0, sz - 1, left, right, val);
	}
	ll query(ll node, ll start, ll end, ll left, ll right) {
		update_lazy(node, start, end);
		if (left > end || right < start) {
			return 0;
		}
		if (left <= start && end <= right) {
			return tree[node];
		}
		ll lsum = query(node * 2, start, (start+end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start+end) / 2 + 1, end, left, right);
		return lsum + rsum;
	}
	ll query(ll left, ll right) {
		return query(1, 0, sz - 1, left, right);
	}
} seg;

void solve() {
	ll MAX_N;
    vector<ll> a(MAX_N);
    seg.init(a, MAX_N);
}