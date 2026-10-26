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

    inline ll merge(ll a, ll b) { return a + b; }
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
                lazy[node * 2] = merge(lazy[node * 2], diff); // TODO
                lazy[node * 2 + 1] = merge(lazy[node * 2 + 1], diff); // TODO
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
        if (left > end || right < start) return 0; // TODO
        if (left <= start && end <= right) return tree[node];
        int mid = (start + end) >> 1;
        ll lsum = query(node * 2, start, mid, left, right);
        ll rsum = query(node * 2 + 1, mid + 1, end, left, right);
        return merge(lsum, rsum);
    }
    void update(ll left, ll right, ll val) { update_range(1, 0, sz - 1, left, right, val); }
    ll query(ll left, ll right) { return query(1, 0, sz - 1, left, right); }
};

int N, M, Q;
int L[200000], R[200000];
ll ans[200000];

struct Query {
    int r, i, t;
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M >> Q;
    for (int i = 0; i < N; ++i) {
        cin >> L[i] >> R[i];
    }
    vector<Query> v[N + 1];
    for (int i = 0; i < Q; ++i) {
        int A, B, C, D; cin >> A >> B >> C >> D;
        v[B].push_back({D, i, 1});
        v[B].push_back({C - 1, i, -1});
        v[A - 1].push_back({D, i, -1});
        v[A - 1].push_back({C - 1, i, 1});
    }
    LazyPropagation seg {M + 1};
    for (int i = 0; i <= N; ++i) {
        if (i != 0) {
            seg.update(L[i-1], R[i-1], 1);
        }
        for (auto q: v[i]) {
            ans[q.i] += seg.query(0, q.r) * q.t;
        }
    }
    for (int i = 0; i < Q; ++i) cout << ans[i] << '\n';
}