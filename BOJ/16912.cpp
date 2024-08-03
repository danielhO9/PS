#include <bits/stdc++.h>
using namespace std;

int N, M;
unordered_map<int, int> start_time;
unordered_map<int, int> end_time;
map<pair<int, int>, int> m;
pair<int, int> query[100000];
pair<int, int> vertex[100000];
int q = 0;
int rk[100001];
int p[100001];
int ans[100000];


int find(int v) {
	if (v == p[v]) return v;
	return find(p[v]);
}

void union_rank(int u, int v, stack<vector<int>>& st) {
	u = find(u), v = find(v);
	if (u == v) return;
	if (rk[u] > rk[v]) swap(u, v);
	p[u] = v;
	if (rk[u] == rk[v]) {
		++rk[v];
		st.push({u, v, 1});
	} else st.push({u, v, 0});
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
		ans[start] = (find(query[start].first) == find(query[start].second));
	} else {
		int mid = (start + end) / 2;
		dnq(node * 2, start, mid);
		dnq(node * 2 + 1, mid + 1, end);
	}
	while (!st.empty()) {
		auto j = st.top(); st.pop();
		if (j[2]) --rk[j[1]];
		p[j[0]] = j[0];
	}
}

void solve() {
	cin >> N >> M;
	int idx = 0;
	for (int i = 1; i <= N; ++i) p[i] = i;
	for (int i = 0; i < M; ++i) {
		int t, a, b; cin >> t >> a >> b;
		if (a > b) swap(a, b);
		if (t == 1) {
			m[{a, b}] = idx;
			vertex[idx] = {a, b};
			start_time[idx] = q;
			end_time[idx] = -2;
			++idx;
		}
		else if (t == 2) {
			end_time[m[{a, b}]] = q - 1;
		}
		else query[q++] = {a, b};
	}
	if (q == 0) return;
	int h = (int)ceil(log2(q));
	int tree_size = (1 << (h + 1));
	tree = vector<vector<edge>> (tree_size);
	for (int i = 0; i < idx; ++i) {
		// cout << vertex[i].first << ' ' << vertex[i].second << ' ' << start_time[i] << ' ' << end_time[i] << '\n';
		if (end_time[i] == -2) end_time[i] = q - 1;
		if (start_time[i] <= end_time[i]) {
			update(1, 0, q - 1, {vertex[i].first, vertex[i].second, start_time[i], end_time[i]});
			// cout << vertex[i].first << ' ' << vertex[i].second << ' ' << start_time[i] << ' ' << end_time[i] << '\n';
		}
	}
	dnq(1, 0, q - 1);
	for (int i = 0; i < q; ++i) cout << ans[i] <<  '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}