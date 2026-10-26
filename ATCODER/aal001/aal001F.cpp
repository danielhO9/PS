#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, Q;

/**
 * Description: Segment Tree implementation for solving the Gold Mine problem.
 *  Supports range queries and point updates efficiently.
 * Time: Both update and query operations are O(\log N).
 */

struct Node {
    ll v[2], l[2], mx;
    bool s;

    Node() {
        v[0] = v[1] = -1;
        l[0] = l[1] = 0;
        mx = 0;
        s = true;
    }
    Node(ll x) {
        v[0] = v[1] = x;
        l[0] = l[1] = 1;
        mx = 1;
        s = true;
    }
};

struct SegmentTree {
    vector<ll> arr;
    vector<Node> tree;
    int sz;

    inline Node merge(const Node& l, const Node& r) {
        Node ret{};
        ret.v[0] = l.v[0];
        ret.v[1] = r.v[1];
        ret.l[0] = (l.s && l.v[1] == r.v[0] ? l.l[0] + r.l[0] : l.l[0]);
        ret.l[1] = (r.s && l.v[1] == r.v[0] ? r.l[1] + l.l[1] : r.l[1]);
        ret.mx = max({ret.l[0], ret.l[1], l.mx, r.mx});
        if (l.v[1] == r.v[0]) ret.mx = max(ret.mx, l.l[1] + r.l[0]);
        ret.s = (l.s && r.s && l.v[1] == r.v[0]);
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
        if (start == end) tree[node] = Node {arr[start]};
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
            tree[node] = Node {arr[index]};
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
    SegmentTree seg {A};
    while (Q--) {
        int t; ll l, r; cin >> t >> l >> r;
        if (t == 1) seg.update(l, r);
        else cout << seg.query(l, r).mx << '\n';
    }
}