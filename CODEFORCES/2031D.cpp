#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
int a[500000];

struct SegmentTree {
	vector<ll> arr;
	vector<ll> tree;
	int sz;

	inline ll merge(ll a, ll b) { return max(a, b); }

	void init(vector<ll>& a) {
		sz = a.size();
		arr = a;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
		init(1, 0, sz - 1);
	}

	void init(int node, int start, int end) {
		if (start == end) {
			tree[node] = -1;
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
			tree[node] = index;
			return;
		}
		update(node * 2, start, (start + end) / 2, index, val);
		update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}

	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return -1; // modify
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return merge(lsum, rsum);
	}

	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }

	ll query(int left, int right) { return query(1, 0, sz - 1, left, right); }
} seg;

struct SegmentTree2 {
	vector<ll> arr;
	vector<ll> tree;
	int sz;

	inline ll merge(ll a, ll b) { return max(a, b); }

	void init(vector<ll>& a) {
		sz = a.size();
		arr = a;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
		init(1, 0, sz - 1);
	}

	void init(int node, int start, int end) {
		if (start == end) tree[node] = arr[start];
		else {
			init(node * 2, start, (start + end) / 2);
			init(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}

	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return -1; // modify
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return merge(lsum, rsum);
	}

	ll query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	vector<pair<int, int>> v;
	for (int i = 0; i < n; ++i) v.push_back({a[i], i});
	sort(v.begin(), v.end());
	vector<ll> tmp(n);
	seg.init(tmp);

	vector<ll> right(n);
	for (auto [_, i]: v) {
		seg.update(i, 1);
		right[i] = seg.query(i, n - 1);
	}
	SegmentTree2 seg2; seg2.init(right);

	vector<ll> val(n);
	for (int i = 0; i < n; ++i) val[i] = a[i];
	SegmentTree2 seg3; seg3.init(val);
	int curl = -1;
	
	for (int i = 0; i < n; ++i) {
		curl = max(curl, i);
		while (true) {
			int ncurl = seg2.query(i, curl);
			if (ncurl == curl) break;
			curl = ncurl;
		}
		// cout << curl << ' ';
		cout << seg3.query(0, curl) << ' ';
		
	}
	cout << '\n';


}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}

/*
1
8
2 4 1 6 3 8 5 7
*/