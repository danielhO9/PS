#include <bits/stdc++.h>
using namespace std;

int N, M;
map<pair<int, int>, int> start_time;
map<pair<int, int>, int> end_time;
pair<int, int> query[100000];
int q = 0;
int rk[100001];
int p[100001];
int ans[100000];
int cnt;

int find(int v) {
	if (v == p[v]) return v;
	return find(p[v]);
}

void union_rank(int u, int v, stack<vector<int>>& st) {
	u = find(u), v = find(v);
	if (u == v) return;
	if (rk[u] < rk[v]) swap(u, v);
	p[v] = u;
	if (rk[v] == rk[u]) {
		++rk[u];
		st.push({v, u, 1});
	} else st.push({v, u, 0});
	--cnt;
}

struct edge {
	int u, v, s, e;
};

vector<vector<edge>> tree;

void update(int node, int start, int end, edge e) {
    if (e.s > end || e.e < start) return;
    if (e.s <= start && end <= e.e) {
        tree[node].push_back(e);
        return;
    }
	int mid = (start + end) / 2;
    update(node * 2, start, mid, e);
    update(node * 2 + 1, mid + 1, end, e);
}

void dnq(int node, int start, int end) {
	stack<vector<int>> st;
	for (auto i: tree[node]) union_rank(i.u, i.v, st);
	if (start == end) {
		ans[start] = cnt;
		while (!st.empty()) {
			auto j = st.top(); st.pop();
			if (j[2]) --rk[j[1]];
			p[j[0]] = j[0];
			++cnt;
		}
		return;
	}
	else {
		int mid = (start + end) / 2;
		dnq(node * 2, start, mid);
		dnq(node * 2 + 1, mid + 1, end);
	}
	while (!st.empty()) {
		auto j = st.top(); st.pop();
		if (j[2]) --rk[j[1]];
		p[j[0]] = j[0];
		++cnt;
	}
	return;
}

void solve() {
	cin >> N >> M;
	cnt = N;
	for (int i = 1; i <= N; ++i) p[i] = i;
	for (int i = 0; i < M; ++i) {
		char t; cin >> t;
		if (t == '?') {
			++q;
			continue;
		}
		int a, b; cin >> a >> b;
		if (a > b) swap(a, b);
		if (t == '+') {
			start_time[{a, b}] = q;
			end_time[{a, b}] = -1;
		}
		else if (t == '-') end_time[{a, b}] = q - 1;
	}
	if (q == 0) return;
	int h = (int)ceil(log2(q));
	int tree_size = (1 << (h + 1));
	tree = vector<vector<edge>> (tree_size);
	for (auto [i, j]: start_time) {
		int k = end_time[i];
		if (k == -1) k = q - 1;
		if (k >= j) update(1, 0, q - 1, {i.first, i.second, j, k});
		// cout << i.first << ' ' << i.second << ' ' << j << ' ' << k << '\n';
	}
	dnq(1, 0, q - 1);
	for (int i = 0; i < q; ++i) cout << ans[i] <<  '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}