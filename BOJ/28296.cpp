#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int parents[100001];
int com[100001];
unordered_map<int, ll> vertex[100001];
ll ans[50001];

int find(int x) {
	if (parents[x] == x) return x;
	parents[x] = find(parents[x]);
	return parents[x];
}

void Union(int x, int y) {
	x = find(x); y = find(y);
	if (vertex[x].size() < vertex[y].size()) swap(x, y);
	for (auto i: vertex[y]) vertex[x][i.first] += i.second;
	parents[y] = x;
}

void solve() {
	int N, K, M; cin >> N >> K >> M;
	for (int i = 1; i <= N; ++i) {
		cin >> com[i];
		vertex[i][com[i]] = 1;
	}
	for (int i = 0; i <= N; ++i) parents[i] = i;
	priority_queue<pair<int, pair<int, int>>> pq;
	for (int i = 0; i < M; ++i) {
		int x, y, w; cin >> x >> y >> w;
		pq.push({w, {x, y}});
	}
	while (!pq.empty()) {
		ll c = pq.top().first; int x = pq.top().second.first, y = pq.top().second.second; pq.pop();
		if (find(x) == find(y)) continue;
		x = find(x), y = find(y);
		if (vertex[x].size() < vertex[y].size()) swap(x, y);
		for (auto i: vertex[y]) {
			if (vertex[x].find(i.first) != vertex[x].end()) {
				ans[i.first] += vertex[x][i.first] * i.second * c;
			}
		}
		Union(x, y);
	}
	for (int i = 1; i <= K; ++i) cout << ans[i] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}