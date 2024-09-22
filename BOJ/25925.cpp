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
		init(1, 0, sz - 1);
	}
	void init(int node, int start, int end) {
		if (start == end) tree[node] = arr[start];
		else {
			init(node * 2, start, (start + end) / 2);
			init(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
		}
	}
	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			arr[index] = max(arr[index], val);
			tree[node] = max(tree[node], val);
			return;
		}
		update(node * 2, start, (start + end) / 2, index, val);
		update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
		tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
	}
	void update(int index, ll val) {
		update(1, 0, sz - 1, index, val);
	}
	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return 0;
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return max(lsum, rsum);
	}
	ll query(int left, int right) {
		return query(1, 0, sz - 1, left, right);
	}
};

int N, Q;
ll X[500000], Y[500000];
ll ans[500000];
unordered_map<ll, int> summ;
unordered_map<ll, int> subm;

void solve() {
	cin >> N >> Q;
	set<ll> sum, sub;
	for (int i = 0; i < N; ++i) {
		cin >> X[i] >> Y[i];
		sum.insert(X[i] + Y[i]);
		sub.insert(Y[i] - X[i]);
	}
	int idx = 0;
	for (auto i: sum) summ[i] = idx++;
	idx = 0;
	for (auto i: sub) subm[i] = idx++;
	int MAX_N = N;
	vector<ll> arr(MAX_N);
	SegmentTree segsum, segsub;
	segsum.init(arr, MAX_N);
	segsub.init(arr, MAX_N);
	vector<pair<int, int>> v;
	for (int i = 0; i < N; ++i) v.push_back({Y[i], i});
	sort(v.begin(), v.end());
	for (int i = 0; i < N; ++i) {
		ll x = X[v[i].second], y = Y[v[i].second];
		ll tmp = 0;
		tmp = max(tmp, segsum.query(summ[x + y], N - 1));
		tmp = max(tmp, segsub.query(subm[y - x], N - 1));
		++tmp;
		ans[v[i].second] = tmp;
		segsum.update(summ[x + y], tmp);
		segsub.update(subm[y - x], tmp);
	}
	while (Q--) {
		int q; cin >> q; --q;
		cout << ans[q] << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}