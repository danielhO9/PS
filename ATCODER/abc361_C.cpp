#include <bits/stdc++.h>
using namespace std;

void solve() {
	int N, K; cin >> N >> K;
	vector<int> A(N); for (int i = 0; i < N; ++i) cin >> A[i];
	sort(A.begin(), A.end());
	int ans = 1e9;
	for (int i = 0; i < N; ++i) {
		int nxt = i + N - K - 1;
		if (nxt == N) break;
		ans = min(ans, A[nxt] - A[i]);
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}