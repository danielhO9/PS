#include <bits/stdc++.h>
using namespace std;

int find(vector<int>& parents, int x) {
	if (parents[x] == x) return x;
	parents[x] = find(parents, parents[x]);
	return parents[x];
}

void Union(vector<int>& parents, int x, int y) {
	x = find(parents, x); y = find(parents, y);
	int minn = min(x, y);
	parents[x] = minn; parents[y] = minn;
}

void solve() {
	int N, M; cin >> N >> M;
	vector<int> parents(N + 1);
	for (int i = 0; i <= N; ++i) parents[i] = i;
	vector<pair<double, double>> cor(N + 1);
	for (int i = 1; i <= N; ++i) cin >> cor[i].first >> cor[i].second;
	priority_queue<pair<double, pair<int, int>>, vector<pair<double, pair<int, int>>>, greater<>> Q;
	for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) if (i != j) {
		Q.push({sqrt((cor[i].first - cor[j].first) * (cor[i].first - cor[j].first) + (cor[i].second - cor[j].second) * (cor[i].second - cor[j].second)), {i, j}});
	}
	double ans = 0.0;
	for (int i = 0; i < M; ++i) {
		int X, Y; cin >> X >> Y;
		Union(parents, X, Y);
	}
	while (!Q.empty()) {
		double dis = Q.top().first; int X = Q.top().second.first, Y = Q.top().second.second; Q.pop();
		if (find(parents, X) != find(parents, Y)) {
			Union(parents, X, Y);
			ans += dis;
		}
	}
	cout << fixed;
	cout.precision(2);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}