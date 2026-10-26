#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * Description: Segment Tree implementation for solving the Gold Mine problem.
 *  Supports range queries and point updates efficiently.
 * Time: Both update and query operations are O(\log N).
 */

string s[9] = {"0", "1", "01", "10", "010", "101", "0101", "1010", "01010"};
vector<pair<int, int>> dp[9];

struct Node {
    ll v[9];

    Node() {
        for (int i = 0; i < 9; ++i) v[i] = -1e15;
        v[0] = 0;
    }
    Node(ll x) {
        for (int i = 0; i < 9; ++i) v[i] = -1e15;
        v[0] = 0;
        v[1] = x;
    }
};

struct SegmentTree {
    vector<ll> arr;
    vector<Node> tree;
    int sz;

    inline Node merge(const Node& l, const Node& r) {
        Node ret{};
        for (int i = 0; i < 9; ++i) {
            for (auto [j, k]: dp[i]) {
                ret.v[i] = max(ret.v[i], l.v[j] + r.v[k]);
            }
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

int N, Q;

void init() {
    for (int i = 0; i < 9; ++i) for (int j = 0; j < 9; ++j) {
        string ss = s[i];
        if (ss.back() == s[j].front()) ss.pop_back();
        ss += s[j];
        for (int k = 0; k < 9; ++k) if (ss == s[k]) {
            dp[k].push_back(make_pair(i, j));
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init();
    cin >> N >> Q;
    vector<ll> A(N + 1);
    for (int i = 1; i <= N; ++i) cin >> A[i];
    SegmentTree seg {A};
    while (Q--) {
        int t; ll l, r; cin >> t >> l >> r;
        if (t == 1) seg.update(l, r);
        else {
            auto tmp = seg.query(l, r);
            ll ans = 0;
            for (int i = 0; i < 9; ++i) ans = max(ans, tmp.v[i]);
            cout << ans << '\n';
        }
    }
}