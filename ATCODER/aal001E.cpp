#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, Q;
const ll MOD = 998244353;
int b[200001];

/**
 * Description: Segment Tree implementation for solving the Gold Mine problem.
 *  Supports range queries and point updates efficiently.
 * Time: Both update and query operations are O(\log N).
 */

struct Node {
    ll v[8];

    Node() {
        memset(v, 0, sizeof(v));
    }
    Node(int i, ll x) {
        memset(v, 0, sizeof(v));
        v[1 << i] = x;
    }
};

struct SegmentTree {
    vector<ll> arr;
    vector<Node> tree;
    int sz;

    inline Node merge(const Node& l, const Node& r) {
        Node ret{};
        for (int i = 0; i < 8; ++i) ret.v[i] = (l.v[i] + r.v[i]) % MOD;
        ret.v[3] += l.v[1] * r.v[2] % MOD;
        ret.v[6] += l.v[2] * r.v[4] % MOD;
        ret.v[7] += l.v[1] * r.v[6] % MOD;
        ret.v[7] %= MOD;
        ret.v[7] += l.v[3] * r.v[4] % MOD;
        for (int i = 0; i < 8; ++i) ret.v[i] %= MOD;
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
        if (start == end) tree[node] = Node {b[start], arr[start]};
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
            arr[index] = val;
            tree[node] = Node {b[index], arr[index]};
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

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> Q;
    vector<ll> A(N + 1);
    for (int i = 1; i <= N; ++i) cin >> A[i];
    string S; cin >> S;
    for (int i = 0; i < N; ++i) {
        if (S[i] == 'R') b[i + 1] = 0;
        else if (S[i] == 'G') b[i + 1] = 1;
        else b[i + 1] = 2;
    }
    SegmentTree seg {A};
    while (Q--) {
        int t; ll l, r; cin >> t >> l >> r;
        if (t == 1) seg.update(l, r);
        else cout << seg.query(l, r).v[7] << '\n';
    }
}