#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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

ll N, D, s, a, b;

void solve() {
	cin >> N >> D >> s >> a >> b;
	vector<ll> arr(N); seg.init(arr);
	ll sidx = 0;
	ll ans = 0;
	ll C, K;
	for (ll i = 1; i <= D; ++i) {
		C = s % N + 1;
		s = (s * a + b) % 1000000007;
		K = s % N + 1;
		s = (s * a + b) % 1000000007;
		ll mx = N - sidx;
		if (C > 0) {
			seg.update(sidx, i);
			if (sidx + min(mx, C) < N) seg.update(sidx + min(mx, C), -i);
			if (mx < C) {
				seg.update(0, i);
				if (C - mx < N) seg.update(C - mx, -i);
				sidx = C - mx;
			} else {
				sidx = sidx + min(mx, C);
			}
		}
		--K;
		ans += seg.query(0, (sidx + K) % N);
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}