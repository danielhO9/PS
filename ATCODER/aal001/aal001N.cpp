#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 998244353;

struct Node {
    ll v, sm;
    Node() {
        v = INT32_MIN;
        sm = 0;
    }
    Node(ll x) {
        v = 0;
        sm = x;
    }
};

inline Node merge(const Node& a, const Node& b) {
    Node ret {};
    ret.v = max(a.v, b.v);
    if (ret.v == a.v) ret.sm += a.sm;
    if (ret.v == b.v) ret.sm += b.sm;
    ret.sm %= MOD;
    return ret;
}

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
            tree[node].v += lazy[node];
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
            tree[node].v += diff;
            if (start != end) {
                lazy[node * 2] += diff;
                lazy[node * 2 + 1] += diff;
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
        if (left > end || right < start) return Node{};
        if (left <= start && end <= right) return tree[node];
        int mid = (start + end) >> 1;
        Node lsum = query(node * 2, start, mid, left, right);
        Node rsum = query(node * 2 + 1, mid + 1, end, left, right);
        return merge(lsum, rsum);
    }
    void update(ll left, ll right, ll val) { update_range(1, 0, sz - 1, left, right, val); }
    Node query(ll left, ll right) { return query(1, 0, sz - 1, left, right); }
};

struct Query {
    ll c, d, dif;
};

int N, Q;
vector<Query> qs[200002];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> Q;
    vector<ll> v(N + 1);
    for (int i = 0; i <= N; ++i) v[i] = i;
    LazyPropagation seg {v};
    while (Q--) {
        ll a, b, c, d; cin >> a >> b >> c >> d;
        qs[a].push_back({b, d, -1});
        qs[c + 1].push_back({b, d, 1});
    }
    ll ans = 0;
    for (ll i = 1; i <= N; ++i) {
        for (auto [c, d, dif]: qs[i]) {
            seg.update(c, d, dif);
        }
        auto q = seg.query(1, N);
        if (q.v == 0) ans += (q.sm * i) % MOD;
        ans %= MOD;
    }
    cout << ans;
}
