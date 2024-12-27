#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
	ll lMax, rMax, max, sum;
};

Node merge(Node l, Node r) {
	Node ret;
	ret.lMax = max(l.lMax, l.sum + r.lMax);
	ret.rMax = max(r.rMax, r.sum + l.rMax);
	ret.max = max({l.max, r.max, l.rMax + r.lMax});
	ret.sum = l.sum + r.sum;
	return ret;
}

void init(vector<ll>& a, vector<Node>& tree, int node, int start, int end) {
	if (start == end) {
		tree[node] = {a[start], a[start], a[start], a[start]};
	}
	else {
		init(a, tree, node * 2, start, (start + end) / 2);
		init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}
}

void update(vector<ll>& a, vector<Node>& tree, int node, int start, int end, int index, ll val) {
	if (index < start || index > end) return;
	if (start == end) {
		a[index] += val;
		tree[node] = {a[index], a[index], a[index], a[index]};
		return;
	}
	update(a, tree, node * 2, start, (start + end) / 2, index, val);
	update(a, tree, node * 2 + 1, (start + end) / 2 + 1, end, index, val);
	tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
}

Node query(vector<Node>& tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return {(ll)-1e14, (ll)-1e14, (ll)-1e14, (ll)-1e14};
	if (left <= start && end <= right) return tree[node];
	Node l = query(tree, node * 2, start, (start + end) / 2, left, right);
	Node r = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return merge(l, r);
}

void solve() {
	int N; cin >> N;
	vector<int> xCor;
	vector<pair<pair<int, int>, ll>> V;
	for (int i = 0; i < N; ++i) {
		int x, y; cin >> x >> y;
		xCor.push_back(x);
		V.push_back({{y, x}, 0});
	}
	int M; cin >> M;
	for (int i = 0; i < M; ++i) {
		int x, y; cin >> x >> y;
		xCor.push_back(x);
		V.push_back({{y, x}, 0});
	}
	ll c1, c2; cin >> c1 >> c2;
	for (int i = 0; i < N; ++i) V[i].second = c1;
	for (int i = N; i < N + M; ++i) V[i].second = -c2;
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
	int h = (int)ceil(log2(MAX_N));
	int tree_size = (1 << (h + 1));
	vector<Node> tree(tree_size);
	for (int y1 = 0; y1 < todo.size(); ++y1) {
		for (int i = 0; i < MAX_N; ++i) arr[i] = 0;
		init(arr, tree, 1, 0, MAX_N - 1);
		for (int y2 = y1; y2 < todo.size(); ++y2) {
			for (auto i: todo[y2]) update(arr, tree, 1, 0, MAX_N - 1, i.first, i.second);
			ans = max(ans, query(tree, 1, 0, MAX_N - 1, 0, MAX_N - 1).max);
			// cout << query(tree, 1, 0, MAX_N - 1, 0, MAX_N - 1).max << '\n';
		}
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}