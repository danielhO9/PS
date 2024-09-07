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
	int ridx;

	void init(int sz_) {
		sz = sz_;
		ridx = 1;
		root.resize(sz);
		root[0] = 1;
	}
	void changeRoot(int idx) { ridx = root[idx]; }
	void setRoot(int idx) {
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
	ll query2(int L, int R, int start, int end, ll x, int mask) {
		if (start == end) return start;
		if ((x >> mask) & 1) {
			if (tree[tree[R].l].val - tree[tree[L].l].val) return query2(tree[L].l, tree[R].l, start, (start + end) / 2, x, mask - 1);
			else return query2(tree[L].r, tree[R].r, (start + end) / 2 + 1, end, x, mask - 1);
		} else {
			if (tree[tree[R].r].val - tree[tree[L].r].val) return query2(tree[L].r, tree[R].r, (start + end) / 2 + 1, end, x, mask - 1);
			else return query2(tree[L].l, tree[R].l, start, (start + end) / 2, x, mask - 1);
		}
	}
	ll query2(int L, int R, int x) {
		return query2(root[L - 1], root[R], 0, sz - 1, x, 18);
	}
	ll query4(int L, int R, int x) {
		return query(R, 0, x) - query(L - 1, 0, x);
	}
	ll query5(int L, int R, int start, int end, int k) {
		if (start == end) return start;
		ll tmp = tree[tree[R].l].val - tree[tree[L].l].val;
		if (tmp >= k) return query5(tree[L].l, tree[R].l, start, (start + end) / 2, k);
		else return query5(tree[L].r, tree[R].r, (start + end) / 2 + 1, end, k - tmp);
	}
	ll query5(int L, int R, int k) {
		return query5(root[L - 1], root[R], 0, sz - 1, k);
	}
} seg;

void solve() {
	seg.init(1 << 19);
	int M; cin >> M;
	int now = 0;
	while (M--) {
		int t; cin >> t;
		if (t == 1) {
			int x; cin >> x;
			seg.setRoot(++now);
			seg.update(now, x, 1);
		}
		if (t == 2) {
			int L, R, x; cin >> L >> R >> x;
			cout << seg.query2(L, R, x) << '\n';
		}
		if (t == 3) {
			int k; cin >> k;
			now -= k; now = max(now, 0);
			seg.changeRoot(now);
		}
		if (t == 4) {
			int L, R, x; cin >> L >> R >> x;
			cout << seg.query4(L, R, x) << '\n';
		}
		if (t == 5) {
			int L, R, x; cin >> L >> R >> x;
			cout << seg.query5(L, R, x) << '\n';
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}