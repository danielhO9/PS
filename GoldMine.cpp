#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
	ll lMax, rMax, max, sum;
};

struct SegmentTree {
	vector<ll> arr;
	vector<Node> tree;
	int sz;

	inline Node merge(Node l, Node r) {
		Node ret;
		ret.lMax = max(l.lMax, l.sum + r.lMax);
		ret.rMax = max(r.rMax, r.sum + l.rMax);
		ret.max = max({l.max, r.max, l.rMax + r.lMax});
		ret.sum = l.sum + r.sum;
		return ret;
	}

	void init(vector<ll>& a) {
		sz = a.size();
		arr = a;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<Node>(tree_size);
		init(1, 0, sz - 1);
	}

	void init(int node, int start, int end) {
		if (start == end) {
			tree[node] = {arr[start], arr[start], arr[start], arr[start]};
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
			arr[index] = val;
			tree[node] = {val, val, val, val};
			return;
		}
		update(node * 2, start, (start + end) / 2, index, val);
		update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}

	Node query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return {INT32_MIN, INT32_MIN, INT32_MIN, INT32_MIN};
		if (left <= start && end <= right) return tree[node];
		Node l = query(node * 2, start, (start + end) / 2, left, right);
		Node r = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return merge(l, r);
	}

	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }

	Node query(int left, int right) { return query(1, 0, sz - 1, left, right); }
} seg;