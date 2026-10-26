#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct LazyPropagation {
	vector<ll> arr;
	vector<ll> tree;
	vector<ll> tree2;
	vector<ll> lazy;
	ll sz;

	void init(vector<ll>& a, ll sz_) {
		sz = sz_;
		arr = a;
		ll h = (ll)ceil(log2(sz));
		ll tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
		tree2 = vector<ll>(tree_size);
		lazy = vector<ll>(tree_size);
		init_(1, 0, sz - 1);
	}
	void init_(ll node, ll start, ll end) {
		if (start == end) {
			tree[node] = arr[start];
			tree2[node] = arr[start] * (sz - start);
		}
		else {
			init_(node * 2, start, (start + end) / 2);
			init_(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = tree[node * 2] + tree[node * 2 + 1];
			tree2[node] = tree2[node * 2] + tree2[node * 2 + 1];
		}
	}
	void update_lazy(ll node, ll start, ll end) {
		if (lazy[node] != 0) {
			tree[node] = (end - start + 1) * lazy[node];
			tree2[node] = (2 * sz - start - end) * (end - start + 1) / 2 * lazy[node];
			if (start != end) {
				lazy[node * 2] = lazy[node];
				lazy[node * 2 + 1] = lazy[node];
			}
			lazy[node] = 0;
		}
	}
	void update_range(ll node, ll start, ll end, ll left, ll right, ll val) {
		update_lazy(node, start, end);
		if (left > end || right < start) {
			return;
		}
		if (left <= start && end <= right) {
			tree[node] = (end - start + 1) * val;
			tree2[node] = (2 * sz - start - end) * (end - start + 1) / 2 * val;
			if (start != end) {
				lazy[node * 2] = val;
				lazy[node * 2 + 1] = val;
			}
			return;
		}
		update_range(node * 2, start, (start + end) / 2, left, right, val);
		update_range(node * 2 + 1, (start + end) / 2 + 1, end, left, right, val);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
		tree2[node] = tree2[node * 2] + tree2[node * 2 + 1];
	}
	void update(ll left, ll right, ll val) {
		if (left > right) return;
		update_range(1, 0, sz - 1, left, right, val);
	}
	pair<ll, ll> query(ll node, ll start, ll end, ll left, ll right) {
		update_lazy(node, start, end);
		if (left > end || right < start) {
			return {0, 0};
		}
		if (left <= start && end <= right) {
			return {tree[node], tree2[node]};
		}
		auto lsum = query(node * 2, start, (start+end) / 2, left, right);
		auto rsum = query(node * 2 + 1, (start+end) / 2 + 1, end, left, right);
		return {lsum.first + rsum.first, lsum.second + rsum.second};
	}
	pair<ll, ll> query(ll left, ll right) {
		return query(1, 0, sz - 1, left, right);
	}
} seg;

ll N;
ll X[200001];

void solve() {
	cin >> N;
	for (ll i = 1; i <= N; ++i) cin >> X[i];
	ll MAX_N = N + 1;
    vector<ll> a(MAX_N);
	for (ll i = 1; i <= N; ++i) {
		if (i == 1) a[i] = X[i];
		else a[i] = X[i] - X[i - 1];
	}
    seg.init(a, MAX_N);
	ll ans = 0ll;
	ll Q; cin >> Q;
	while (Q--) {
		ll T, G; cin >> T >> G;
		ll Tcor = seg.query(1, T).first;
		if (Tcor < G) {
			ll l = T, r = N + 1;
			while (l + 1 < r) {
				ll mid = (l + r) / 2;
				if (seg.query(1, mid).first < mid - T + G) l = mid;
				else r = mid;
			}
			ll tmp = (2 * G + l - T) * (l - T + 1) / 2;
			// cout << tmp << ' ';
			auto T_l = seg.query(T, l);
			// cout << T_l.first << ' ' << T_l.second << '\n';
			tmp -= T_l.second - (N - l) * T_l.first;
			if (T - 1 >= 1) tmp -= seg.query(1, T - 1).first * (l - T + 1);
			ans += tmp;
			// cout << l << ' ' << tmp << '\n';
			if (l + 1 <= N) {
				auto lcor = seg.query(1, l + 1).first;
				seg.update(l + 1, l + 1, lcor - (G+l-T));
			}
			seg.update(T, T, seg.query(T, T).first + G - Tcor);
			if (T + 1 <= l) seg.update(T + 1, l, 1);
		}
		if (Tcor > G) {
			ll r = T, l = 0;
			while (l + 1 < r) {
				ll mid = (l + r) / 2;
				if (seg.query(1, mid).first > G-T+mid) r = mid;
				else l = mid;
			}
			// cout << r << ' ';
			ll tmp = (2 * G + r - T) * (T - r + 1) / 2;
			auto T_r = seg.query(r, T);
			tmp = T_r.second - (N - T) * T_r.first - tmp;
			if (r - 1 >= 0) tmp += seg.query(1, r - 1).first * (1 + T - r);
			// cout << tmp << '\n';
			ans += tmp;
			if (T + 1 <= N) {
				auto rcor = seg.query(1, T + 1).first;
				seg.update(T + 1, T + 1, rcor - G);
			}
			if (r - 1 >= 0) {
				auto rcor = seg.query(1, r - 1).first;
				seg.update(r, r, (G - T + r) - rcor);
			}
			if (r + 1 <= T) seg.update(r + 1, T, 1);
		}
		// cout << ans << ' ';
		// for (ll i = 1; i <= N; ++i) {
		// 	cout << seg.query(1, i).first << ' ';
		// }
		// cout << '\n';
	}
	cout << ans;
}


int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}