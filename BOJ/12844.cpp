#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void init(vector<LL> &a, vector<LL> &tree, int node, int start, int end) {
    if (start == end) {
        tree[node] = a[start];
    } else {
        init(a, tree, node * 2, start, (start + end) / 2);
        init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
        tree[node] = tree[node * 2] ^ tree[node * 2 + 1];
    }
}

void update_lazy(vector<LL> &tree, vector<LL> &lazy, int node, int start, int end) {
    if (lazy[node] != 0) {
        if ((end - start + 1) % 2 == 1) tree[node] ^= lazy[node];
        if (start != end) {
            lazy[node * 2] ^= lazy[node];
            lazy[node * 2 + 1] ^= lazy[node];
        }
        lazy[node] = 0;
    }
}

void update_range(vector<LL> &tree, vector<LL> &lazy, int node, int start, int end, int left, int right, LL diff) {
    update_lazy(tree, lazy, node, start, end);
    if (left > end || right < start) {
        return;
    }
    if (left <= start && end <= right) {
        if ((end - start + 1) % 2 == 1) tree[node] ^= diff;
        if (start != end) {
            lazy[node * 2] ^= diff;
            lazy[node * 2 + 1] ^= diff;
        }
        return;
    }
    update_range(tree, lazy, node * 2, start, (start + end) / 2, left, right, diff);
    update_range(tree, lazy, node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff);
    tree[node] = tree[node * 2] ^ tree[node * 2 + 1];
}

LL query(vector<LL> &tree, vector<LL> &lazy, int node, int start, int end, int left, int right) {
    update_lazy(tree, lazy, node, start, end);
    if (left > end || right < start) {
        return 0;
    }
    if (left <= start && end <= right) {
        return tree[node];
    }
    LL lsum = query(tree, lazy, node * 2, start, (start+end) / 2, left, right);
    LL rsum = query(tree, lazy, node * 2 + 1, (start+end) / 2 + 1, end, left, right);
    return lsum ^ rsum;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<LL> a(n);
    int h = (int)ceil(log2(n));
    int tree_size = (1 << (h + 1));
    vector<LL> tree(tree_size);
    vector<LL> lazy(tree_size);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    init(a, tree, 1, 0, n-1);
	int m; cin >> m;
    while (m--) {
        int what;
        cin >> what;
        if (what == 1) {
            int left, right; LL diff;
            cin >> left >> right >> diff;
            update_range(tree, lazy, 1, 0, n - 1, left, right, diff);
        } else if (what == 2) {
            int left, right;
            cin >> left >> right;
            cout << query(tree, lazy, 1, 0, n - 1, left, right) << '\n';
        }
    }
    return 0;
}