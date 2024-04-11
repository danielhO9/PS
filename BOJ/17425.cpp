#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll ans[1000001];

void init() {
	memset(ans, 0, sizeof(ans));
	for (ll i = 1; i <= 1e6; ++i) {
		ll now = i;
		while (now <= 1e6) {
			ans[now] += i;
			now += i;
		}
	}
	for (int i = 2; i <= 1e6; ++i) ans[i] += ans[i - 1];
}

void solve() {
	int N; cin >> N;
	cout << ans[N] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	int t; cin >> t;
	while (t--) solve();
}