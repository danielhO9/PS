#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int N, M;

LL dis[501], cycleCnt[501];
vector<pair<int, LL>> graph[501];
bool inQ[501];
queue<int> Q;

bool SPFA(int v) {
	dis[v] = 0; Q.push(v); inQ[v] = true;
	while (!Q.empty()) {
		int here = Q.front(); Q.pop(); inQ[here] = false;
		for (auto [there, cost]: graph[here]) if (dis[there] > dis[here] + cost) {
			dis[there] = dis[here] + cost;
			if (!inQ[there]) {
				++cycleCnt[there];
				if (cycleCnt[there] >= N) return false;
				Q.push(there);
				inQ[there] = true;
			}
		}
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M; LL A, B, C;
	for (int i = 0; i < M; ++i) {
		cin >> A >> B >> C;
		graph[A].push_back({B, C});
	}
	for (int i = 1; i <= N; ++i) dis[i] = INT32_MAX;
	if (!SPFA(1)) cout << -1;
	else for (int i = 2; i <= N; ++i) {
		if (dis[i] != INT32_MAX) cout << dis[i] << '\n';
		else cout << -1 << '\n';
	}
}