#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * Description: Segment Tree implementation for solving the Gold Mine problem.
 *  Supports range queries and point updates efficiently.
 * Time: Both update and query operations are O(\log N).
 */

struct Node {
    bool t[30][2];

    Node() {
        for (int i = 0; i < 30; ++i) for (int j = 0; j < 2; ++j) t[i][j] = j;
    }
    Node(ll x) {
        for (int i = 0; i < 30; ++i) for (int j = 0; j < 2; ++j) {
            int k = ((x >> i) & 1);
            t[i][j] = !(k & j);
        }
    }
};

struct SegmentTree {
    vector<ll> arr;
    vector<Node> tree;
    int sz;

    inline Node merge(const Node& l, const Node& r) {
        Node ret{};
        for (int i = 0; i < 30; ++i) for (int j = 0; j < 2; ++j) {
            ret.t[i][j] = r.t[i][l.t[i][j]];
        }
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
    int N, Q; cin >> N >> Q;
    vector<ll> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    SegmentTree seg {A};
    while (Q--) {
        int t, l, r; cin >> t >> l >> r;
        if (t == 1) {
            --l; seg.update(l, r);
        } else {
            --l; --r;
            if (l == r) cout << seg.arr[l] << '\n';
            else {
                auto res = seg.query(l + 1, r);
                ll ret = seg.arr[l];
                for (int i = 0; i < 30; ++i) {
                    int tmp = ((ret >> i) & 1);
                    if (tmp != res.t[i][tmp]) ret ^= (1 << i);
                }
                cout << ret << '\n';
            }
        }
    }
}