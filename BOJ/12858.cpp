#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll lgcd(ll a, ll b) {
	if (a < b) swap(a, b);
	if (b == -1) return a;
	if (b == 0) return a;
	return lgcd(b, a % b);
}

struct SegmentTree {
	vector<ll> arr;
	vector<ll> tree;
	int sz;
	int type;

	inline ll agg(ll a, ll b) { 
		if (type == 0) return a + b;
		else return lgcd(a, b);
	}

	void init(vector<ll>& a, int _type) {
		sz = a.size();
		type = _type;
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
			tree[node] = agg(tree[node * 2], tree[node * 2 + 1]);
		}
	}

	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			if (type == 0) {
				arr[index] = agg(arr[index], val);
				tree[node] = agg(tree[node], val);
			} else {
				arr[index] = val;
				tree[node] = val;
			}
			return;
		}
		update(node * 2, start, (start + end) / 2, index, val);
		update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
		tree[node] = agg(tree[node * 2], tree[node * 2 + 1]);
	}

	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }

	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) {
			if (type == 0) return 0;
			else return -1;
		}
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return agg(lsum, rsum);
	}

	ll query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

int N, Q;
ll A[100001];

void solve() {
	cin >> N;
	for (int i = 1; i <= N; ++i) cin >> A[i];
	vector<ll> a_sum(N + 1);
	for (int i = 1; i <= N; ++i) a_sum[i] = A[i] - A[i - 1];
	vector<ll> a_gcd(N + 1);
	for (int i = 1; i <= N; ++i) a_gcd[i] = abs(A[i] - A[i - 1]);
	SegmentTree seg, seg_gcd;
	seg.init(a_sum, 0); seg_gcd.init(a_gcd, 1);
	cin >> Q;
	while (Q--) {
		ll T; int a, b; cin >> T >> a >> b;
		if (T == 0) {
			if (a == b) cout << seg.query(0, a) << '\n';
			else cout << lgcd(seg.query(0, a), seg_gcd.query(a + 1, b)) << '\n';
		} else {
			seg.update(a, T);
			ll paval = seg.query(0, a - 1);
			ll aval = seg.query(0, a);
			seg_gcd.update(a, abs(paval - aval));
			if (b < N) {
				seg.update(b + 1, -T);
				ll pbval = seg.query(0, b);
				ll bval = seg.query(0, b + 1);
				seg_gcd.update(b + 1, abs(pbval - bval));
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}