#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INIT_VALUE = 0; // TODO

struct LazyPropagation {
	vector<ll> arr;
	vector<ll> tree;
	vector<ll> lazy;
	int sz;

	inline ll merge(ll a, ll b) { return a + b; }
	LazyPropagation() = default;
	LazyPropagation(int sz): LazyPropagation(vector<ll>(sz, INIT_VALUE)) {}
	LazyPropagation(const vector<ll>& a) {
		sz = a.size();
		arr = a;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
        lazy = vector<ll>(tree_size);
		init(1, 0, sz - 1);
	}
	void init(ll node, ll start, ll end) {
		if (start == end) tree[node] = arr[start];
		else {
			int mid = (start + end) / 2;
			init(node * 2, start, mid);
			init(node * 2 + 1, mid + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}
	void update_lazy(ll node, ll start, ll end) {
		if (lazy[node] != 0) {
			tree[node] = (end - start + 1) - tree[node]; // TODO
			if (start != end) {
				lazy[node * 2] ^= 1;
				lazy[node * 2 + 1] ^= 1;
			}
			lazy[node] = 0;
		}
	}
	void update_range(ll node, ll start, ll end, ll left, ll right) {
		update_lazy(node, start, end);
		if (left > end || right < start) return;
		if (left <= start && end <= right) {
			tree[node] = (end - start + 1) - tree[node]; // TODO
			if (start != end) {
				lazy[node * 2] ^= 1;
				lazy[node * 2 + 1] ^= 1;
			}
			return;
		}
		int mid = (start + end) / 2;
		update_range(node * 2, start, mid, left, right);
		update_range(node * 2 + 1, mid + 1, end, left, right);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}
	ll query(ll node, ll start, ll end, ll left, ll right) {
		update_lazy(node, start, end);
		if (left > end || right < start) return INIT_VALUE;
		if (left <= start && end <= right) return tree[node];
		int mid = (start + end) / 2;
		ll lsum = query(node * 2, start, mid, left, right);
		ll rsum = query(node * 2 + 1, mid + 1, end, left, right);
		return merge(lsum, rsum);
	}
	void update(ll left, ll right) { update_range(1, 0, sz - 1, left, right); }
	ll query(ll left, ll right) { return query(1, 0, sz - 1, left, right); }
};

int n;

void solve() {
    cin >> n;
    const ll bot = -1000000010;
    vector<pair<ll, ll>> cor;
    for (int i = 0; i < n; ++i) {
        ll x, y; cin >> x >> y;
        cor.push_back(make_pair(x, x + y - bot));
    }
    vector<ll> v;
    for (auto i: cor) {
        v.push_back(i.first - 1);
        v.push_back(i.first);
        v.push_back(i.first + 1);
        v.push_back(i.second - 1);
        v.push_back(i.second);
        v.push_back(i.second + 1);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    LazyPropagation seg {(int) v.size()};
    for (auto i: cor) {
        int l = lower_bound(v.begin(), v.end(), i.first) - v.begin();
        int r = lower_bound(v.begin(), v.end(), i.second) - v.begin();
        seg.update(l, r);
    }
    int l = -1, r = v.size(), mid; --r;
    ll mx = seg.query(0, r);
    assert(mx != 0);
    while (l + 1 < r) {
        mid = (l + r) / 2;
        if (seg.query(0, mid)) r = mid;
        else l = mid;
    }
    int s = r;

    l = -1, r = v.size(); --r;
    while (l + 1 < r) {
        mid = (l + r) / 2;
        if (seg.query(0, mid) == mx) r = mid;
        else l = mid;
    }
    int e = r;
    ll len = v[e] - v[s] + 1;
    cout << v[s] << ' ' << bot + len - 1 << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}