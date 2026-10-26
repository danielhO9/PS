#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * Description: Segment Tree supports range queries and point updates efficiently.
 *  Useful for maintaining cumulative sums or other associative operations.
 * Time: Build O(N), Update O(\log N), Query O(\log N).
 */
struct SegmentTree {
    vector<ll> arr;
    vector<ll> tree;
    int sz;

    inline ll merge(ll a, ll b) { return a + b; }
    SegmentTree() = default;
    SegmentTree(int sz): SegmentTree(vector<ll>(sz, 0)) {} // TODO
    SegmentTree(const vector<ll>& a) {
        sz = a.size();
        arr = a;
        int h = 32 - __builtin_clz(sz - 1);
        int tree_size = (1 << (h + 1));
        tree = vector<ll>(tree_size);
        init(1, 0, sz - 1);
    }
    void init(int node, int start, int end) {
        if (start == end) tree[node] = arr[start];
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
            tree[node] = val;
            return;
        }
        int mid = (start + end) >> 1;
        update(node * 2, start, mid, index, val);
        update(node * 2 + 1, mid + 1, end, index, val);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }
    ll query(int node, int start, int end, int left, int right) {
        if (left > end || right < start) return 0; // TODO
        if (left <= start && end <= right) return tree[node];
        int mid = (start + end) >> 1;
        ll lsum = query(node * 2, start, mid, left, right);
        ll rsum = query(node * 2 + 1, mid + 1, end, left, right);
        return merge(lsum, rsum);
    }
    void update(int index, ll val) { update(1, 0, sz - 1, index, val); }
    ll query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N, Q; cin >> N >> Q;
    vector<ll> A(N + 2);
    for (int i = 1; i <= N; ++i) cin >> A[i];
    A[0] = 1e15, A[N + 1] = 1e15;
    
    SegmentTree seg {A};
    for (int i = 0; i < Q; ++i) {
        int t, j; ll x; cin >> t >> j >> x;
        if (t == 1) seg.update(j, x);
        else if (t == 2) {
            int l = j - 1, r = N + 1;
            while (l + 1 < r) {
                int mid = ((l + r) >> 1);
                if (seg.query(j, mid) >= x) r = mid;
                else l = mid;
            }
            cout << r << '\n';
        } else {
            int l = 0, r = j + 1;
            while (l + 1 < r) {
                int mid = ((l + r) >> 1);
                if (seg.query(mid, j) >= x) l = mid;
                else r = mid;
            }
            cout << l << '\n';
        }
    }
}