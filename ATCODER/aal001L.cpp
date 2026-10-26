#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll A[100001], B[100001], C[100001];

struct Node {
    ll sm[3], mx[3];
    bool empty = false;

    Node() {
        empty = true;
        for (int i = 0; i < 3; ++i) {
            sm[i] = mx[i] = 0;
        }
    }
    Node(int idx) {
        sm[0] = mx[0] = A[idx];
        sm[1] = mx[1] = B[idx];
        sm[2] = mx[2] = C[idx];
    }
};

void update_node(Node& n, const vector<ll>& val) {
    // cerr << val.size() << '\n';
    assert(val.size() == 3);
    vector<ll> tmp(3);
    for (int i = 0; i < 3; ++i) tmp[i] = n.sm[i];
    for (int i = 0; i < 3; ++i) n.sm[i] = tmp[val[i]];

    for (int i = 0; i < 3; ++i) tmp[i] = n.mx[i];
    for (int i = 0; i < 3; ++i) n.mx[i] = tmp[val[i]];
}

void update_lz(vector<ll>& prv, const vector<ll>& upd) {
    vector<ll> tmp(3);
    for (int i = 0; i < 3; ++i) tmp[i] = prv[i];
    for (int i = 0; i < 3; ++i) prv[i] = tmp[upd[i]];
}

/**
 * Description: Segment Tree with Lazy Propagation for efficient range updates and queries.
 *  Supports range updates and range queries efficiently.
 * Time: Both update and query operations are O(\log N).
 */
struct LazyPropagation {
    vector<Node> tree;
    vector<vector<ll>> lazy;
    int sz;

    inline Node merge(const Node& a, const Node& b) {
        if (a.empty) return b;
        if (b.empty) return a;

        Node ret{};
        for (int i = 0; i < 3; ++i) {
            ret.sm[i] = a.sm[i] + b.sm[i];
            ret.mx[i] = max(a.mx[i], a.sm[i] + b.mx[i]);
        }
        ret.empty = false;
        return ret;
    }
    LazyPropagation() = default;
    LazyPropagation(int sz): LazyPropagation(vector<ll>(sz, 0)) {} // TODO
    LazyPropagation(const vector<ll>& a) {
        sz = a.size();
        int h = 32 - __builtin_clz(sz - 1);
        int tree_size = (1 << (h + 1));
        tree = vector<Node>(tree_size);
        lazy = vector<vector<ll>>(tree_size, {0, 1, 2});
        init(1, 0, sz - 1);
    }
    void init(ll node, ll start, ll end) {
        if (start == end) tree[node] = Node {(int) start};
        else {
            int mid = (start + end) >> 1;
            init(node * 2, start, mid);
            init(node * 2 + 1, mid + 1, end);
            tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
        }
    }
    void update_lazy(ll node, ll start, ll end) {
        if (lazy[node][0] != 0 || lazy[node][1] != 1) {
            update_node(tree[node], lazy[node]);
            if (start != end) {
                update_lz(lazy[node * 2], lazy[node]);
                update_lz(lazy[node * 2 + 1], lazy[node]);
            }
            lazy[node] = {0, 1, 2};
        }
    }
    void update_range(ll node, ll start, ll end, ll left, ll right, const vector<ll>& diff) {
        update_lazy(node, start, end);
        if (left > end || right < start) return;
        if (left <= start && end <= right) {
            update_node(tree[node], diff);
            if (start != end) {
                update_lz(lazy[node * 2], diff);
                update_lz(lazy[node * 2 + 1], diff);
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
        if (left > end || right < start) return Node{}; // TODO
        if (left <= start && end <= right) return tree[node];
        int mid = (start + end) >> 1;
        Node lsum = query(node * 2, start, mid, left, right);
        Node rsum = query(node * 2 + 1, mid + 1, end, left, right);
        return merge(lsum, rsum);
    }
    void update(ll left, ll right, const vector<ll>& val) { update_range(1, 0, sz - 1, left, right, val); }
    Node query(ll left, ll right) { return query(1, 0, sz - 1, left, right); }
};

int N, Q;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> Q;
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < N; ++i) cin >> B[i];
    for (int i = 0; i < N; ++i) cin >> C[i];
    A[N] = B[N] = C[N] = 1e15;
    LazyPropagation seg {N + 1};
    while (Q--) {
        int t; cin >> t;
        if (t == 4) {
            int i; cin >> i; --i;
            int l = i - 1, r = N;
            while (l + 1 < r) {
                int mid = ((l + r) >> 1);
                if (seg.query(i, mid).mx[0] > 0) r = mid;
                else l = mid;
            }
            cout << r + 1 << '\n';
        } else {
            int l, r; cin >> l >> r; --l; --r;
            vector<ll> v;
            if (t == 1) v = {1, 0, 2};
            if (t == 2) v = {0, 2, 1};
            if (t == 3) v = {2, 1, 0};
            seg.update(l, r, v);
        }
    }
}