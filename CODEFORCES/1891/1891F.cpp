#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL sum(vector<LL> &tree, int i) {
    LL ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= (i & -i);
    }
    return ans;
}
void update(vector<LL> &tree, int i, LL diff) {
    while (i < tree.size()) {
        tree[i] += diff;
        i += (i & -i);
    }
}

void eulerTour(vector<int>& start, vector<int>& end, vector<vector<int>>& graph, int v, int& cnt) {
	start[v] = ++cnt;
	for (auto i: graph[v]) eulerTour(start, end, graph, i, cnt);
	end[v] = cnt;
}

void solve() {
	int q; cin >> q;
	vector<pair<int, pair<int, LL>>> query;
	int n = 1;
	for (int i = 0; i < q; ++i) {
		int what; cin >> what;
		if (what == 1) {
			int v; cin >> v;
			query.push_back({1, {v, 0}});
			++n;
		} else {
			int v; LL x; cin >> v >> x;
			query.push_back({2, {v, x}});
		}
	}
	vector<vector<int>> graph(n + 1);
	int sz = 1; 
	for (auto [i, j]: query) if (i == 1) graph[j.first].push_back(++sz);
	vector<int> start(n + 1), end(n + 1); int cnt = 0;
	eulerTour(start, end, graph, 1, cnt);
    vector<LL> tree(n + 1, 0);
	sz = 1;
	for (auto [i, j]: query) {
		if (i == 1) {
			int v = start[++sz];
			LL x = sum(tree, v);
			update(tree, v, -x);
			if (v != n) update(tree, v + 1, x);
		} else {
			int v = j.first; LL x = j.second;
			update(tree, start[v], x);
			if (end[v] != n) update(tree, end[v] + 1, -x);
		}
	}
	for (int i = 1; i <= n; ++i) {
		int v = start[i];
		cout << sum(tree, v) << ' ';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}

/*
1
9
2 1 3
1 1
2 2 1
1 1
2 3 2
1 3
2 1 4
1 3
2 3 2
*/