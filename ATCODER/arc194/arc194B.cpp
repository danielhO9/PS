#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
ll P[200000];

struct SegmentTree {
	vector<ll> arr;
	vector<ll> tree;
	int sz;

	inline ll merge(ll a, ll b) { return a + b; }

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

	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			arr[index] += val; // modify
			tree[node] += val; // modify
			return;
		}
		update(node * 2, start, (start + end) / 2, index, val);
		update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}

	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return 0; // modify
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return merge(lsum, rsum);
	}

	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }

	ll query(int left, int right) { return query(1, 0, sz - 1, left, right); }
} seg;

ll f(ll l, ll r) {
	return r * (r + 1) / 2 - l * (l + 1) / 2;
}

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> P[i];
	vector<ll> arr(N + 1, 0); seg.init(arr);
	vector<ll> inv(N + 1);
	for (int i = 0; i < N; ++i) inv[P[i]] = i;
	vector<ll> cnt(N + 1);
	for (int i = N; i >= 1; --i) {
		cnt[i] = seg.query(0, inv[i]);
		seg.update(inv[i], 1);
	}
	ll ans = 0;
	for (int i = 1; i <= N; ++i) {
		ll cur = inv[i] - cnt[i];
		ll nxt = i - 1;
		ans += f(cur, nxt);
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}