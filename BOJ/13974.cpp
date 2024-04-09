#include <bits/stdc++.h>
using namespace std;

int cache[5000][5000], opt[5000][5000];
int sum[5000];

void solve() {
	int K; cin >> K;
	for (int i = 0; i < K; ++i) for (int j = 0; j < K; ++j) cache[i][j] = 987654321;
	for (int i = 0; i < K; ++i) cache[i][i] = 0;
	for (int i = 0; i < K; ++i) {
		cin >> sum[i];
		if (i != 0) sum[i] += sum[i - 1];
	}
	for (int i = 0; i < K; ++i) opt[i][i] = i;
	for (int dif = 1; dif < K; ++dif) {
		for (int s = 0; s + dif < K; ++s) {
			// s, s + dif
			for (int i = opt[s][s + dif - 1]; i <= min(opt[s + 1][s + dif], s + dif - 1); ++i) {
				if (cache[s][s + dif] > cache[s][i] + cache[i + 1][s + dif] + (s == 0 ? sum[s + dif] : sum[s + dif] - sum[s - 1])) {
					cache[s][s + dif] = cache[s][i] + cache[i + 1][s + dif] + (s == 0 ? sum[s + dif] : sum[s + dif] - sum[s - 1]);
					opt[s][s + dif] = i;
				}
			}
		}
	}
	cout << cache[0][K - 1] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}