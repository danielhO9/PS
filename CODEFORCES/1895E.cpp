#include <bits/stdc++.h>
using namespace std;

void dfs(int v, vector<int>& graph, vector<int>& t, int& n) {
	if (t[v] != -1) return;
	if (graph[v] == -1) {
		if (v >= n) t[v] = 2;
		else t[v] = 0;
		return;
	}
	t[v] = 1;
	dfs(graph[v], graph, t, n);
	t[v] = t[graph[v]];
}

void solve() {
	int n; cin >> n;
	vector<pair<int, int>> a, b;
	int ax[n], ay[n];
	for (int i = 0; i < n; ++i) cin >> ax[i];
	for (int i = 0; i < n; ++i) cin >> ay[i];
	int m; cin >> m;
	int bx[m], by[m];
	for (int i = 0; i < m; ++i) cin >> bx[i];
	for (int i = 0; i < m; ++i) cin >> by[i];
	for (int i = 0; i < n; ++i) a.push_back(make_pair(ax[i], ay[i]));
	for (int i = 0; i < m; ++i) b.push_back(make_pair(bx[i], by[i]));
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	vector<int> ma(n), mb(m);
	for (int i = n - 1; i >= 0; --i) {
		if (i == n - 1) ma[i] = i;
		else {
			if (a[i].second < a[ma[i + 1]].second) ma[i] = ma[i + 1];
			else ma[i] = i;
		}
	}
	for (int i = m - 1; i >= 0; --i) {
		if (i == m - 1) mb[i] = i;
		else {
			if (b[i].second < b[mb[i + 1]].second) mb[i] = mb[i + 1];
			else mb[i] = i;
		}
	}
	vector<int> graph(n + m, -1);
	for (int i = 0; i < n; ++i) {
		auto cnt = lower_bound(b.begin(), b.end(), make_pair(a[i].second + 1, -1));
		if (cnt != b.end()) graph[i] = mb[cnt - b.begin()] + n;
	}
	for (int i = 0; i < m; ++i) {
		auto cnt = lower_bound(a.begin(), a.end(), make_pair(b[i].second + 1, -1));
		if (cnt != a.end()) graph[i + n] = ma[cnt - a.begin()];
	}
	vector<int> t(n + m, -1);
	int ans[3] = {0, 0, 0};
	for (int i = 0; i < n; ++i) {
		if (t[i] == -1) dfs(i, graph, t, n);
		++ans[t[i]];
	}
	for (int i = 0; i < 3; ++i) cout << ans[i] << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}