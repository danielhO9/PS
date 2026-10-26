#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
int K[20];

void solve() {
	cin >> N;
	int ans = INT32_MAX;
	for (int i = 0; i < N; ++i) cin >> K[i];
	int sumK = 0;
	for (int i = 0; i < N; ++i) sumK += K[i];
	for (int i = 0; i < (1 << N); ++i) {
		int cnt = 0;
		for (int j = 0; j < N; ++j) if ((i >> j) & 1) {
			cnt += K[j];
		}
		cnt = max(cnt, sumK - cnt);
		ans = min(ans, cnt);
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}