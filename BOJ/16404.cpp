#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void update_lazy(vector<LL> &tree, vector<LL> &lazy, int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += (end - start + 1) * lazy[node];
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
        tree[node] += (end - start + 1) * diff;
        if (start != end) {
            lazy[node * 2] += diff;
            lazy[node * 2 + 1] += diff;
        }
        return;
    }
    update_range(tree, lazy, node * 2, start, (start + end) / 2, left, right, diff);
    update_range(tree, lazy, node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
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
    return lsum + rsum;
}

void EulerRoot(vector<int>& start, vector<int>& end, vector<vector<int>>& graph, int v, int& cnt) {
	start[v] = ++cnt;
	for (auto i: graph[v]) EulerRoot(start, end, graph, i, cnt);
	end[v] = cnt;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int N, M; cin >> N >> M;
	vector<vector<int>> graph(N + 1);
	for (int i = 1; i <= N; ++i) {
		int p; cin >> p;
		if (p != -1) graph[p].push_back(i);
	}
	vector<int> start(N + 1), end(N + 1);
	int cnt = -1; EulerRoot(start, end, graph, 1, cnt);
	int h = (int)ceil(log2(N));
    int tree_size = (1 << (h + 1));
    vector<LL> tree(tree_size);
    vector<LL> lazy(tree_size);
	while (M--) {
        int what;
        cin >> what;
        if (what == 1) {
            int i; LL diff;
            cin >> i >> diff;
            update_range(tree, lazy, 1, 0, N - 1, start[i], end[i], diff);
        } else if (what == 2) {
			int i; cin >> i;
            cout << query(tree, lazy, 1, 0, N - 1, start[i], start[i]) << '\n';
        }
    }
}