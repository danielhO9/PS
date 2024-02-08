#include <bits/stdc++.h>
using namespace std;

int cache[128][128];
int ans[1 << 21];

// 111 110 101 100 011 010 001

// 1111000
// 1100110
// 1010101

void init() {
	memset(cache, -1, sizeof(cache));
	for (int i = 0; i < (1 << 21); ++i) ans[i] = INT32_MAX;
	queue<pair<int, int>> Q;
	int a = 120, b = 102, m = 85;
	Q.push({a, b}); cache[a][b] = 0;
	while (!Q.empty()) {
		auto [c, d] = Q.front(); Q.pop();
		pair<int, int> V[4] = {{c & d, d}, {c | d, d}, {c, c ^ d}, {c, d ^ m}};
		for (auto i: V) if (cache[i.first][i.second] == -1) {
			cache[i.first][i.second] = cache[c][d] + 1;
			Q.push(i);
		}
	}
	for (int i = 0; i < 128; ++i) for (int j = 0; j < 128; ++j) for (int k = 0; k < 128; ++k) {
		int temp = 0;
		for (int l = 0; l < 7; ++l) {
			if ((k >> l) & 1) temp += (2 * ((i >> l) & 1) + ((j >> l) & 1)) << (3 * l);
			else temp += 1 << (3 * l + 2);
		}
		if (cache[i][j] >= 0) ans[temp] = min(ans[temp], cache[i][j]);
	}
	// cout << ans[1194276];
}

void solve() {
	int a, b, c, d, m; cin >> a >> b >> c >> d >> m;
	vector<int> temp(7, 4);
	for (int i = 0; i < 30; ++i) {
		int ai = (a >> i) & 1, bi = (b >> i) & 1, ci = (c >> i) & 1, di = (d >> i) & 1, mi = (m >> i) & 1;
		if (4 * ai + 2 * bi + mi == 0) {
			if (2 * ci + di != 0) {
				cout << "-1\n"; return;
			}
		} else {
			if (temp[4 * ai + 2 * bi + mi - 1] != 4 && temp[4 * ai + 2 * bi + mi - 1] != 2 * ci + di) {
				cout << "-1\n"; return;
			} else {
				temp[4 * ai + 2 * bi + mi - 1] = 2 * ci + di;
			}
		}
	}
	int ret = 0;
	for (int i = 0; i < 7; ++i) ret += temp[i] << (3 * i);
	// cout << ret;
	if (ans[ret] == INT32_MAX) {
		cout << "-1\n"; return;
	} else {
		cout << ans[ret] << '\n';
		return;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	int t; cin >> t;
	while (t--) solve();
}