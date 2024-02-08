#include <bits/stdc++.h>
using namespace std;

struct Edge {
	int v, u, d;
};

vector<pair<int, int>> graph[201];
int dis[201][201];
int maxEdge[201];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int N, M; cin >> N >> M;
	int S, E, L;
	vector<Edge> V;
	for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) dis[i][j] = 987654321;
	for (int i = 0; i < M; ++i) {
		cin >> S >> E >> L;
		V.push_back({S, E, L});
		dis[S][E] = min(dis[S][E], L);
		dis[E][S] = min(dis[E][S], L);
	}
	for (int i = 1; i <= N; ++i) dis[i][i] = 0;
	for (int m = 1; m <= N; ++m) for (int s = 1; s <= N; ++s) for (int e = 1; e <= N; ++e) {
			if (dis[s][e] > dis[s][m] + dis[m][e]) dis[s][e] = dis[s][m] + dis[m][e];
	}
	// for (int i = 1; i <= N; ++i) {
	// 	for (int j = 1; j <= N; ++j) {
	// 		cout << i << ' ' << j << ' ' << dis[i][j] << '\n';
	// 	}
	// }
	double ans = 987654321.0;
	for (int start = 1; start <= N; ++start) {
		double temp = 0.0;
		for (auto edge: V) {
			double t1 = dis[start][edge.v], t2 = dis[start][edge.u];
			if (abs(t1 - t2) >= edge.d) temp = max(min(t1, t2) + edge.d, temp);
			else temp = max(temp, ((double) edge.d - abs(t1 - t2)) / 2.0 + max(t1, t2));
		}
		ans = min(ans, temp);
	}
	cout << fixed;
	cout.precision(1);
	cout << ans;
}