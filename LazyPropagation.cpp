#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void init(vector<ll> &a, vector<ll> &tree, int node, int start, int end) {
    if (start == end) {
        tree[node] = a[start];
    } else {
        init(a, tree, node * 2, start, (start + end) / 2);
        init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
}

void update_lazy(vector<ll> &tree, vector<ll> &lazy, int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void update_range(vector<ll> &tree, vector<ll> &lazy, int node, int start, int end, int left, int right, ll diff) {
    update_lazy(tree, lazy, node, start, end);
    if (left > end || right < start) {
        return;
    }
    if (left <= start && end <= right) {
        tree[node] += (end - start + 1) * diff;
        if (start != end) {
            lazy[node * 2] += diff;
            lazy[node * 2 + 1] += diff;
        }
        return;
    }
    update_range(tree, lazy, node * 2, start, (start + end) / 2, left, right, diff);
    update_range(tree, lazy, node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(vector<ll> &tree, vector<ll> &lazy, int node, int start, int end, int left, int right) {
    update_lazy(tree, lazy, node, start, end);
    if (left > end || right < start) {
        return 0;
    }
    if (left <= start && end <= right) {
        return tree[node];
    }
    ll lsum = query(tree, lazy, node * 2, start, (start+end) / 2, left, right);
    ll rsum = query(tree, lazy, node * 2 + 1, (start+end) / 2 + 1, end, left, right);
    return lsum + rsum;
}

void solve() {
	int n;
	// 0 ~ n - 1
    vector<ll> a(n);
    int h = (int)ceil(log2(n));
    int tree_size = (1 << (h + 1));
    vector<ll> tree(tree_size);
    vector<ll> lazy(tree_size);
    // init(a, tree, 1, 0, n - 1);
	// update_range(tree, lazy, 1, 0, n - 1, left - 1, right - 1, diff);
	// query(tree, lazy, 1, 0, n - 1, left - 1, right - 1);
}