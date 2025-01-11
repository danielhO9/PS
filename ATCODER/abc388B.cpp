#include <bits/stdc++.h>
using namespace std;

int N, D;
int T[100], L[100];

void solve() {
	cin >> N >> D;
	for (int i = 0; i < N; ++i) cin >> T[i] >> L[i];
	for (int k = 1; k <= D; ++k) {
		int ans = -1;
		for (int i = 0; i < N; ++i) ans = max(ans, T[i] * (L[i] + k));
		cout << ans << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}