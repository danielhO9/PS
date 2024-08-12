#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n, c, k; cin >> n >> c >> k;
	string s; cin >> s;
	int presum[c][n + 1]; memset(presum, 0, sizeof(presum));
	for (int i = 0; i < c; ++i) {
		for (int j = 1; j <= n; ++j) {
			presum[i][j] = presum[i][j - 1] + (s[j - 1] == i + 'A');
		}
	}
	queue<int> q;
	bool bad[1 << c]; memset(bad, 0, sizeof(bad));
	for (int i = 1; i <= n - k + 1; ++i) {
		int l = i, r = i + k - 1;
		int tmp = 0;
		for (int j = 0; j < c; ++j) {
			if (presum[j][r] - presum[j][l - 1] == 0) tmp |= (1 << j);
		}
		bad[tmp] = 1; q.push(tmp);
	}
	int tmp = (1 << c) - 1;
	tmp ^= (1 << (s.back() - 'A'));
	bad[tmp] = 1; q.push(tmp);
	while (!q.empty()) {
		int here = q.front(); q.pop();
		// cout << here << ' ';
		for (int i = 0; i < c; ++i) if ((here >> i) & 1) {
			int there = (here ^ (1 << i));
			if (!bad[there]) {
				bad[there] = true;
				q.push(there);
			}
		}
	}
	int ans = c;
	for (int i = 0; i < (1 << c); ++i) if (!bad[i]) ans = min(ans, __builtin_popcount(i));
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--)solve();
}