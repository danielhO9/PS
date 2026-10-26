#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
    ll lval, rval;
	ll lmx, rmx, mx;
    bool same;
    Node() = default;
    Node(ll val): lval(val), rval(val), lmx(1), rmx(1), mx(1), same(true) {}
};

struct SegmentTree {
	vector<ll> arr;
	vector<Node> tree;
	int sz;

	inline Node merge(const Node& l, const Node& r) {
        if (l.lval == 26) return r;
        if (r.rval == 26) return l;
		Node ret{};
        ret.lval = l.lval;
        ret.rval = r.rval;
        if (l.same && l.rval == r.lval) ret.lmx = l.mx + r.lmx;
        else ret.lmx = l.lmx;
        if (r.same && l.rval == r.lval) ret.rmx = l.rmx + r.mx;
        else ret.rmx = r.rmx;
        ret.mx = max({ret.lmx, ret.rmx, l.mx, r.mx});
        if (l.rval == r.lval) ret.mx = max(ret.mx, l.rmx + r.lmx);
        ret.same = (l.same && r.same && l.rval == r.lval);
		return ret;
	}
	SegmentTree() = default;
	SegmentTree(const vector<ll>& a) {
		sz = a.size();
		arr = a;
		int h = (int) ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<Node>(tree_size);
		init(1, 0, sz - 1);
	}
	void init(int node, int start, int end) {
		if (start == end) tree[node] = Node {arr[start]};
		else {
			int mid = (start + end) / 2;
			init(node * 2, start, mid);
			init(node * 2 + 1, mid + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}
	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			arr[index] = val;
			tree[node] = Node {arr[index]};
			return;
		}
		int mid = (start + end) / 2;
		update(node * 2, start, mid, index, val);
		update(node * 2 + 1, mid + 1, end, index, val);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}
	Node query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return Node {26};
		if (left <= start && end <= right) return tree[node];
		int mid = (start + end) / 2;
		Node l = query(node * 2, start, mid, left, right);
		Node r = query(node * 2 + 1, mid + 1, end, left, right);
		return merge(l, r);
	}
	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }
	Node query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

int N, Q;
string S;

void solve() {
    cin >> N >> Q;
    cin >> S;
    vector<ll> a(N);
    for (int i = 0; i < N; ++i) a[i] = S[i] - 'a';
    SegmentTree seg {a};
    while (Q--) {
        int t; cin >> t;
        if (t == 1) {
            int i; char x; cin >> i >> x; --i;
            seg.update(i, x - 'a');
        } else {
            int l, r; cin >> l >> r; --l; --r;
            cout << seg.query(l, r).mx << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}