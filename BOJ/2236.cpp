#include <bits/stdc++.h>
using namespace std;

int N, K;
int pri[50];
int ans[50];

void solve() {
	cin >> N >> K;
	for (int i = 0; i < N; ++i) cin >> pri[i];
	priority_queue<pair<int, int>> pq;
	for (int i = 0; i < N; ++i) pq.push({pri[i], i});
	for (int i = 0; i < min(N, K); ++i) {
		auto cur = pq.top(); pq.pop();
		ans[cur.second] = cur.second + 1;
	}
	int cnt = 0;
	for (int i = 0; i < N; ++i) if (ans[i] != 0) {
		++cnt;
		cout << i + 1 << '\n';
	}
	for (int i = 0; i < (K - cnt); ++i) cout << 0 << '\n';
	for (int i = 0; i < N; ++i) cout << ans[i] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}