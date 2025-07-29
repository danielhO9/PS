#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
	ll val[4];

	Node() { memset(val, 0, sizeof(val)); }
	Node(ll x): Node() { val[3] = x; }
};

struct SegmentTree {
	vector<ll> arr;
	vector<Node> tree;
	int sz;

	inline Node merge(const Node& l, const Node& r) {
		Node ret{};
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) for (int k = 0; k < 4; ++k) {
                if ((j & 1) && (k >> 1)) continue;
                if (!(i & 1) && (k & 1)) continue;
                if (!(i >> 1) && (j >> 1)) continue;
                ret.val[i] = max(ret.val[i], l.val[j] + r.val[k]);
            }
        }
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
		if (left > end || right < start) return Node {INT32_MIN};
		if (left <= start && end <= right) return tree[node];
		int mid = (start + end) / 2;
		Node l = query(node * 2, start, mid, left, right);
		Node r = query(node * 2 + 1, mid + 1, end, left, right);
		return merge(l, r);
	}
	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }
	Node query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

int N, D;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> D;
    vector<ll> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];
    SegmentTree seg {a};
    ll ans = 0;
    while (D--) {
        ll i, d; cin >> i >> d; --i;
        seg.update(i, d);
        auto ret = seg.query(0, N - 1);
        ans += *max_element(ret.val, ret.val + 4);
    }
    cout << ans;
}