#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

struct LazyPropagation {
	vector<ll> arr;
	vector<ll> tree;
	vector<ll> tree_idx;
	vector<ll> lazy;
	vector<ll> assign;
	ll sz;
	const ll ass = 10001;

	void init(vector<ll>& a, ll sz_) {
		sz = sz_;
		arr = a;
		ll h = (ll)ceil(log2(sz));
		ll tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
		tree_idx = vector<ll>(tree_size);
		lazy = vector<ll>(tree_size);
		assign = vector<ll>(tree_size, ass);
		init_(1, 0, sz - 1);
	}
	void init_(ll node, ll start, ll end) {
		if (start == end) {
			tree[node] = arr[start];
			tree_idx[node] = arr[start] * start;
		}
		else {
			init_(node * 2, start, (start + end) / 2);
			init_(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = tree[node * 2] + tree[node * 2 + 1];
			tree_idx[node] = tree_idx[node * 2] + tree_idx[node * 2 + 1];
		}
	}
	void update_lazy(ll node, ll start, ll end) {
		if (assign[node] != ass) {
			tree[node] = (end - start + 1) * assign[node];
			tree_idx[node] = (end - start + 1) * (end + start) / 2 * assign[node];
			if (start != end) {
				assign[node * 2] = assign[node];
				assign[node * 2 + 1] = assign[node];
				lazy[node * 2] = 0ll;
				lazy[node * 2 + 1] = 0ll;
			}
			assign[node] = ass;
		}
		if (lazy[node] != 0) {
			tree[node] += (end - start + 1) * lazy[node];
			tree_idx[node] += (end - start + 1) * (end + start) / 2 * lazy[node];
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
			tree_idx[node] += (end - start + 1) * (end + start) / 2 * diff;
			if (start != end) {
				lazy[node * 2] += diff;
				lazy[node * 2 + 1] += diff;
			}
			return;
		}
		update_range(node * 2, start, (start + end) / 2, left, right, diff);
		update_range(node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
		tree_idx[node] = tree_idx[node * 2] + tree_idx[node * 2 + 1];
	}
	void update(ll left, ll right, ll val) {
		update_range(1, 0, sz - 1, left, right, val);
	}
	void update_range_ass(ll node, ll start, ll end, ll left, ll right, ll val) {
		update_lazy(node, start, end);
		if (left > end || right < start) {
			return;
		}
		if (left <= start && end <= right) {
			tree[node] = (end - start + 1) * val;
			tree_idx[node] = (end - start + 1) * (end + start) / 2 * val;
			if (start != end) {
				assign[node * 2] = val;
				lazy[node * 2] = 0ll;
				assign[node * 2 + 1] = val;
				lazy[node * 2 + 1] = 0ll;
			}
			return;
		}
		update_range_ass(node * 2, start, (start + end) / 2, left, right, val);
		update_range_ass(node * 2 + 1, (start + end) / 2 + 1, end, left, right, val);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
		tree_idx[node] = tree_idx[node * 2] + tree_idx[node * 2 + 1];
	}
	void update_ass(ll left, ll right, ll val) {
		update_range_ass(1, 0, sz - 1, left, right, val);
	}
	
	pll query(ll node, ll start, ll end, ll left, ll right) {
		update_lazy(node, start, end);
		if (left > end || right < start) {
			return {0, 0};
		}
		if (left <= start && end <= right) {
			return {tree[node], tree_idx[node]};
		}
		auto lsum = query(node * 2, start, (start+end) / 2, left, right);
		auto rsum = query(node * 2 + 1, (start+end) / 2 + 1, end, left, right);
		return {lsum.first + rsum.first, lsum.second + rsum.second};
	}
	pll query(ll left, ll right) {
		return query(1, 0, sz - 1, left, right);
	}
} seg;

ll n, q;

void solve() {
	cin >> n >> q;
	ll MAX_N = n + 1;
    vector<ll> a(MAX_N);
	for (ll i = 1; i <= n; ++i) cin >> a[i];
    seg.init(a, MAX_N);
	while (q--) {
		ll t, l, r; cin >> t >> l >> r;
		if (t == 1) {
			ll x; cin >> x;
			seg.update(l, r, x);
		} else if (t == 2) {
			ll x; cin >> x;
			seg.update_ass(l, r, x);
		} else {
			auto res = seg.query(l, r);
			// cout << res.first << ' ' << res.second << '\n';
			res.second -= (l - 1) * res.first;
			if (res.first == 0) {
				if (res.second == 0) {
					cout << "Yes\n";
					continue;
				} else {
					cout << "No\n";
					continue;
				}
			}
			if (res.second % res.first == 0) {
				ll tmp = res.second / res.first;
				if (1 <= tmp && tmp <= r - l + 1) {
					cout << "Yes\n";
				} else {
					cout << "No\n";
				}
			} else {
				cout << "No\n";
			}
		}
	}
}

int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	solve();
}