#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SegmentTree {
	vector<ll> arr;
	vector<pair<ll, ll>> tree;
	int sz;

	inline pair<ll, ll> merge(pair<ll, ll>& a, pair<ll, ll>& b) {
		if (a.second <= b.second) return a;
		else return b;
	}

	void init(vector<ll>& a) {
		sz = a.size();
		arr = a;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<pair<ll, ll>>(tree_size);
		init(1, 0, sz - 1);
	}

	void init(int node, int start, int end) {
		if (start == end) tree[node] = {start, arr[start]};
		else {
			init(node * 2, start, (start + end) / 2);
			init(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}

	pair<ll, ll> query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return {0, LLONG_MAX}; // modify
		if (left <= start && end <= right) return tree[node];
		pair<ll, ll> lsum = query(node * 2, start, (start + end) / 2, left, right);
		pair<ll, ll> rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return merge(lsum, rsum);
	}

	pair<ll, ll> query(int left, int right) { return query(1, 0, sz - 1, left, right); }
} seg;

ll n;
ll a[100000];

void solve() {
	cin >> n;
	for (ll i = 0; i < n; ++i) cin >> a[i];
	vector<ll> v(n);
	for (int i = 0; i < n; ++i) v[i] = a[i];
	seg.init(v);
	vector<bool> vis(n, false);
	vector<ll> ans;
	int s = 0;
	ll pmn = LLONG_MAX;
	while (true) {
		if (s == n) break;
		auto mn = seg.query(s, n - 1);
		if (mn.second > pmn) break;
		ans.push_back(mn.second);
		vis[mn.first] = true;
		if (mn.first > s) pmn = min(pmn, seg.query(s, mn.first - 1).second + 1);
		s = mn.first + 1;
	}
	vector<ll> tmp;
	for (int i = 0; i < n; ++i) if (!vis[i]) tmp.push_back(a[i] + 1);
	sort(tmp.begin(), tmp.end());
	for (auto i: tmp) ans.push_back(i);
	for (auto i: ans) cout << i << ' ';
	cout << '\n';
	

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	ll t; cin >> t;
	while (t--) solve();
}