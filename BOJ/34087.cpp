#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

ll N, M, K;
ll A[100001], a[100001];

/**
 * Description: Segment Tree supports range queries and point updates efficiently.
 *  Useful for maintaining cumulative sums or other associative operations.
 * Time: Build O(N), Update O(\log N), Query O(\log N).
 */
struct SegmentTree {
    vector<pll> arr;
    vector<pll> tree;
    int sz;

    inline pll merge(pll a, pll b) { return make_pair(a.first + b.first, a.second + b.second); }
    SegmentTree() = default;
    SegmentTree(int sz): SegmentTree(vector<pll>(sz, {0, 0})) {} // TODO
    SegmentTree(const vector<pll>& a) {
        sz = a.size();
        arr = a;
        int h = 32 - __builtin_clz(sz - 1);
        int tree_size = (1 << (h + 1));
        tree = vector<pll>(tree_size);
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
            arr[index].first += val;
            ++arr[index].second;
            tree[node] = arr[index];
            return;
        }
        int mid = (start + end) >> 1;
        update(node * 2, start, mid, index, val);
        update(node * 2 + 1, mid + 1, end, index, val);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }
    pll query(int node, int start, int end, int left, int right) {
        if (left > end || right < start) return {0, 0}; // TODO
        if (left <= start && end <= right) return tree[node];
        int mid = (start + end) >> 1;
        pll lsum = query(node * 2, start, mid, left, right);
        pll rsum = query(node * 2 + 1, mid + 1, end, left, right);
        return merge(lsum, rsum);
    }
    void update(int index, ll val) { update(1, 0, sz - 1, index, val); }
    pll query(int left, int right) { return query(1, 0, sz - 1, left, right); }
} seg;

vector<ll> v;
ll ord[100001];

pll f(ll x) {
    seg = SegmentTree {(int) v.size()};
    pll ret = {0, 0};
    for (int i = 0; i <= N; ++i) {
        seg.update(ord[i], a[i]);
        ll val = a[i] - x;
        int itr = upper_bound(v.begin(), v.end(), val) - v.begin();
        if (itr == 0) continue;
        auto tmp = seg.query(0, itr - 1);
        ret.second += tmp.second;
        ret.first += a[i] * tmp.second - tmp.first;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M >> K;
    for (int i = 1; i <= N; ++i) cin >> A[i];
    for (int i = 1; i <= N; ++i) A[i] += A[i - 1];
    for (int i = 0; i <= N; ++i) a[i] = A[i] - K * i;

    for (int i = 0; i <= N; ++i) v.push_back(a[i]);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    for (int i = 0; i <= N; ++i) ord[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();

    auto tmp = f(1);
    if (tmp.second <= M) {
        cout << A[N] + tmp.first;
        return 0;
    }

    ll l = 1, r = 1e16;
    while (l + 1 < r) {
        ll mid = (l + r) >> 1;
        tmp = f(mid);
        if (tmp.second > M) l = mid;
        else r = mid;
    }

    tmp = f(l);
    cout << A[N] + tmp.first - l * (tmp.second - M);
    return 0;
}