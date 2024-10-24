#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
	int l, r;
	ll val;
};

struct PST {
	vector<Node> tree = {{0, 0, 0}, {0, 0, 0}};
	vector<int> root;
	int sz;
	int ridx; // current root = root[ridx]

	void init(int sz_) {
		sz = sz_;
		ridx = 1;
		root.resize(sz);
		root[0] = 1;
	}
	void changeRoot(int idx) { ridx = root[idx]; }
	
	void newRoot(int idx) {
        root[idx] = tree.size();
		tree.push_back({tree[ridx].l, tree[ridx].r, tree[ridx].val});
		ridx = root[idx];
	}
	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		tree[node].val += val;
		if (start == end) return;
		int mid = (start + end) / 2;
		if (index <= mid) {
			int lidx = tree[node].l;
			tree[node].l = tree.size();
			tree.push_back({tree[lidx].l, tree[lidx].r, tree[lidx].val});
			update(tree[node].l, start, mid, index, val);
		}
		if (index > mid) {
			int ridx = tree[node].r;
			tree[node].r = tree.size();
			tree.push_back({tree[ridx].l, tree[ridx].r, tree[ridx].val});
			update(tree[node].r, mid + 1, end, index, val);
		}
	}
	void update(int rt, int index, ll val) {
		update(root[rt], 0, sz - 1, index, val);
	}
	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return 0;
		if (left <= start && end <= right) return tree[node].val;
		ll lsum = query(tree[node].l, start, (start + end) / 2, left, right);
		ll rsum = query(tree[node].r, (start + end) / 2 + 1, end, left, right);
		return lsum + rsum;
	}
	ll query(int rt, int left, int right) {
		return query(root[rt], 0, sz - 1, left, right);
	}
} seg;

void solve() {
	// root(vector) size
	seg.init(1e5 + 1);
}