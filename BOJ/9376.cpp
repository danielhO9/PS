#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int h, w;
char prison[100][100];
int dy[4] = {1, -1, 0, 0}, dx[4] = {0, 0, 1, -1};

vector<ll> dijkstra(int src, vector<vector<pair<int, ll>>>& adj) {
	const int MAX_V = adj.size();
	vector<ll> dist(MAX_V, 987654321);
	dist[src] = 0;
	priority_queue<pair<ll, int>> pq;
	pq.push(make_pair(0, src));
	while(!pq.empty()) {
		ll cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		if (dist[here] < cost) continue;
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			ll nextDist = cost + adj[here][i].second;
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}

// MAX_V: max vertex number
// time complexity: (V+E)logV
void solve() {
	cin >> h >> w;
	vector<int> prisoner;
	for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) {
		cin >> prison[i][j];
		if (prison[i][j] == '$') prisoner.push_back(i * w + j);
	}
	int MAX_V = h * w + 1;
	vector<vector<pair<int, ll>>> adj(MAX_V);
	for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) {
		if (prison[i][j] == '*') continue;
		if (i == 0 || j == 0 || i == h - 1 || j == w - 1) {
			adj[h * w].push_back({i * w + j, prison[i][j] == '#' ? 1ll : 0ll});
			adj[i * w + j].push_back({h * w, 0});
		}
		for (int k = 0; k < 4; ++k) {
			int ni = i + dy[k], nj = j + dx[k];
			if (0 <= ni && ni < h && 0 <= nj && nj < w && prison[ni][nj] != '*') {
				adj[i * w + j].push_back({ni * w + nj, prison[ni][nj] == '#' ? 1ll : 0ll});
			}
		}
	}
	vector<ll> ans1 = dijkstra(prisoner[0], adj);
	vector<ll> ans2 = dijkstra(prisoner[1], adj);
	vector<ll> ans3 = dijkstra(h * w, adj);
	ll ans = 987654321;
	for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j) {
		if (prison[i][j] == '*') continue;
		int p = i * w + j;
		if (prison[i][j] == '.' || prison[i][j] == '$') ans = min(ans, ans1[p] + ans2[p] + ans3[p]);
		else ans = min(ans, ans1[p] + ans2[p] + ans3[p] - 2);
	}
	ans = min(ans, ans1[h * w] + ans2[h * w]);
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}