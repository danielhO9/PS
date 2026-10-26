#include <bits/stdc++.h>
using namespace std;

int limit, len, ans;

int add(int x, int t, vector<vector<bool>>& vis) {
	if (vis[t][x]) return ans;
	queue<int> Q;
	vis[t][x] = 1; Q.push(x);
	while (!Q.empty()) {
		int now = Q.front(); Q.pop();
		if (vis[0][now] && vis[1][now]) ans = max(ans, now);
		for (int i = 0; i < len; ++i) if ((now >> i) & 1) {
			if (!vis[t][now ^ (1 << i)]) {
				vis[t][now ^ (1 << i)] = 1;
				Q.push(now ^ (1 << i));
			}
		}
	}
	return ans;
}

void solve() {
	int n, q; cin >> n >> q;
	limit = 1, len = 0, ans = 0;
	while (limit < n) {
		limit *= 2; ++len;
	}
	vector<vector<bool>> vis(2, vector<bool>(limit, 0));
	int prev = 0;
	while (q--) {
		int e; cin >> e;

		add((prev + e) % n, 0, vis);
		prev = add(((1 << len) - 1) ^ ((prev + e) % n), 1, vis);
		cout << prev << ' ';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while (t--) solve();
}