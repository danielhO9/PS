#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void init(vector<LL> &a, vector<LL> &tree, int node, int start, int end) {
    if (start == end) {
        tree[node] = a[start];
    } else {
        init(a, tree, node * 2, start, (start + end) / 2);
        init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }
}

void update_lazy(vector<LL> &tree, vector<LL> &lazy, int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += lazy[node];
        if (start != end) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
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
        tree[node] += diff;
        if (start != end) {
            lazy[node * 2] += diff;
            lazy[node * 2 + 1] += diff;
        }
        return;
    }
    update_range(tree, lazy, node * 2, start, (start + end) / 2, left, right, diff);
    update_range(tree, lazy, node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff);
    tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
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
    return max(lsum, rsum);
}

void solve() {
	int n, q; cin >> n >> q;
	LL asum = 0;
	vector<LL> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		asum += a[i];
	}
	vector<LL> b(n); for (int i = 0; i < n; ++i) cin >> b[i];
	vector<LL> c(n); for (int i = 0; i < n - 1; ++i) cin >> c[i];
	vector<LL> dif(n); for (int i = 0; i < n; ++i) dif[i] = a[i] - b[i];
	vector<LL> arr(n);
	for (int i = n - 1; i >= 0; --i) {
		if (i == n - 1) arr[i] = dif[i];
		else arr[i] = arr[i + 1] + dif[i];
	}
    int h = (int)ceil(log2(n));
    int tree_size = (1 << (h + 1));
    vector<LL> tree(tree_size);
    vector<LL> lazy(tree_size);
    init(arr, tree, 1, 0, n - 1);
	while (q--) {
		int p; LL x, y, z; cin >> p >> x >> y >> z; --p;
		update_range(tree, lazy, 1, 0, n - 1, 0, p, x - y - dif[p]);
		asum -= a[p]; asum += x; dif[p] = x - y; a[p] = x;
		LL rem = max(0LL, query(tree, lazy, 1, 0, n - 1, 0, n - 1));
		cout << asum - rem << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}