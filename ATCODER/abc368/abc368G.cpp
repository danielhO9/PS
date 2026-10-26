#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SegmentTree {
	vector<ll> arr;
	vector<ll> tree;
	int sz;

	void init(vector<ll>& a, int sz_) {
		sz = sz_;
		arr = a;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
		init_(1, 0, sz - 1);
	}
	void init_(int node, int start, int end) {
		if (start == end) tree[node] = arr[start];
		else {
			init_(node * 2, start, (start + end) / 2);
			init_(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = tree[node * 2] + tree[node * 2 + 1];
		}
	}
	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			arr[index] = val;
			tree[node] = val;
			return;
		}
		update(node * 2, start, (start + end) / 2, index, val);
		update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
	void update(int index, ll val) {
		update(1, 0, sz - 1, index, val);
	}
	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return 0;
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return lsum + rsum;
	}
	ll query(int left, int right) {
		return query(1, 0, sz - 1, left, right);
	}
} seg;

ll N, Q;
ll A[100001], B[100001];
set<ll> s;

ll query(ll l, ll r) {
	ll ret = 0ll;
	ll cur = l;
	while (true) {
		auto it = s.lower_bound(cur);
		if (it == s.end()) {
			ret += seg.query(cur, r);
			break;
		}
		ll idx = *it;
		if (idx > r) {
			ret += seg.query(cur, r);
			break;
		}
		ret += seg.query(cur, idx - 1);
		ret = max(ret + A[idx], ret * B[idx]);
		cur = idx + 1;
		if (cur > r) break;
	}
	return ret;
}

void solve() {
	cin >> N;
	for (int i = 1; i <= N; ++i) cin >> A[i];
	for (int i = 1; i <= N; ++i) cin >> B[i];
	for (int i = 1; i <= N; ++i) {
		if (B[i] != 1) s.insert(i);
	}
	int MAX_N = N + 1;
	vector<ll> arr(MAX_N);
	for (int i = 1; i <= N; ++i) arr[i] = A[i];
	seg.init(arr, MAX_N);
	cin >> Q;
	while (Q--) {
		int t; ll l, r; cin >> t >> l >> r;
		if (t == 1) {
			A[l] = r;
			seg.update(l, r);
		}
		else if (t == 2) {
			if (B[l] != 1) s.erase(l);
			B[l] = r;
			if (B[l] != 1) s.insert(l);
		} else cout << query(l, r) << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}