#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
ll a[200000];
ll b[200000];
vector<int> adj[200000];

struct SegmentTree {
	vector<ll> tree;
	int sz;

	inline ll agg(ll x, ll y) {
		if (x == -1 || y == -1) return x + y + 1;
		return (b[x] < b[y] ? x : y);
	}

	void init(int sz_) {
		sz = sz_;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
		init(1, 0, sz - 1);
	}
	void init(int node, int start, int end) {
		if (start == end) tree[node] = start;
		else {
			init(node * 2, start, (start + end) / 2);
			init(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = agg(tree[node * 2], tree[node * 2 + 1]);
		}
	}
	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return -1;
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return agg(lsum, rsum);
	}
	ll query(int left, int right) {
		return query(1, 0, sz - 1, left, right);
	}
};

void getGraph(int l, int r, SegmentTree& seg) {
	if (l == r) return;
	int mnidx = seg.query(l, r);
	if (l < mnidx) {
		adj[mnidx].push_back(seg.query(l, mnidx - 1));
		getGraph(l, mnidx - 1, seg);
	}
	if (mnidx < r) {
		adj[mnidx].push_back(seg.query(mnidx + 1, r));
		getGraph(mnidx + 1, r, seg);
	}
}

vector<ll> dfs(int v) {
	vector<ll> ret;
	if (adj[v].size() == 0) {
		ll tmp = a[v];
		while (tmp != 1) {
			ret.push_back(tmp);
			tmp = (tmp + b[v] - 1) / b[v];
		}
		ret.push_back(1);
		return ret;
	}
	for (int u: adj[v]) {
		vector<ll> partial = dfs(u);
		for (auto& i: partial) i *= -1;
		vector<ll> tmp(ret.size() + partial.size());
		merge(ret.begin(), ret.end(), partial.begin(), partial.end(), tmp.begin());
		swap(ret, tmp);
	}
	for (auto& i: ret) i *= -1;
	for (auto& i: ret) i = max(i, a[v]);
	for (int i = 0; i < 70; ++i) ret.push_back(a[v]);
	for (int i = 1; i < ret.size(); ++i) {
		ret[i] = min(ret[i], (ret[i - 1] + b[v] - 1) / b[v]);
	}
	assert(ret.back() == 1);
	while (ret.size() >= 2 && ret[(int)ret.size() - 2] == 1) ret.pop_back();
	return ret;
}

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) cin >> b[i];
	for (int i = 0; i < n; ++i) adj[i].clear();
	SegmentTree seg;
	seg.init(n);
	getGraph(0, n - 1, seg);
	vector<int> deg(n, 0);
	for (int i = 0; i < n; ++i) {
		for (auto j: adj[i]) ++deg[j];
	}
	int rt;
	for (int i = 0; i < n; ++i) if (deg[i] == 0) {
		rt = i;
		break;
	}
	vector<ll> ans = dfs(rt);
	for (int i = 0; i < 70; ++i) {
		if (ans[i] == 1) {
			cout << i << '\n';
			return;
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}