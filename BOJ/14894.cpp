#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node { int l, r; ll val; };

struct PST {
	vector<Node> tree;
	vector<int> root; // 1-index (0: dummy)
	int sz;

	PST(int sz): sz(sz) {
        tree.resize(1);
        root.resize(1);
	}
    // p에서 c로 분기
	void newRoot(int c, int p) {
        assert(p < root.size());
        while (root.size() <= c) root.push_back(0);
        root[c] = tree.size();
		tree.push_back(Node{tree[root[p]]});
        return;
	}
	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		tree[node].val += val;
		if (start == end) return;
		int mid = (start + end) / 2;
		if (index <= mid) {
			int lidx = tree[node].l;
			tree[node].l = tree.size();
			tree.push_back(Node{tree[lidx]});
			update(tree[node].l, start, mid, index, val);
		}
		if (index > mid) {
			int ridx = tree[node].r;
			tree[node].r = tree.size();
			tree.push_back(Node{tree[ridx]});
			update(tree[node].r, mid + 1, end, index, val);
		}
	}
	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return 0;
		if (left <= start && end <= right) return tree[node].val;
        int mid = (start + end) / 2;
		ll lsum = query(tree[node].l, start, mid, left, right);
		ll rsum = query(tree[node].r, mid + 1, end, left, right);
		return lsum + rsum;
	}
    int kth(int l, int r, int start, int end, ll k) {
        if (start == end) return start;
        ll tmp = tree[tree[r].l].val - tree[tree[l].l].val;
        int mid = (start + end) / 2;
        if (tmp >= k) return kth(tree[l].l, tree[r].l, start, mid, k);
        else return kth(tree[l].r, tree[r].r, mid + 1, end, k - tmp);
    }
    void update(int rt, int index, ll val) {
        assert(rt < root.size());
        update(root[rt], 0, sz - 1, index, val);
    }
	ll query(int rt, int left, int right) {
        assert(rt < root.size());
        return query(root[rt], 0, sz - 1, left, right);
    }
    int kth(int l, int r, int k) {
        assert(l - 1 < root.size() && r < root.size());
        return kth(root[l - 1], root[r], 0, sz - 1, k);
    }
};

int N;
int a[500000];
int inv[500001];

ll dnc(PST& seg, int l, int r) {
    if (l == r) return 0;
    ll ret = r - l + 1;
    int len = r - l + 1;
    ll piv = a[seg.kth(l, r, (len + 1) / 2)];
    if (l < piv) ret += dnc(seg, l, piv - 1);
    if (piv < r) ret += dnc(seg, piv + 1, r);
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> a[i];
    for (int i = 0; i < N; ++i) inv[a[i]] = i;
    PST seg {N};
    for (int i = 1; i <= N; ++i) {
        seg.newRoot(i, i - 1);
        seg.update(i, inv[i], 1);
    }
    cout << dnc(seg, 1, N);
}