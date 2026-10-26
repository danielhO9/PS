#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * Description: Segment Tree with Lazy Propagation for efficient range updates and queries.
 *  Supports range updates and range queries efficiently.
 * Time: Both update and query operations are O(\log N).
 */
struct LazyPropagation {
    vector<ll> arr;
    vector<ll> tree;
    vector<ll> lazy;
    int sz;

    inline ll merge(ll a, ll b) { return min(a, b); }
    LazyPropagation() = default;
    LazyPropagation(int sz): LazyPropagation(vector<ll>(sz, 0)) {} // TODO
    LazyPropagation(const vector<ll>& a) {
        sz = a.size();
        arr = a;
        int h = 32 - __builtin_clz(sz - 1);
        int tree_size = (1 << (h + 1));
        tree = vector<ll>(tree_size);
        lazy = vector<ll>(tree_size);
        init(1, 0, sz - 1);
    }
    void init(ll node, ll start, ll end) {
        if (start == end) tree[node] = arr[start];
        else {
            int mid = (start + end) >> 1;
            init(node * 2, start, mid);
            init(node * 2 + 1, mid + 1, end);
            tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
        }
    }
    void update_lazy(ll node, ll start, ll end) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node]; // TODO
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
            tree[node] += diff; // TODO
            if (start != end) {
                lazy[node * 2] += diff; // TODO
                lazy[node * 2 + 1] += diff; // TODO
            }
            return;
        }
        int mid = (start + end) >> 1;
        update_range(node * 2, start, mid, left, right, diff);
        update_range(node * 2 + 1, mid + 1, end, left, right, diff);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }
    ll query(ll node, ll start, ll end, ll left, ll right) {
        update_lazy(node, start, end);
        if (left > end || right < start) return 1e15; // TODO
        if (left <= start && end <= right) return tree[node];
        int mid = (start + end) >> 1;
        ll lsum = query(node * 2, start, mid, left, right);
        ll rsum = query(node * 2 + 1, mid + 1, end, left, right);
        return merge(lsum, rsum);
    }
    void update(ll left, ll right, ll val) { update_range(1, 0, sz - 1, left, right, val); }
    ll query(ll left, ll right) { return query(1, 0, sz - 1, left, right); }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N, Q; cin >> N >> Q;
    vector<ll> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    LazyPropagation seg{A};
    for (int i = 0; i < Q; ++i) {
        int t; cin >> t;
        if (t == 1) {
            int l, r, x; cin >> l >> r >> x;
            seg.update(--l, --r, x);
        } else {
            int l, r; cin >> l >> r;
            cout << seg.query(--l, --r) << '\n';
        }
    }
}