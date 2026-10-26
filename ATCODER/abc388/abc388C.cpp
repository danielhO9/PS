#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
ll A[500001];

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> A[i];
	A[N] = 2e9 + 1;
	ll ans = 0;
	int idx = 0;
	for (int i = 0; i < N; ++i) {
		while (A[i] * 2 > A[idx]) ++idx;
		ans += (N - idx);
		// cout << idx << '\n';
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}