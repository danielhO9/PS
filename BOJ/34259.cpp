#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct LazyPropagation {
	vector<ll> tree;
	vector<ll> lazy;
	int sz;

	inline ll merge(ll a, ll b) { return a + b; }
	LazyPropagation() = default;
	LazyPropagation(int sz): LazyPropagation(vector<ll>(sz, 0)) {}
	LazyPropagation(const vector<ll>& a) {
		sz = a.size();
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
        lazy = vector<ll>(tree_size);
	}
	void update_lazy(ll node, ll start, ll end) {
		if (lazy[node] != 0) {
			tree[node] += (end - start + 1) * lazy[node];
			if (start != end) {
				lazy[node * 2] = merge(lazy[node * 2], lazy[node]);
				lazy[node * 2 + 1] = merge(lazy[node * 2 + 1], lazy[node]);
			}
			lazy[node] = 0;
		}
	}
	void update_range(ll node, ll start, ll end, ll left, ll right, ll diff) {
		update_lazy(node, start, end);
		if (left > end || right < start) return;
		if (left <= start && end <= right) {
			tree[node] += (end - start + 1) * diff;
			if (start != end) {
				lazy[node * 2] = merge(lazy[node * 2], diff);
				lazy[node * 2 + 1] = merge(lazy[node * 2 + 1], diff);
			}
			return;
		}
		int mid = (start + end) / 2;
		update_range(node * 2, start, mid, left, right, diff);
		update_range(node * 2 + 1, mid + 1, end, left, right, diff);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}
	ll query(ll node, ll start, ll end, ll left, ll right) {
		update_lazy(node, start, end);
		if (left > end || right < start) return 0;
		if (left <= start && end <= right) return tree[node];
		int mid = (start + end) / 2;
		ll lsum = query(node * 2, start, mid, left, right);
		ll rsum = query(node * 2 + 1, mid + 1, end, left, right);
		return merge(lsum, rsum);
	}
	void update(ll left, ll right, ll val) { update_range(1, 0, sz - 1, left, right, val); }
	ll query(ll left, ll right) { return query(1, 0, sz - 1, left, right); }
};

struct LazyPropagationMax {
	vector<ll> tree;
	vector<ll> lazy;
	int sz;

	inline ll merge(ll a, ll b) { return max(a, b); }
	LazyPropagationMax() = default;
	LazyPropagationMax(int sz): LazyPropagationMax(vector<ll>(sz, 0)) {}
	LazyPropagationMax(const vector<ll>& a) {
		sz = a.size();
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
        lazy = vector<ll>(tree_size);
	}
	void update_lazy(ll node, ll start, ll end) {
		if (lazy[node] != 0) {
			tree[node] += lazy[node];
			if (start != end) {
				lazy[node * 2] += lazy[node];
				lazy[node * 2 + 1] += lazy[node];
			}
			lazy[node] = 0;
		}
	}
	void update_range(ll node, ll start, ll end, ll left, ll right, ll diff) {
		update_lazy(node, start, end);
		if (left > end || right < start) return;
		if (left <= start && end <= right) {
			tree[node] += diff;
			if (start != end) {
				lazy[node * 2] += diff;
				lazy[node * 2 + 1] += diff;
			}
			return;
		}
		int mid = (start + end) / 2;
		update_range(node * 2, start, mid, left, right, diff);
		update_range(node * 2 + 1, mid + 1, end, left, right, diff);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}
	ll query(ll node, ll start, ll end, ll left, ll right) {
		update_lazy(node, start, end);
		if (left > end || right < start) return LLONG_MIN;
		if (left <= start && end <= right) return tree[node];
		int mid = (start + end) / 2;
		ll lsum = query(node * 2, start, mid, left, right);
		ll rsum = query(node * 2 + 1, mid + 1, end, left, right);
		return merge(lsum, rsum);
	}
	void update(ll left, ll right, ll val) { update_range(1, 0, sz - 1, left, right, val); }
	ll query(ll left, ll right) { return query(1, 0, sz - 1, left, right); }
};

int N, Q, cnt;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> Q;
	LazyPropagation seg {N + 2};
	LazyPropagation dif {N + 2};
	LazyPropagationMax dif2 {N + 2};
    while (Q--) {
        int t, l, r; cin >> t >> l >> r;
        if (t == 1) {
            ll k; cin >> k;
			seg.update(l, r, k);
			
			ll prv = dif.query(l - 1, l - 1);
			dif.update(l - 1, l - 1, -prv + max(0ll, seg.query(l - 1, l - 1) - seg.query(l, l)));
			prv = dif.query(r, r);
			dif.update(r, r, -prv + max(0ll, seg.query(r, r) - seg.query(r + 1, r + 1)));

			dif2.update(l, r, k);
			dif2.update(l - 1, l - 1, -k);
			dif2.update(r + 1, r + 1, -k);
			if (l + 1 <= r - 1) dif2.update(l + 1, r - 1, -2ll * k);
			if (l != r) {
				dif2.update(l, l, -k);
				dif2.update(r, r, -k);
			}

        } else {
			if (l == r) {
                if (seg.query(l, r) == 0) cout << 0 << '\n';
                else cout << -1 << '\n';
            }
			else {
				ll mx = LLONG_MIN;
				if (l + 1 <= r - 1) mx = max(mx, dif2.query(l + 1, r - 1));
				mx = max(mx, seg.query(l, l) - seg.query(l + 1, l + 1));
				mx = max(mx, seg.query(r, r) - seg.query(r - 1, r - 1));
				if (mx > 0) cout << "-1\n";
				else cout << dif.query(l, r - 1) + seg.query(r, r) << '\n';
			}
        }
    }
}