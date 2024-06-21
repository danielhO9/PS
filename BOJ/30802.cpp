#include <bits/stdc++.h>
using namespace std;

void solve() {
	int N, sz[6], T, P;
	cin >> N;
	for (int i = 0; i < 6; ++i) cin >> sz[i];
	cin >> T >> P;
	int ans = 0;
	for (int i = 0; i < 6; ++i) {
		ans += (sz[i] + T - 1) / T;
	}
	cout << ans << '\n';
	cout << N / P << ' ' << N % P;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}