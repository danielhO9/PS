#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int N; cin >> N;
	vector<LL> dist(N); for (int i = 0; i < N - 1; ++i) cin >> dist[i];
	vector<LL> coin(N); for (int i = 0; i < N; ++i) cin >> coin[i];
	for (int i = 1; i < N; ++i) coin[i] = min(coin[i], coin[i - 1]);
	LL ans = 0;
	for (int i = 0; i < N - 1; ++i) ans += dist[i] * coin[i];
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}