#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Query {
    int t;
    ll l, r;
};

struct Node {
    ll l, c;
    Node() = default;
    Node(ll x) {
        l = x;
        c = 0;
    }
};

/**
 * Description: Segment Tree with Lazy Propagation for efficient range updates and queries.
 *  Supports range updates and range queries efficiently.
 * Time: Both update and query operations are O(\log N).
 */
struct LazyPropagation {
    vector<ll> arr;
    vector<Node> tree;
    vector<ll> lazy;
    int sz;

    inline Node merge(const Node& a, const Node& b) {
        Node ret {};
        ret.l = a.l + b.l;
        ret.c = a.c + b.c;
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
            tree[node].c = tree[node].l - tree[node].c;
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
            tree[node].c = tree[node].l - tree[node].c;
            if (start != end) {
                lazy[node * 2] ^= 1;
                lazy[node * 2 + 1] ^= 1;
            }
            return;
        }
        int mid = (start + end) >> 1;
        update_range(node * 2, start, mid, left, right);
        update_range(node * 2 + 1, mid + 1, end, left, right);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }
    Node query(ll node, ll start, ll end, ll left, ll right) {
        update_lazy(node, start, end);
        if (left > end || right < start) return 0; // TODO
        if (left <= start && end <= right) return tree[node];
        int mid = (start + end) >> 1;
        Node lsum = query(node * 2, start, mid, left, right);
        Node rsum = query(node * 2 + 1, mid + 1, end, left, right);
        return merge(lsum, rsum);
    }
    void update(ll left, ll right) { update_range(1, 0, sz - 1, left, right); }
    Node query(ll left, ll right) { return query(1, 0, sz - 1, left, right); }
};

vector<Query> qs;
int Q;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> Q; qs.resize(Q);
    for (int i = 0; i < Q; ++i) cin >> qs[i].t >> qs[i].l >> qs[i].r;
    vector<ll> v;
    for (int i = 0; i < Q; ++i) {
        v.push_back(qs[i].l);
        v.push_back(qs[i].r + 1);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    vector<ll> A(v.size());
    int N = v.size();
    for (int i = 0; i + 1 < N; ++i) {
        A[i] = v[i + 1] - v[i];
    }
    for (int i = 0; i < Q; ++i) {
        qs[i].l = lower_bound(v.begin(), v.end(), qs[i].l) - v.begin();
        qs[i].r = upper_bound(v.begin(), v.end(), qs[i].r) - v.begin(); --qs[i].r;
    }
    LazyPropagation seg {A};
    for (auto [t,l, r]: qs) {
        if (t == 1) seg.update(l, r);
        else cout << seg.query(l, r).c << '\n';
    }
}