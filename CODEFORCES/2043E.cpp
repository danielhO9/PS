#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, m;
int A[1000][1000];
int B[1000][1000];
set<int> adj[62000];
bool vis[62000];

void solve() {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> A[i][j];
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> B[i][j];
	for (int i = 0; i < 62000; ++i) adj[i].clear();
	memset(vis, 0, sizeof(vis));


	vector<int> pts;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) for (int k = 0; k < 31; ++k) {
		if ((B[i][j] >> k) & 1) adj[i * 31 + k].insert((j + n) * 31 + k);
		else adj[(j + n) * 31 + k].insert(i * 31 + k);
		if ( ((A[i][j] >> k) & 1) && !((B[i][j] >> k) & 1) ) pts.push_back(i * 31 + k);
		if ( !((A[i][j] >> k) & 1) && ((B[i][j] >> k) & 1) ) pts.push_back((j + n) * 31 + k);
	}

	vector<int> deg(62000, 0);
	
	queue<int> q;
	for (int i: pts) {
		if (vis[i]) continue;

		vis[i] = true;
		q.push(i);

		while (!q.empty()) {
			int cur = q.front(); q.pop();
			for (int j: adj[cur]) {
				if (!vis[j]) {
					vis[j] = true;
					q.push(j);
				}
				++deg[j];
			}
		}
	}

	int cnt = 0;
	for (int i = 0; i < 62000; ++i) if (vis[i]) ++cnt;


	queue<int> zr;
	for (int i = 0; i < 62000; ++i) if (vis[i] && deg[i] == 0) {
		zr.push(i);
	}

	while (!zr.empty()) {
		int cur = zr.front(); zr.pop();
		--cnt;
		for (auto v: adj[cur]) if (vis[v]) {
			--deg[v];
			if (deg[v] == 0) zr.push(v);
		}
	}

	if (cnt == 0) cout << "Yes\n";
	else cout << "No\n";


}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}