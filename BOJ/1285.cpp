#include <bits/stdc++.h>
using namespace std;

int coin[20];
int ans = 987654321;

void solve() {
	int N; cin >> N;
	for (int i = 0; i < N; ++i) {
		string s; cin >> s;
		int tmp = 0;
		for (int j = 0; j < N; ++j) {
			if (s[j] == 'H') tmp += (1 << j);
		}
		coin[i] = tmp;
	}
	for (int i = 0; i < (1 << N); ++i) {
		for (int j = 0; j < N; ++j) {
			if ((i >> j) & 1) for (int k = 0; k < N; ++k) coin[k] ^= (1 << j);
		}
		int tans = 0;
		for (int k = 0; k < N; ++k) {
			tans += min(__builtin_popcount(coin[k]), N - __builtin_popcount(coin[k]));
		}
		ans = min(ans, tans);
		for (int j = 0; j < N; ++j) {
			if ((i >> j) & 1) for (int k = 0; k < N; ++k) coin[k] ^= (1 << j);
		}
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}