#include <bits/stdc++.h>
using namespace std;

/**
 * Description: Segment Tree supports range queries and point updates efficiently.
 *  Useful for maintaining cumulative sums or other associative operations.
 * Time: Build O(N), Update O(\log N), Query O(\log N).
 */
struct SegmentTree {
    vector<int> arr;
    vector<int> tree;
    int sz;

    inline int merge(int a, int b) { return max(a, b); }
    SegmentTree() = default;
    SegmentTree(int sz): SegmentTree(vector<int>(sz, 0)) {} // TODO
    SegmentTree(const vector<int>& a) {
        sz = a.size();
        arr = a;
        int h = 32 - __builtin_clz(sz - 1);
        int tree_size = (1 << (h + 1));
        tree = vector<int>(tree_size);
        init(1, 0, sz - 1);
    }
    void init(int node, int start, int end) {
        if (start == end) tree[node] = arr[start];
        else {
            int mid = (start + end) / 2;
            init(node * 2, start, mid);
            init(node * 2 + 1, mid + 1, end);
            tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
        }
    }
    void update(int node, int start, int end, int index, int val) {
        if (index < start || index > end) return;
        if (start == end) {
            arr[index] = max(arr[index], val);
            tree[node] = arr[index];
            return;
        }
        int mid = (start + end) >> 1;
        update(node * 2, start, mid, index, val);
        update(node * 2 + 1, mid + 1, end, index, val);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }
    int query(int node, int start, int end, int left, int right) {
        if (left > end || right < start) return 0; // TODO
        if (left <= start && end <= right) return tree[node];
        int mid = (start + end) >> 1;
        int lsum = query(node * 2, start, mid, left, right);
        int rsum = query(node * 2 + 1, mid + 1, end, left, right);
        return merge(lsum, rsum);
    }
    void update(int index, int val) { update(1, 0, sz - 1, index, val); }
    int query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

int n, k;
int arr[300000];
int ord[300000];
const int INF = 1e9;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> arr[i];
    
    vector<int> num;
    num.push_back(-INF);
    num.push_back(2 * INF + 1);
    for (int i = 0; i < n; ++i) num.push_back(arr[i]);
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());
    
    for (int i = 0; i < n; ++i) ord[i] = lower_bound(num.begin(), num.end(), arr[i]) - num.begin();

    SegmentTree seg {(int) num.size()};

    for (int i = 0; i < n; ++i) {
        int val = arr[i] - k;
        auto itr = upper_bound(num.begin(), num.end(), val);
        --itr;
        int idx = itr - num.begin();

        int dp = seg.query(0, idx);

        val = arr[i] + k;
        itr = lower_bound(num.begin(), num.end(), val);
        idx = itr - num.begin();

        dp = max(dp, seg.query(idx, (int) num.size() - 1));
        
        seg.update(ord[i], dp + 1);
    }
    cout << seg.query(0, (int) num.size() - 1);
}