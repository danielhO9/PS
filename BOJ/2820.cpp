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

void dfs(vector<int>& start, vector<int>& end, int v, vector<vector<int>>& graph, int& cnt) {
	start[v] = ++cnt;
	for (auto i: graph[v]) dfs(start, end, i, graph, cnt);
	end[v] = cnt;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int N, M; cin >> N >> M;
	vector<LL> tree(N + 1);
	vector<LL> a(N + 1);
	vector<vector<int>> graph(N + 1);
	cin >> a[1];
	for (int i = 2; i <= N; ++i) {
		cin >> a[i]; int p; cin >> p;
		graph[p].push_back(i);
	}
	vector<int> start(N + 1), end(N + 1);
	int cnt = 0; dfs(start, end, 1, graph, cnt);
	for (int i = 1; i <= N; ++i) {
		update(tree, start[i], a[i]);
		if (start[i] != N) update(tree, start[i] + 1, -a[i]);
	}
	while (M--) {
		char t; cin >> t;
		if (t == 'p') {
			int a; LL x; cin >> a >> x;
			if (start[a] != N) update(tree, start[a] + 1, x);
			if (end[a] != N) update(tree, end[a] + 1, -x);
		} else {
			int a; cin >> a;
			cout << sum(tree, start[a]) << '\n';
		}
	}
}