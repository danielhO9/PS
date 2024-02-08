#include <bits/stdc++.h>
using namespace std;

int N, M, energy[100001];
vector<pair<int, int>> graph[100001];
int dep[100001], parents[100001][17], dis[100001];

void dfs(int v, int p, int d) {
    parents[v][0] = p;
    if (p == -1) {
        dep[v] = 1; dis[v] = 0;
    } else {
        dep[v] = dep[p] + 1; dis[v] = dis[p] + d;
    }
    for (auto [i, nd]: graph[v]) if (i != p) dfs(i, v, nd);
}

void getParents(int num) {
    for (int i = 1; i <= N; ++i) {
        if (parents[i][num - 1] == -1) parents[i][num] = -1;
        else parents[i][num] = parents[parents[i][num - 1]][num - 1];
    }
}

int solution(int v) {
	int e = energy[v];
    for (int i = 16; i >= 0; --i) {
		if (v == 1) break;
		if (parents[v][i] == -1) parents[v][i] = 1;
        if (dis[v] - dis[parents[v][i]] <= e) {
			e -= dis[v] - dis[parents[v][i]];
			v = parents[v][i];
		}
    }
    return v;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 1; i <= N; ++i) cin >> energy[i];
	int a, b, d;
	for (int i = 0; i < N - 1; ++i) {
		cin >> a >> b >> d;
		graph[a].push_back({b, d});
		graph[b].push_back({a, d});
	}
	dfs(1, -1, 0); for (int i = 1; i < 17; ++i) getParents(i);
	// for (int i = 1; i <= N; ++i) {
	// 	for (int j = 0; j < 17; ++j) cout << parents[i][j] << " ";
	// 	cout << '\n';
	// }
	for (int i = 1; i <= N; ++i) cout << solution(i) << '\n';
}