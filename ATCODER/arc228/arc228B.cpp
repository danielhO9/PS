#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

/**
 * Description: Segment Tree supports range queries and point updates efficiently.
 *  Useful for maintaining cumulative sums or other associative operations.
 * Time: Build O(N), Update O(\log N), Query O(\log N).
 */
struct SegmentTree {
    vector<ll> arr;
    vector<pair<ll, int>> tree;
    int sz;

    inline pair<ll, ll> merge(pair<ll, ll> a, pair<ll, ll> b) { return min(a, b); }
    SegmentTree() = default;
    SegmentTree(int sz): SegmentTree(vector<ll>(sz, 0)) {} // TODO
    SegmentTree(const vector<ll>& a) {
        sz = a.size();
        arr = a;
        int h = 32 - __builtin_clz(sz - 1);
        int tree_size = (1 << (h + 1));
        tree = vector<pair<ll, int>>(tree_size);
        init(1, 0, sz - 1);
    }
    void init(int node, int start, int end) {
        if (start == end) tree[node] = make_pair(arr[start], start);
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
            tree[node].first = val;
            return;
        }
        int mid = (start + end) >> 1;
        update(node * 2, start, mid, index, val);
        update(node * 2 + 1, mid + 1, end, index, val);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }
    pair<ll, int> query(int node, int start, int end, int left, int right) {
        if (left > end || right < start) return make_pair(LLONG_MAX, -1);
        if (left <= start && end <= right) return tree[node];
        int mid = (start + end) >> 1;
        auto lsum = query(node * 2, start, mid, left, right);
        auto rsum = query(node * 2 + 1, mid + 1, end, left, right);
        return merge(lsum, rsum);
    }
    void update(int index, ll val) { update(1, 0, sz - 1, index, val); }
    pair<ll, int> query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

int N;
ll A[200001], P[200001], cnt[200001], inv[200001];
int l[200001];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 1; i <= N; ++i) cin >> P[i];
    for (int i = 1; i <= N; ++i) cin >> A[i];
    for (int i = 1; i <= N; ++i) inv[P[i]] = i;
    
    set<int> st;
    st.insert(0);
    for (int i = N; i >= 1; --i) {
        auto itr = st.lower_bound(inv[i]);
        --itr;
        l[inv[i]] = *itr;
        st.insert(inv[i]);
    }

    vector<ll> a(N + 1);
    for (int i = 1; i <= N; ++i) {
        a[i] = A[P[i]];
        cnt[i] = 1;
    }
    SegmentTree seg {a};
    ll ans = 0;
    for (int i = 2; i <= N; ++i) {
        auto [dif, idx] = seg.query(max(1, l[i]), i - 1);
        ans += dif;
        ++cnt[idx];
        seg.update(idx, A[P[idx]] * (2 * cnt[idx] - 1));
    }
    cout << ans;
}