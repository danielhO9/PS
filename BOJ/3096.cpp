#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, M;
int adj[1001][1001];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	while (M--) {
		int i, j; cin >> i >> j;
		adj[i][j] = 1;
	}
	ll ans = 0;
	for (int i = 1; i <= N; ++i) for (int j = i + 1; j <= N; ++j) {
		ll cnt = 0;
		for (int k = 1; k <= N; ++k) if (adj[i][k] && adj[j][k]) ++cnt;
		if (cnt != 0) ans += cnt * (cnt - 1) / 2;
	}
	cout << ans;
}