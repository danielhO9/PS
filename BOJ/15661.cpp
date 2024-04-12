#include <bits/stdc++.h>
using namespace std;

int N;
int S[20][20];
int power[1 << 20];


void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> S[i][j];
	memset(power, 0, sizeof(power));
	for (int i = 1; i < (1 << N); ++i) {
		for (int j = 0; j < N; ++j) if ((i >> j) & 1) {
			for (int k = 0; k < N; ++k) if ((i >> k) & 1) {
				power[i] += S[j][k];
			}
		}
	}
	int ans = 987654321;
	for (int i = 1; i < (1 << N); ++i) {
		ans = min(ans, abs(power[i] - power[(1 << N) - 1 - i]));
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}