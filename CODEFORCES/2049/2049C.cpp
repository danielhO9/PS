#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
int x, y;
int ans[200001];

void solve() {
	cin >> n >> x >> y;
	for (int i = 1; i <= n; ++i) ans[i] = -1;
	if (x > y) swap(x, y);
	ans[x] = 0;
	ans[y] = 1;
	for (int i = x + 1; i < y; ++i) {
		if (ans[i + 1] != -1) {
			if (ans[i - 1] == 0) ans[i] = 2;
			else ans[i] = 0;
		} else {
			if (ans[i - 1] == 0) ans[i] = 1;
			else ans[i] = 0;
		}
	}
	for (int i = y % n + 1; i != x; i = i % n + 1) {
		int nxt = i % n + 1;
		int prv = (i - 1 == 0 ? n : i - 1);
		if (ans[nxt] != -1) {
			if (ans[prv] == 0) ans[i] = 1;
			else ans[i] = 2;
		} else {
			if (ans[prv] == 0) ans[i] = 1;
			else ans[i] = 0;
		}
	}
	for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}