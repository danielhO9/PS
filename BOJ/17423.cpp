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
			tree[node] += (end - start + 1) * lazy[node]; // TODO
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
			tree[node] += (end - start + 1) * diff; // TODO
			if (start != end) {
				lazy[node * 2] = merge(lazy[node * 2], diff); // modify
				lazy[node * 2 + 1] = merge(lazy[node * 2 + 1], diff); // modify
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
		if (left > end || right < start) return INIT_VALUE;
		if (left <= start && end <= right) return tree[node];
		int mid = (start + end) / 2;
		ll lsum = query(node * 2, start, mid, left, right);
		ll rsum = query(node * 2 + 1, mid + 1, end, left, right);
		return merge(lsum, rsum);
	}
	void update(ll left, ll right, ll val) { update_range(1, 0, sz - 1, left, right, val); }
	ll query(ll left, ll right) { return query(1, 0, sz - 1, left, right); }
} seg;

struct Query {
    ll v, s, e, t;
};

int N;
ll S[100000], x[100000], y[100000];

bool available(ll V) {
    vector<ll> v;
    for (int i = 0; i < N; ++i) {
        v.push_back(-x[i] + y[i] - V * S[i] + 1);
        v.push_back(-x[i] + y[i] + V * S[i]);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    seg = LazyPropagation {(int) v.size()};
    vector<Query> q;
    for (int i = 0; i < N; ++i) {
        ll l = x[i] + y[i] - V * S[i];
        ll r = x[i] + y[i] + V * S[i];
        ll s = -x[i] + y[i] - V * S[i] + 1;
        ll e = -x[i] + y[i] + V * S[i];
        s = lower_bound(v.begin(), v.end(), s) - v.begin();
        e = lower_bound(v.begin(), v.end(), e) - v.begin();
        q.push_back(Query {l, s, e, 1});
        q.push_back(Query {r, s, e, 0});
    }
    sort(q.begin(), q.end(), [](const Query& a, const Query& b) {
        if (a.v == b.v) return a.t < b.t;
        return a.v < b.v;
    });
    for (const auto& query: q) {
        if (query.t) {
            if (seg.query(query.s, query.e)) return false;
            seg.update(query.s, query.e, 1);
        } else seg.update(query.s, query.e, -1);
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> S[i];
    for (int i = 0; i < N; ++i) cin >> x[i] >> y[i];
    int l = 0, r = 1e6 + 1;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (available(mid)) l = mid;
        else r = mid;
    }
    cout << l;
}