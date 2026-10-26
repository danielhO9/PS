#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, Q;
const ll MOD = 998244353;

/**
 * Description: Segment Tree with Lazy Propagation for efficient range updates and queries.
 *  Supports range updates and range queries efficiently.
 * Time: Both update and query operations are O(\log N).
 */

struct Node {
    ll sm[5];

    Node() = default;
    Node(ll x) {
        sm[0] = 1;
        for (int i = 1; i <= 4; ++i) sm[i] = sm[i - 1] * x % MOD;
    }
};

struct LazyPropagation {
    vector<ll> arr;
    vector<Node> tree;
    vector<ll> lazy;
    int sz;

    inline Node merge(const Node& l, const Node& r) {
        Node ret{};
        for (int i = 0; i <= 4; ++i) ret.sm[i] = (l.sm[i] + r.sm[i]) % MOD;
        return ret;
    }
    inline Node merge(const Node n, ll x) {
        Node ret {n};

        ret.sm[4] += (((ret.sm[0] * x % MOD) * x % MOD) * x % MOD) * x % MOD; ret.sm[4] %= MOD;
        ret.sm[4] += 4 * ((ret.sm[1] * x % MOD) * x % MOD) * x % MOD; ret.sm[4] %= MOD;
        ret.sm[4] += 6 * (ret.sm[2] * x % MOD) * x % MOD; ret.sm[4] %= MOD;
        ret.sm[4] += 4 * ret.sm[3] * x % MOD; ret.sm[4] %= MOD;

        ret.sm[3] += ((ret.sm[0] * x % MOD) * x % MOD) * x % MOD; ret.sm[3] %= MOD;
        ret.sm[3] += 3 * (ret.sm[1] * x % MOD) * x % MOD; ret.sm[3] %= MOD;
        ret.sm[3] += 3 * ret.sm[2] * x % MOD; ret.sm[3] %= MOD;
        
        ret.sm[2] += (ret.sm[0] * x % MOD) * x % MOD; ret.sm[2] %= MOD;
        ret.sm[2] += 2 * ret.sm[1] * x % MOD; ret.sm[2] %= MOD;

        ret.sm[1] += ret.sm[0] * x % MOD; ret.sm[1] %= MOD;
        return ret;
    }
    LazyPropagation() = default;
    LazyPropagation(int sz): LazyPropagation(vector<ll>(sz, 0)) {} // TODO
    LazyPropagation(const vector<ll>& a) {
        sz = a.size();
        arr = a;
        int h = 32 - __builtin_clz(sz - 1);
        int tree_size = (1 << (h + 1));
        tree = vector<Node>(tree_size);
        lazy = vector<ll>(tree_size);
        init(1, 0, sz - 1);
    }
    void init(ll node, ll start, ll end) {
        if (start == end) tree[node] = Node{arr[start]};
        else {
            int mid = (start + end) >> 1;
            init(node * 2, start, mid);
            init(node * 2 + 1, mid + 1, end);
            tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
        }
    }
    void update_lazy(ll node, ll start, ll end) {
        if (lazy[node] != 0) {
            tree[node] = merge(tree[node], lazy[node]);
            if (start != end) {
                lazy[node * 2] += lazy[node]; lazy[node * 2] %= MOD;
                lazy[node * 2 + 1] += lazy[node]; lazy[node * 2 + 1] %= MOD;
            }
            lazy[node] = 0;
        }
    }
    void update_range(ll node, ll start, ll end, ll left, ll right, ll diff) {
        update_lazy(node, start, end);
        if (left > end || right < start) return;
        if (left <= start && end <= right) {
            tree[node] = merge(tree[node], diff);
            if (start != end) {
                lazy[node * 2] += diff; lazy[node * 2] %= MOD;
                lazy[node * 2 + 1] += diff; lazy[node * 2 + 1] %= MOD;
            }
            return;
        }
        int mid = (start + end) >> 1;
        update_range(node * 2, start, mid, left, right, diff);
        update_range(node * 2 + 1, mid + 1, end, left, right, diff);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }
    Node query(ll node, ll start, ll end, ll left, ll right) {
        update_lazy(node, start, end);
        if (left > end || right < start) return Node {};
        if (left <= start && end <= right) return tree[node];
        int mid = (start + end) >> 1;
        Node lsum = query(node * 2, start, mid, left, right);
        Node rsum = query(node * 2 + 1, mid + 1, end, left, right);
        return merge(lsum, rsum);
    }
    void update(ll left, ll right, ll val) { update_range(1, 0, sz - 1, left, right, val); }
    Node query(ll left, ll right) { return query(1, 0, sz - 1, left, right); }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> Q;
    vector<ll> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    LazyPropagation seg {A};
    while (Q--) {
        int t; ll l, r, x; cin >> t >> l >> r >> x;
        if (t == 1) seg.update(--l, --r, x);
        else {
            auto tmp = seg.query(--l, --r);
            cout << tmp.sm[x] << '\n';
        }
    }
}