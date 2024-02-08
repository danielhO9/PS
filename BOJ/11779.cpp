#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int n, m, start, stop, choice[1001];
vector<pair<LL, int>> graph[1001];
LL dis[1001];
priority_queue<pair<LL, int>, vector<pair<LL, int>>, greater<>> Q;
vector<int> way;

void reconstruct() {
	int x = stop;
	while (x != 0) {
		way.push_back(x);
		x = choice[x];
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m; int a, b; LL d;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b >> d;
		graph[a].push_back({d, b});
	}
	cin >> start >> stop;
	for (int i = 0; i < 1001; ++i) dis[i] = LLONG_MAX;
	dis[start] = 0; Q.push({0, start});
	LL cost; int place;
	while (!Q.empty()) {
		cost = Q.top().first; place = Q.top().second;
		Q.pop();
		if (dis[place] < cost) continue;
		for (auto i: graph[place]) {
			if (cost + i.first < dis[i.second]) {
				choice[i.second] = place;
				dis[i.second] = cost + i.first;
				Q.push({cost + i.first, i.second});
			}
		}
	}
	cout << dis[stop] << "\n";
	reconstruct();
	cout << way.size() << "\n";
	while (!way.empty()) {
		cout << way.back() << " ";
		way.pop_back();
	}
}