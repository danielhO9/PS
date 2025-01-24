#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct LazyPropagation {
	vector<ll> arr;
	vector<ll> tree;
	vector<ll> lazy;
	ll sz;

	inline ll merge(ll a, ll b) { return max(a, b); }

	void init(vector<ll>& a) {
		sz = a.size();
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
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}

	void update_lazy(ll node, ll start, ll end) {
		if (lazy[node] != 0) {
			tree[node] += lazy[node]; // modify
			if (start != end) {
				lazy[node * 2] += lazy[node]; // modify
				lazy[node * 2 + 1] += lazy[node]; // modify
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
			tree[node] += diff; // modify
			if (start != end) {
				lazy[node * 2] += diff; // modify
				lazy[node * 2 + 1] += diff; // modify
			}
			return;
		}
		update_range(node * 2, start, (start + end) / 2, left, right, diff);
		update_range(node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}

	ll query(ll node, ll start, ll end, ll left, ll right) {
		update_lazy(node, start, end);
		if (left > end || right < start) return LLONG_MIN;
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return merge(lsum, rsum);
	}

	void update(ll left, ll right, ll val) { update_range(1, 0, sz - 1, left, right, val); }

	ll query(ll left, ll right) { return query(1, 0, sz - 1, left, right); }
} seg;

int N, M;
int l[200000], r[200000];
ll a[200000];
vector<pair<int, ll>> dif[200002];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	for (int i = 0; i < M; ++i) cin >> l[i] >> r[i] >> a[i];
	vector<ll> arr(N + 1); seg.init(arr);
	for (int i = 0; i < M; ++i) {
		dif[l[i]].push_back({l[i], a[i]});
		dif[r[i] + 1].push_back({l[i], -a[i]});
	}
	ll ans = 0;
	for (int i = 1; i <= N; ++i) {
		for (auto j: dif[i]) seg.update(0, j.first - 1, j.second);
		ll val = seg.query(0, i - 1);
		seg.update(i, i, val);
		ans = max(ans, val);
	}
	cout << ans;
}