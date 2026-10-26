#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m;
ll a[1000][1000];
ll f[1000][1000];
ll c[1000][1000];
bool path[1000][1000];
string s;

void solve() {
	cin >> n >> m;
	cin >> s;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> a[i][j];
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) path[i][j] = false;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) f[i][j] = 0;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) c[i][j] = a[i][j];
	vector<pair<int, int>> adj[m + n];
	int y = 0, x = 0;
	path[y][x] = true;
	adj[y].push_back({y, x});
	adj[x + n].push_back({y, x});
	for (auto i: s) {
		if (i == 'D') ++y;
		else ++x;
		path[y][x] = true;
		adj[y].push_back({y, x});
		adj[x + n].push_back({y, x});
	}
	vector<int> deg(m + n);
	ll sum = 0;
	for (int i = 0; i < m + n; ++i) deg[i] = adj[i].size();
	queue<int> q;
	for (int i = 0; i < m + n; ++i) if (deg[i] == 1) q.push(i);
	while (!q.empty()) {
		int cur = q.front(); q.pop();
		if (cur < n) {
			ll psum = 0;
			ll fsum = 0;
			for (int i = 0; i < m; ++i) fsum += f[cur][i];
			for (int i = 0; i < m; ++i) psum += c[cur][i];
			psum = sum - psum;
			fsum = 1 - fsum;
			for (int i = 0; i < m; ++i) if (path[cur][i]) {
				f[cur][i] = fsum;
				c[cur][i] = psum;
				path[cur][i] = false;
				--deg[cur];
				--deg[i + n];
				if (deg[i + n] == 1) {
					q.push(i + n);
				}
			}
		} else {
			cur -= n;
			ll fsum = 0;
			ll psum = 0;
			for (int i = 0; i < n; ++i) fsum += f[i][cur];
			for (int i = 0; i < n; ++i) psum += c[i][cur];
			psum = sum - psum;
			fsum = 1 - fsum;
			for (int i = 0; i < n; ++i) if (path[i][cur]) {
				f[i][cur] = fsum;
				c[i][cur] = psum;
				path[i][cur] = false;
				--deg[cur + n];
				--deg[i];
				if (deg[i] == 1) {
					q.push(i);
				}
			}
		}
	}
	ll xval = 0;
	for (int i = 0; i < n; ++i) {
		ll fsum = 0;
		ll psum = 0;
		for (int j = 0; j < m; ++j) {
			fsum += f[i][j];
			psum += c[i][j];
		}
		if (fsum == 0) {
			xval = psum;
		}
	}
	for (int i = 0; i < m; ++i) {
		ll fsum = 0;
		ll psum = 0;
		for (int j = 0; j < n; ++j) {
			fsum += f[j][i];
			psum += c[j][i];
		}
		if (fsum == 0) {
			xval = psum;
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			c[i][j] += f[i][j] * xval;
			cout << c[i][j] << ' ';
		}
		cout << '\n';
	}
	// for (int i = 0; i < n; ++i) {
	// 	ll fsum = 0;
	// 	ll psum = 0;
	// 	for (int j = 0; j < m; ++j) {
	// 		fsum += f[i][j];
	// 		psum += c[i][j];
	// 	}
	// 	assert(psum == xval);
	// }
	// for (int i = 0; i < m; ++i) {
	// 	ll fsum = 0;
	// 	ll psum = 0;
	// 	for (int j = 0; j < n; ++j) {
	// 		fsum += f[j][i];
	// 		psum += c[j][i];
	// 	}
	// 	assert(psum == xval);
	// }
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}