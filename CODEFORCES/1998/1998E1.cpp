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
		if (start == end) tree[node] = start;
		else {
			init_(node * 2, start, (start + end) / 2);
			init_(node * 2 + 1, (start + end) / 2 + 1, end);

			tree[node] = arr[tree[node * 2]] < arr[tree[node * 2 + 1]] ? tree[node * 2 + 1] : tree[node * 2];
		}
	}
	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return 0;
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return arr[lsum] < arr[rsum] ? rsum : lsum;
	}
	ll query(int left, int right) {
		return query(1, 0, sz - 1, left, right);
	}
} seg;

int n, x;
ll psum[200002];
ll bad[200002];
vector<ll> a;

void dnq(int l, int r) {
	if (l > r) return;
	int m = seg.query(l, r);
	// cout << l << ' ' << r << ' ' << m << '\n';
	ll lsum = psum[m - 1] - psum[l - 1];
	ll rsum = psum[r] - psum[m];
	if (lsum < a[m]) {
		++bad[l];
		--bad[m];
	} else {
		dnq(l, m - 1);
	}
	if (rsum < a[m]) {
		++bad[m + 1];
		--bad[r + 1];
	} else {
		dnq(m + 1, r);
	}
}

void solve() {
	cin >> n >> x;
	a = vector<ll>(n + 1);
	for (int i = 1; i <= n; ++i) cin >> a[i];
	seg.init(a, n + 1);
	for (int i = 1; i <= n; ++i) {
		psum[i] = psum[i - 1] + a[i];
		bad[i] = 0;
	}
	dnq(1, n);
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		bad[i] += bad[i - 1];
		if (bad[i] == 0) ++ans;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}