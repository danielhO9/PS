#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, M;
ll B[200000], W[200000];
ll smB[200000], smW[200000];

void solve() {
	cin >> N >> M;
	for (int i = 0; i < N; ++i) cin >> B[i];
	for (int i = 0; i < M; ++i) cin >> W[i];
	sort(B, B + N); sort(W, W + M);
	reverse(B, B + N); reverse(W, W + M);
	smB[0] = B[0], smW[0] = W[0];
	for (int i = 1; i < N; ++i) smB[i] = smB[i - 1] + B[i];
	for (int i = 1; i < M; ++i) smW[i] = smW[i - 1] + W[i];
	ll ans = 0;
	ll mx = -1e15;
	if (N > M) mx = *max_element(smB + M, smB + N);
	for (int i = M - 1; i >= 0; --i) {
		if (i >= N) continue;
		mx = max(mx, smB[i]);
		ans = max(ans, smW[i] + mx);
	}
	ans = max(ans, mx);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}