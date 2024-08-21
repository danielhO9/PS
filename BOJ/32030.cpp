#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// S[i...], S의 lcp
vector<int> getZ(const string& s) {
	const int n = s.size();
	int l = 0, r = 0;
	vector<int> z(n, 0);
	z[0] = n;
	for (int i = 1; i < n; ++i) {
		if (i <= r) z[i] = min(r - i, z[i - l]);
		while (s[i + z[i]] == s[z[i]]) ++z[i];
		if (i > r) l = i;
		r = max(r, i + z[i] - 1);
	}
	return z;
}

int N;
string S, C, T;
bool twice[26][26];
vector<pair<int, ll>> adj[500000];

vector<ll> dijkstra(int src) {
	const int MAX_V = T.size();
	vector<ll> dist(MAX_V, LLONG_MAX);
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

void solve() {
	cin >> N;
	cin >> S >> C >> T;
	memset(twice, 0, sizeof(twice));
	for (int i = 0; i < N; ++i) {
		twice[S[i] - 'a'][C[i] - 'a'] = true;
	}
	auto z = getZ(T);
	for (int i = 0; i + 1 < T.size(); ++i) {
		for (int j = 0; j < 26; ++j) {
			if (twice[T[i] - 'a'][j]) {
				int r = 2 * i + 1;
				int tmp = min(z[i + 1] + i, r);
				if (tmp == r && r + 1 < T.size() && T[r + 1] == j + 'a') {
					// cout << i << ' ' << r + 1 << ' ' << 1 << "\n";
					adj[i].push_back({r + 1, 1});
				} else {
					int dif = r - tmp + 2;
					// cout << i << ' ' << z[i + 1] + i << ' ' << dif << "\n";
					adj[i].push_back({tmp, dif});
				}
			} else {
				if (T[i + 1] == j + 'a') {
					// cout << i << ' ' << i + 1 << ' ' << 1 << "\n";
					adj[i].push_back({i + 1, 1});
				}
			}
		}
	}
	for (int i = 1; i < T.size(); ++i) adj[i].push_back({i - 1, 1});
	auto ans = dijkstra(0);
	if (ans[(int)T.size() - 1] == LLONG_MAX) cout << -1;
	else cout << ans[(int)T.size() - 1] + 1;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}