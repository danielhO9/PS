#include <bits/stdc++.h>
using namespace std;
int n, m;

double table[5000][5000];

void init() {
	table[2][0] = 0.0;
	table[2][1] = 0.5;
	for (int i = 4; i < 5000; i += 2) {
		double ii = i;
		double p = 1, q = i - 3;
		table[i][i - 1] = 1 / ii;
		for (int j = 1; j < i - 1; ++j) {
			table[i][j] = (table[i - 2][j] * q + table[i - 2][j - 1] * p) / ii;
			++p; --q;
		}
	}
}

double calc(vector<double>& p) {
	double a = p.size();
	if (p.size() % 2 == 1) {
		double ret = 0.0;
		for (auto i: p) ret += i;
		return ret / a;
	}
	double ret = 0.0;
	for (int i = 0; i < p.size(); ++i) {
		ret += p[i] * table[p.size()][i];
	}
	return ret;
}

double matchCache(vector<double>& cache, vector<vector<int>>& graph, int v) {
	if (v == n) return 1.0;
	double& ret = cache[v];
	if (ret > -0.5) return ret;
	vector<double> p;
	for (auto i: graph[v]) p.push_back(matchCache(cache, graph, i));
	sort(p.begin(), p.end());
	ret = calc(p);
	return ret;
}

void solve() {
	cin >> n >> m;
	vector<vector<int>> graph(n + 1);
	while(m--) {
		int a, b; cin >> a >> b;
		graph[a].push_back(b);
	}
	vector<double> cache(n + 1, -1.0);
	cout << fixed;
	cout.precision(12);
	cout << matchCache(cache, graph, 1) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	int t; cin >> t;
	while (t--) solve();
}

