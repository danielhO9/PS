#include <bits/stdc++.h>
using namespace std;

bool vis[14348907];
int three[16];

void query(int q, int x) {
	if (q == 1) {
		if (vis[x]) return;
		deque<int> Q;
		vis[x] = true; Q.push_back(x);
		while (!Q.empty()) {
			int here = Q.front(); Q.pop_front();
			for (int i = 0; i < 15; ++i) {
				int tmp = (here / three[i]) % 3;
				if (tmp != 0) {
					int there = here - tmp * three[i];
					if (vis[there]) continue;
					vis[there] = true;
					Q.push_back(there);
				}
			}
		}
	} else {
		int ans = 0;
		int here = 0;
		for (int i = 14; i >= 0; --i) {
			int xi = (x / three[i]) % 3;
			if (xi == 2) {
				ans += 2 * three[i];
				continue;
			}
			else if (xi == 1) {
				if (vis[here + 2 * three[i]]) {
					ans += 2 * three[i];
					here += 2 * three[i];
				}
				else {
					ans += three[i];
					continue;
				}
			} else {
				if (vis[here + 2 * three[i]]) {
					ans += 2 * three[i];
					here += 2 * three[i];
				}
				else if (vis[here + three[i]]) {
					ans += three[i];
					here += three[i];
				}
				else continue;
			}
		}
		cout << ans << '\n';
	}
}

void init() {
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i <= 15; ++i) {
		if (i == 0) three[i] = 1;
		else three[i] = three[i - 1] * 3;
	}
}

void solve() {
	init();
	int M; cin >> M;
	while (M--) {
		int q, x; cin >> q >> x;
		query(q, x);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}