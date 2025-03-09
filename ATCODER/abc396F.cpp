#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct LazyPropagation {
	vector<ll> arr;
	vector<ll> tree;
	vector<ll> lazy;
	ll sz;

	inline ll merge(ll a, ll b) { return a + b; }

	void init(vector<ll>& a) {
		sz = a.size();
		arr = a;
		ll h = (ll)ceil(log2(sz));
		ll tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
		lazy = vector<ll>(tree_size);
		init_(1, 0, sz - 1);
	}

	void init_(ll node, ll start, ll end) {
		if (start == end) tree[node] = arr[start];
		else {
			init_(node * 2, start, (start + end) / 2);
			init_(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}

	void update_lazy(ll node, ll start, ll end) {
		if (lazy[node] != 0) {
			tree[node] += (end - start + 1) * lazy[node]; // modify
			if (start != end) {
				lazy[node * 2] = merge(lazy[node * 2], lazy[node]); // modify
				lazy[node * 2 + 1] = merge(lazy[node * 2 + 1], lazy[node]); // modify
			}
			lazy[node] = 0;
		}
	}

	void update_range(ll node, ll start, ll end, ll left, ll right, ll diff) {
		update_lazy(node, start, end);
		if (left > end || right < start) {
			return;
		}
		if (left <= start && end <= right) {
			tree[node] += (end - start + 1) * diff; // modify
			if (start != end) {
				lazy[node * 2] = merge(lazy[node * 2], diff); // modify
				lazy[node * 2 + 1] = merge(lazy[node * 2 + 1], diff); // modify
			}
			return;
		}
		update_range(node * 2, start, (start + end) / 2, left, right, diff);
		update_range(node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}

	ll query(ll node, ll start, ll end, ll left, ll right) {
		update_lazy(node, start, end);
		if (left > end || right < start) return 0; // modify
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return merge(lsum, rsum);
	}

	void update(ll left, ll right, ll val) { update_range(1, 0, sz - 1, left, right, val); }

	ll query(ll left, ll right) { return query(1, 0, sz - 1, left, right); }
} seg;

int N, M;
int A[200000];
vector<int> bezr[200000];

void solve() {
	cin >> N >> M;
	for (int i = 0; i < N; ++i) cin >> A[i];
	vector<ll> arr(N); seg.init(arr);
	vector<pair<int, int>> v;
	for (int i = 0; i < N; ++i) v.push_back({A[i], i});
	sort(v.begin(), v.end());
	vector<ll> narr(N);
	for (auto i: v) {
		if (i.second == N - 1) narr[i.second] = 0;
		else narr[i.second] = seg.query(i.second + 1, N - 1);
		seg.update(i.second, i.second, 1);
	}
	LazyPropagation nseg; nseg.init(narr);
	for (int i = 0; i < N; ++i) {
		int tmp = A[i] % M;
		if (tmp != 0) bezr[M - tmp].push_back(i);
	}
	for (int i = 0; i < M; ++i) {
		if (i == 0) {
			cout << nseg.query(0, N - 1) << '\n';
			continue;
		}
		for (auto j: bezr[i]) if (j != 0) nseg.update(0, j - 1, 1);
		for (auto j: bezr[i]) {
			int val = nseg.query(j, j);
			nseg.update(j, j, -val);
		}
		cout << nseg.query(0, N - 1) << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}