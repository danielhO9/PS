#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, q;
int por[200000];
vector<int> pts[16];

void query(int x, int y) {
	for (int i = 0; i < 4; ++i) {
		if (((por[x] >> i) & 1) && ((por[y] >> i) & 1)) {
			cout << y - x << '\n';
			return;
		}
	}
	int ans = INT32_MAX;
	for (int i = 0; i < 4; ++i) if (((por[x] >> i) & 1)) {
		for (int j = 0; j < 4; ++j) if (((por[y] >> j) & 1)) {
			int pos = (1 << i) + (1 << j);
			int idx = lower_bound(pts[pos].begin(), pts[pos].end(), x) - pts[pos].begin();
			if (idx != pts[pos].size()) {
				if (pts[pos][idx] <= y) {
					cout << y - x << '\n';
					return;
				}
				ans = min(ans, 2 * pts[pos][idx] - x - y);
			}
			if (idx != 0) {
				--idx;
				ans = min(ans, x + y - 2 * pts[pos][idx]);
			}

		}
	}
	if (ans == INT32_MAX) cout << -1 << '\n';
	else cout << ans << '\n';
	return;
}

void solve() {
	cin >> n >> q;
	for (int i = 0; i < 16; ++i) pts[i].clear();
	for (int i = 0; i < n; ++i) {
		string s; cin >> s;
		int tmp = 0;
		for (int j = 0; j < 2; ++j) {
			if (s[j] == 'R') tmp += (1 << 0);
			if (s[j] == 'G') tmp += (1 << 1);
			if (s[j] == 'B') tmp += (1 << 2);
			if (s[j] == 'Y') tmp += (1 << 3);
		}
		por[i] = tmp;
		pts[tmp].push_back(i);
	}
	while (q--) {
		int x, y; cin >> x >> y; --x; --y;
		if (x > y) swap(x, y);
		query(x, y);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}