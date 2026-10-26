#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, m;

void solve() {
	cin >> n >> m;
	int sx = 0, sy = 0;
	for (int i = 0; i < n; ++i) {
		int x, y; cin >> x >> y;
		if (i == 0) continue;
		sx += x;
		sy += y;
	}
	cout << (sx + sy + 2 * m) * 2 << '\n';

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}