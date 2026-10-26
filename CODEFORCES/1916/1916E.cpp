#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void update_lazy(vector<LL> &tree, vector<LL> &lazy, int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += lazy[node];
        if (start != end) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void update_range(vector<LL> &tree, vector<LL> &lazy, int node, int start, int end, int left, int right, LL diff) {
    update_lazy(tree, lazy, node, start, end);
    if (left > end || right < start) {
        return;
    }
    if (left <= start && end <= right) {
        tree[node] += diff;
        if (start != end) {
            lazy[node * 2] += diff;
            lazy[node * 2 + 1] += diff;
        }
        return;
    }
    update_range(tree, lazy, node * 2, start, (start + end) / 2, left, right, diff);
    update_range(tree, lazy, node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff);
    tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}

LL query(vector<LL> &tree, vector<LL> &lazy, int node, int start, int end, int left, int right) {
    update_lazy(tree, lazy, node, start, end);
    if (left > end || right < start) {
        return 0;
    }
    if (left <= start && end <= right) {
        return tree[node];
    }
    LL lsum = query(tree, lazy, node * 2, start, (start+end) / 2, left, right);
    LL rsum = query(tree, lazy, node * 2 + 1, (start+end) / 2 + 1, end, left, right);
    return max(lsum, rsum);
}

void dfs(vector<vector<int>>& graph, vector<int>& start, vector<int>& end, int v, int& cnt) {
	start[v] = cnt++;
	for (auto i: graph[v]) dfs(graph, start, end, i, cnt);
	end[v] = cnt - 1;
}

void dfs2(vector<vector<int>> &graph, int v, vector<int>& a, vector<vector<int>>& colD,
vector<LL>& tree, vector<LL>& lazy, vector<int>& start, vector<int>& end, int& n, LL& ans) {
	for (auto i: graph[v]) dfs2(graph, i, a, colD, tree, lazy, start, end, n, ans);
	update_range(tree, lazy, 1, 0, n - 1, start[v], end[v], 1);
	int col = a[v];
	while (true) {
		if (colD[col].empty()) break;
		int u = colD[col].back();
		if (start[u] < start[v] || end[u] > end[v]) break;
		update_range(tree, lazy, 1, 0, n - 1, start[u], end[u], -1);
		colD[col].pop_back();
	}
	colD[col].push_back(v);
	priority_queue<LL> pos;
	pos.push(query(tree, lazy, 1, 0, n - 1, start[v], start[v]));
	for (int i: graph[v]) pos.push(query(tree, lazy, 1, 0, n - 1, start[i], end[i]));
	LL f = 1, s = 1;
	if (!pos.empty()) { f = pos.top(); pos.pop(); }
	if (!pos.empty()) { s = pos.top(); pos.pop(); }
	// cout << v << '\n';
	// while (!pos.empty()) {
	// 	cout << pos.top() << ' ';
	// 	pos.pop();
	// }
	// cout << '\n';
	ans = max(ans, f * s);
}

void solve() {
	int n; cin >> n;
	int h = (int)ceil(log2(n));
    int tree_size = (1 << (h + 1));
    vector<LL> tree(tree_size);
    vector<LL> lazy(tree_size);
	vector<vector<int>> graph(n + 1);
	for (int i = 2; i <= n; ++i) {
		int p; cin >> p;
		graph[p].push_back(i);
	}
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) cin >> a[i];
	vector<int> start(n + 1), end(n + 1); int cnt = 0;
	dfs(graph, start, end, 1, cnt);
	vector<vector<int>> colD(n + 1);
	LL ans = 1;
	dfs2(graph, 1, a, colD, tree, lazy, start, end, n, ans);
	cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}