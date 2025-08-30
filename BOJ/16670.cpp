#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
	ll t, d, sm;

	Node() = default;
};

struct SegmentTree {
	vector<Node> tree;
	int sz;

	inline Node merge(const Node& l, const Node& r) {
        if (l.sm == 0) return r;
        if (r.sm == 0) return l;
        Node ret{};
        ret.t = l.t;
        ret.d = max(r.t + r.d - l.t, l.d + r.sm);
        ret.sm = l.sm + r.sm;
		return ret;
	}
	SegmentTree() = default;
	SegmentTree(const int _sz) {
		sz = _sz;
		int h = (int) ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<Node>(tree_size);
	}
	void update(int node, int start, int end, int index, ll t, ll d) {
		if (index < start || index > end) return;
		if (start == end) {
			tree[node] = Node {t, d, d};
			return;
		}
		int mid = (start + end) / 2;
		update(node * 2, start, mid, index, t, d);
		update(node * 2 + 1, mid + 1, end, index, t, d);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}
	Node query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return Node {0, 0, 0};
		if (left <= start && end <= right) return tree[node];
		int mid = (start + end) / 2;
		Node l = query(node * 2, start, mid, left, right);
		Node r = query(node * 2 + 1, mid + 1, end, left, right);
		return merge(l, r);
	}
	void update(int index, ll t, ll d) { update(1, 0, sz - 1, index, t, d); }
	Node query(int left, int right) { return query(1, 0, sz - 1, left, right); }
} seg;

struct Query {
    int t, a, b;
};

int q;
vector<Query> queries;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> q;
    vector<int> v;
    for (int i = 0; i < q; ++i) {
        char c; cin >> c;
        if (c == '+') {
            int t, d; cin >> t >> d;
            queries.push_back(Query {0, t, d});
            v.push_back(t);
        } else if (c == '-') {
            int a; cin >> a; --a;
            queries.push_back(Query {1, a, 0});
        } else {
            int t; cin >> t;
            queries.push_back(Query {2, t, 0});
        }
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    seg = SegmentTree {(int) v.size()};
    for (int i = 0; i < q; ++i) {
        if (queries[i].t == 0) {
            int idx = lower_bound(v.begin(), v.end(), queries[i].a) - v.begin();
            seg.update(idx, queries[i].a, queries[i].b);
        } else if (queries[i].t == 1) {
            int idx = lower_bound(v.begin(), v.end(), queries[queries[i].a].a) - v.begin();
            seg.update(idx, 0, 0);
        } else {
            int idx = upper_bound(v.begin(), v.end(), queries[i].a) - v.begin();
            if (idx == 0) cout << 0 << '\n';
            else {
                --idx;
                auto Node = seg.query(0, idx);
                if (Node.sm == 0) cout << 0 << '\n';
                else cout << max(Node.t + Node.d - queries[i].a, 0ll) << '\n';
            }
        }
    }
}