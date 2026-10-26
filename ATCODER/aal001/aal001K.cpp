#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 998244353;

struct Query {
    int t;
    ll x;
};

vector<ll> a;

struct Node {
    ll v, c;
    Node() = default;
    Node(int i, ll _c) {
        c = _c;
        v = a[i] * c % MOD;
    }
};

/**
 * Description: Segment Tree implementation for solving the Gold Mine problem.
 *  Supports range queries and point updates efficiently.
 * Time: Both update and query operations are O(\log N).
 */

struct SegmentTree {
    vector<ll> arr;
    vector<Node> tree;
    int sz;

    inline Node merge(const Node& l, const Node& r) {
        Node ret{};
        ret.v = l.v + r.v; ret.v %= MOD;
        ret.c = l.c + r.c; ret.c %= MOD;
        return ret;
    }
    SegmentTree() = default;
    SegmentTree(const vector<ll>& a) {
        sz = a.size();
        arr = a;
        int h = 32 - __builtin_clz(sz - 1);
        int tree_size = (1 << (h + 1));
        tree = vector<Node>(tree_size);
        init(1, 0, sz - 1);
    }
    void init(int node, int start, int end) {
        if (start == end) tree[node] = Node {start, arr[start]};
        else {
            int mid = (start + end) >> 1;
            init(node * 2, start, mid);
            init(node * 2 + 1, mid + 1, end);
            tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
        }
    }
    void update(int node, int start, int end, int index, ll val) {
        if (index < start || index > end) return;
        if (start == end) {
            arr[index] += val;
            tree[node] = Node {index, arr[index]};
            return;
        }
        int mid = (start + end) >> 1;
        update(node * 2, start, mid, index, val);
        update(node * 2 + 1, mid + 1, end, index, val);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }
    Node query(int node, int start, int end, int left, int right) {
        if (left > end || right < start) return Node {};
        if (left <= start && end <= right) return tree[node];
        int mid = (start + end) >> 1;
        Node l = query(node * 2, start, mid, left, right);
        Node r = query(node * 2 + 1, mid + 1, end, left, right);
        return merge(l, r);
    }
    void update(int index, ll val) { update(1, 0, sz - 1, index, val); }
    Node query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

vector<Query> qs;
int N, Q;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> Q; qs.resize(Q);
    vector<ll> A(N); for (int i = 0; i < N; ++i) cin >> A[i];

    for (int i = 0; i < Q; ++i) {
        cin >> qs[i].t;
        if (qs[i].t != 3) cin >> qs[i].x;
    }

    for (int i = 0; i < Q; ++i) {
        if (qs[i].t != 3) a.push_back(qs[i].x);
    }
    for (int i = 0; i < N; ++i) a.push_back(A[i]);
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    
    vector<ll> aa(a.size());
    for (int i = 0; i < N; ++i) {
        int idx = lower_bound(a.begin(), a.end(), A[i]) - a.begin();
        ++aa[idx];
    }
    SegmentTree seg {aa};
    ll sm = 0;
    sort(A.begin(), A.end());
    for (ll i = 0; i < N; ++i) {
        sm += (i + 1) * A[i] % MOD;
        sm %= MOD;
    }
    ll len = N;
    for (auto [t, x]: qs) {
        if (t != 3) {
            x = lower_bound(a.begin(), a.end(), x) - a.begin();
        }
        if (t == 1) {
            auto q = x + 1 < a.size() ? seg.query(x + 1, (int) a.size() - 1) : Node{};
            sm += q.v; sm %= MOD;
            ++len;
            sm += (len - q.c) * a[x] % MOD; sm %= MOD;
            seg.update(x, 1);
            // cout << t << ' ' << len << ' ' << a[x] << '\n';
        } else if (t == 2) {
            auto q = x + 1 < a.size() ? seg.query(x + 1, (int) a.size() - 1) : Node{};
            sm += MOD - q.v; sm %= MOD;
            sm += MOD - ((len - q.c) * a[x] % MOD); sm %= MOD;
            seg.update(x, -1);
            --len;
            // cout << t << ' ' << len << ' ' << a[x] << '\n';
        } else {
            cout << sm << '\n';
        }
    }
}