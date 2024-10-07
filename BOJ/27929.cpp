#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

pll add(pll& a, pll& b) {
	return {a.first + b.first, a.second + b.second};
}

struct SegmentTree {
	vector<pll> arr;
	vector<pll> tree;
	int sz;

	void init(vector<pll>& a, int sz_) {
		sz = sz_;
		arr = a;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<pll>(tree_size);
		init(1, 0, sz - 1);
	}
	void init(int node, int start, int end) {
		if (start == end) tree[node] = arr[start];
		else {
			init(node * 2, start, (start + end) / 2);
			init(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = add(tree[node * 2], tree[node * 2 + 1]);
		}
	}
	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			++arr[index].first;
			arr[index].second += val;
			tree[node] = arr[index];
			return;
		}
		update(node * 2, start, (start + end) / 2, index, val);
		update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
		tree[node] = add(tree[node * 2], tree[node * 2 + 1]);
	}
	void update(int index, ll val) {
		update(1, 0, sz - 1, index, val);
	}
	ll rquery(int node, int start, int end, int k) {
		if (tree[node].first == k) return tree[node].second;
		if (start == end) return tree[node].second / tree[node].first * k;
		if (tree[node * 2 + 1].first >= k) return rquery(node * 2 + 1, (start + end) / 2 + 1, end, k);
		return tree[node * 2 + 1].second + rquery(node * 2, start, (start + end) / 2, k - tree[node * 2 + 1].first);
	}
	ll lquery(int node, int start, int end, int k) {
		if (tree[node].first == k) return tree[node].second;
		if (start == end) return tree[node].second / tree[node].first * k;
		if (tree[node * 2].first >= k) return lquery(node * 2, start, (start + end) / 2, k);
		return tree[node * 2].second + lquery(node * 2 + 1, (start + end) / 2 + 1, end, k - tree[node * 2].first);
	}
};

void solve() {
	ll N, M; cin >> N >> M;
	vector<ll> V(N); for (int i = 0; i < N; ++i) cin >> V[i];
	set<ll> s;
	for (int i = 0; i < N; ++i) s.insert(V[i]);
	vector<pll> q;
	ll added = 0ll;
	for (int i = 0; i < M; ++i) {
		ll Q, W; cin >> Q >> W;
		q.push_back({Q, W});
		if (Q == 1) s.insert(W - added);
		else if (Q == 2) added += W;
	}
	unordered_map<ll, ll> m;
	vector<ll> val(s.size());
	int idx = -1;
	for (auto i: s) {
		val[++idx] = i;
		m[i] = idx;
	}
	int MAX_N = s.size();
	vector<pll> arr(MAX_N, {0, 0});
	for (int i = 0; i < N; ++i) {
		idx = m[V[i]];
		++arr[idx].first;
		arr[idx].second += V[i];
	}
	SegmentTree seg;
	seg.init(arr, MAX_N);
	added = 0ll;
	for (int i = 0; i < M; ++i) {
		ll Q = q[i].first;
		ll W = q[i].second;
		if (Q == 1) {
			ll val = W - added;
			seg.update(m[val], val);
		} else if (Q == 2) {
			added += W;
		} else if (Q == 3) {
			ll ret = seg.rquery(1, 0, MAX_N - 1, W);
			ret += added * W;
			cout << ret << ' ';
		} else {
			ll ret = seg.lquery(1, 0, MAX_N - 1, W);
			ret += added * W;
			cout << ret << ' ';
		}
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}