#include <bits/stdc++.h>
using namespace std;

int N, M;
int X[100000], Y[100000], Z[100000];
vector<pair<int, int>> adj[200001];
int ans[200001];
bool vis[200001];

void solve() {
	cin >> N >> M;
	for (int i = 0; i < M; ++i) cin >> X[i] >> Y[i] >> Z[i];
	for (int i = 0; i < M; ++i) {
		adj[X[i]].push_back({Y[i], Z[i]});
		adj[Y[i]].push_back({X[i], Z[i]});
	}
	memset(ans, -1, sizeof(ans));
	for (int i = 1; i <= N; ++i) if (ans[i] == -1) {
		ans[i] = 0;
		vector<int> v;
		queue<int> q; q.push(i); vis[i] = true; v.push_back(i);
		while (!q.empty()) {
			int here = q.front(); q.pop();
			for (auto [there, w]: adj[here]) {
				if (vis[there]) {
					if (ans[there] != (ans[here] ^ w)) {
						cout << -1;
						return;
					}
					continue;
				}
				vis[there] = true;
				ans[there] = ans[here] ^ w;
				v.push_back(there);
				q.push(there);
			}
		}
		int val = 0;
		int sz = v.size();
		for (int j = 29; j >= 0; --j) {
			int cnt = 0;
			for (auto k: v) if ((ans[k] >> j) & 1) ++cnt;
			if (cnt > sz / 2) val ^= (1 << j);
		}
		for (auto j: v) ans[j] ^= val;
	}
	for (int i = 1; i <= N; ++i) cout << ans[i] << ' ';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}