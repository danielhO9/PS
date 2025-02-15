#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct LazyPropagation {
	vector<ll> arr;
	vector<pair<ll, ll>> tree;
	vector<ll> lazy;
	ll sz;

	inline pair<ll, ll> merge(pair<ll, ll> a, pair<ll, ll> b) {
		if (a.first == b.first) return {a.first, a.second + b.second};
		if (a.first < b.first) return a;
		return b;
	}

	void init(vector<ll>& a) {
		sz = a.size();
		arr = a;
		ll h = (ll)ceil(log2(sz));
		ll tree_size = (1 << (h + 1));
		tree = vector<pair<ll, ll>>(tree_size);
		lazy = vector<ll>(tree_size);
		init_(1, 0, sz - 1);
	}

	void init_(ll node, ll start, ll end) {
		if (start == end) tree[node] = {arr[start], 1};
		else {
			init_(node * 2, start, (start + end) / 2);
			init_(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}

	void update_lazy(ll node, ll start, ll end) {
		if (lazy[node] != 0) {
			tree[node].first += lazy[node]; // modify
			if (start != end) {
				lazy[node * 2] = lazy[node * 2] + lazy[node]; // modify
				lazy[node * 2 + 1] = lazy[node * 2 + 1] + lazy[node]; // modify
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
			tree[node].first += diff; // modify
			if (start != end) {
				lazy[node * 2] = lazy[node * 2] + diff; // modify
				lazy[node * 2 + 1] = lazy[node * 2 + 1] + diff; // modify
			}
			return;
		}
		update_range(node * 2, start, (start + end) / 2, left, right, diff);
		update_range(node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}

	pair<ll, ll> query(ll node, ll start, ll end, ll left, ll right) {
		update_lazy(node, start, end);
		if (left > end || right < start) return {LLONG_MAX, 1}; // modify
		if (left <= start && end <= right) return tree[node];
		auto lsum = query(node * 2, start, (start + end) / 2, left, right);
		auto rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return merge(lsum, rsum);
	}

	void update(ll left, ll right, ll val) { update_range(1, 0, sz - 1, left, right, val); }

	pair<ll, ll> query(ll left, ll right) { return query(1, 0, sz - 1, left, right); }
} seg;

int N;
vector<pair<int, int>> p[30001], m[30001];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; ++i) {
		int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		p[x1].push_back({y1, y2});
		m[x2].push_back({y1, y2});
	}
	vector<ll> arr(30000, 0);
	seg.init(arr);
	ll ans = 0;
	for (int x = 0; x < 30000; ++x) {
		for (auto i: p[x]) seg.update(i.first, i.second - 1, 1);
		for (auto i: m[x]) seg.update(i.first, i.second - 1, -1);
		auto res = seg.query(0, 30000 - 1);
		ans += 30000 - (res.first == 0 ? res.second : 0);
	}
	cout << ans;

}