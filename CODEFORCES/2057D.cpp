#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
	// left max - right min, right max - left min
	ll val1, val2, max, min;
};

Node merge(Node l, Node r) {
	Node ret;
	ret.val1 = max({l.val1, r.val1, l.max - r.min});
	ret.val2 = max({l.val2, r.val2, r.max - l.min});
	ret.max = max(l.max, r.max);
	ret.min = min(l.min, r.min);
	return ret;
}

struct SegmentTree {
	vector<ll> a;
	vector<Node> tree;
	int sz;

	void init(vector<ll>& arr) {
		sz = arr.size();
		a = arr;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<Node>(tree_size);
		init(1, 0, sz - 1);
	}

	void init(int node, int start, int end) {
		if (start == end) {
			tree[node] = {0, 0, a[start], a[start]};
		}
		else {
			init(node * 2, start, (start + end) / 2);
			init(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}

	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			a[index] = val;
			tree[node] = {0, 0, val, val};
			return;
		}
		update(node * 2, start, (start + end) / 2, index, val);
		update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}

	Node query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return {-20000000000, -20000000000, -20000000000, 20000000000};
		if (left <= start && end <= right) return tree[node];
		Node l = query(node * 2, start, (start + end) / 2, left, right);
		Node r = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return merge(l, r);
	}

	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }

	Node query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

ll n, q;
ll a[200001];

void solve() {
	cin >> n >> q;
	for (ll i = 1; i <= n; ++i) cin >> a[i];
	vector<ll> ap(n + 1), am(n + 1);
	for (ll i = 1; i <= n; ++i) ap[i] = a[i] + i;
	for (ll i = 1; i <= n; ++i) am[i] = a[i] - i;
	SegmentTree segp, segm;
	segp.init(ap); segm.init(am);
	cout << max(segp.query(1, n).val1, segm.query(1, n).val2) << '\n';
	while (q--) {
		ll p, x; cin >> p >> x;
		segp.update(p, x + p);
		segm.update(p, x - p);
		cout << max(segp.query(1, n).val1, segm.query(1, n).val2) << '\n';
	}

	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}