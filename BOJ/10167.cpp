#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
	ll lmx, rmx, mx, sm;

	Node() = default;
	Node(ll x): lmx(x), rmx(x), mx(x), sm(x) {}
};

struct SegmentTree {
	vector<ll> arr;
	vector<Node> tree;
	int sz;

	inline Node merge(const Node& l, const Node& r) {
		Node ret{};
		ret.lmx = max(l.lmx, l.sm + r.lmx);
		ret.rmx = max(r.rmx, r.sm + l.rmx);
		ret.mx = max({l.mx, r.mx, l.rmx + r.lmx});
		ret.sm = l.sm + r.sm;
		return ret;
	}
	SegmentTree(const vector<ll>& a) {
		sz = a.size();
		arr = a;
		int h = (int) ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<Node>(tree_size);
		init(1, 0, sz - 1);
	}
	void init(int node, int start, int end) {
		if (start == end) tree[node] = Node {arr[start]};
		else {
			int mid = (start + end) / 2;
			init(node * 2, start, mid);
			init(node * 2 + 1, mid + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}
	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			arr[index] += val;
			tree[node] = Node {arr[index]};
			return;
		}
		int mid = (start + end) / 2;
		update(node * 2, start, mid, index, val);
		update(node * 2 + 1, mid + 1, end, index, val);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}
	Node query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return Node {INT32_MIN};
		if (left <= start && end <= right) return tree[node];
		int mid = (start + end) / 2;
		Node l = query(node * 2, start, mid, left, right);
		Node r = query(node * 2 + 1, mid + 1, end, left, right);
		return merge(l, r);
	}
	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }
	Node query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

void solve() {
	int N; cin >> N;
	vector<int> xCor;
	vector<pair<pair<int, int>, ll>> V;
	for (int i = 0; i < N; ++i) {
		int x, y; ll w; cin >> x >> y >> w;
		xCor.push_back(x);
		V.push_back({{y, x}, w});
	}
	sort(xCor.begin(), xCor.end());
	xCor.erase(unique(xCor.begin(), xCor.end()), xCor.end());

	unordered_map<int, int> dict;
	int idx = 0;
	for (auto i: xCor) dict[i] = idx++;
	xCor.clear();
	sort(V.begin(), V.end());
	vector<vector<pair<int, ll>>> todo;
	for (int i = 0; i < V.size(); ++i) {
		if (todo.empty() || V[i].first.first != V[i - 1].first.first) todo.push_back({});
		todo.back().push_back({dict[V[i].first.second], V[i].second});
	}
	V.clear(); V.shrink_to_fit();
	ll ans = 0;
	// 0 ~ MAX_N - 1
	int MAX_N = idx;
	vector<ll> arr(MAX_N);
	for (int y1 = 0; y1 < todo.size(); ++y1) {
		for (int i = 0; i < MAX_N; ++i) arr[i] = 0;
		SegmentTree seg {arr};
		for (int y2 = y1; y2 < todo.size(); ++y2) {
			for (auto i: todo[y2]) seg.update(i.first, i.second);
			ans = max(ans, seg.query(0, MAX_N - 1).mx);
			// cout << query(tree, 1, 0, MAX_N - 1, 0, MAX_N - 1).max << '\n';
		}
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}