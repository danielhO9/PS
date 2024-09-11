#include <bits/stdc++.h>
using namespace std;

int N, M, s, e;
vector<pair<int, int>> adj[300001];
pair<int, char> dis[300001];
vector<vector<int>> arr;
bool vis[300001];

void solve() {
	cin >> N >> M >> s >> e;
	for (int i = 0; i < M; ++i) {
		int u, v, c; cin >> u >> v >> c;
		adj[u].push_back({v, c});
		adj[v].push_back({u, c});
	}

	dis[s] = {0, '0'};
	vis[s] = true;
	arr.push_back({});
	arr[0].push_back(s);
	queue<int> q; q.push(s);
	while (!q.empty()) {
		int here = q.front(); q.pop();
		for (auto [there, c]: adj[here]) if (!vis[there] && c == 0) {
			q.push(there);
			arr[0].push_back(there);
			dis[there] = {0, '0'};
			vis[there] = true;
		}
	}
	int idx = 0;
	while (true) {
		if (idx == arr.size()) break;
		if (arr[idx].empty()) {
			++idx;
			continue;
		}
		arr.push_back({});
		for (auto i: arr[idx]) {
			for (auto [j, c]: adj[i]) if (!vis[j] && c == 0) {
				// cout << j << ' ';
				arr.back().push_back(j);
				dis[j] = {i, c + '0'};
				vis[j] = true;
			}
		}
		arr.push_back({});
		for (auto i: arr[idx]) {
			for (auto [j, c]: adj[i]) if (!vis[j] && c == 1) {
				// cout << j << ' ';
				arr.back().push_back(j);
				dis[j] = {i, c + '0'};
				vis[j] = true;
			}
		}
		++idx;
	}

	string ans = "";
	while (e != 0) {
		ans += dis[e].second;
		e = dis[e].first;
	}
	while (ans.back() == '0') ans.pop_back();
	if (ans.size() == 0) ans.push_back('0');
	reverse(ans.begin(), ans.end());
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}