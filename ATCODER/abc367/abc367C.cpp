#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, K;
int R[8];
int ans[8];

void dfs(int idx) {
	if (idx == N) {
		int sum = 0;
		for (int i = 0; i < N; ++i) sum += ans[i];
		if (sum % K) return;
		for (int i = 0; i < N; ++i) cout << ans[i] << ' ';
		cout << '\n';
		return;
	}
	for (int i = 1; i <= R[idx]; ++i) {
		ans[idx] = i;
		dfs(idx + 1);
	}
}

void solve() {
	cin >> N >> K;
	for (int i = 0; i < N; ++i) cin >> R[i];
	dfs(0);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}