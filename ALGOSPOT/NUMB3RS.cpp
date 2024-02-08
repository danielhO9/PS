#include <bits/stdc++.h>
using namespace std;

int n, d, p, graph[50][50], t, q, deg[50];
double cache[50][101];

double matchCache(int pl, int s) {
	if (s == 0 && pl == p) return 1.0;
	if (s == 0) return 0.0;
	double& ret = cache[pl][s];
	if (ret > -0.5) return ret;
	ret = 0.0;
	for (int i = 0; i < n; ++i) if (graph[pl][i] == 1) ret += matchCache(i, s - 1) / deg[i];
	return ret;
}

void solution() {
	cin >> n >> d >> p;
	for (int i = 0; i < 50; ++i) for (int j = 0; j < 101; ++j) cache[i][j] = -1.0;
	memset(deg, 0, sizeof(deg));
	memset(graph, 0, sizeof(graph));
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
		cin >> graph[i][j];
		if (graph[i][j]) ++deg[i];
	}
	cin >> t;
	for (int i = 0; i < t; ++i) {
		cin >> q;
		cout.precision(9);
		cout << matchCache(q, d) << " ";
	}
	cout << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int c; cin >> c;
	for (int i = 0; i < c; ++i) solution();
}