#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

int N;
int a[21][21];
int cache[21][1 << 21];

int matchCache(int n, int mask) {
	int& ret = cache[n][mask];
	if (ret != -1) return ret;
	// cout << n << ' ' << mask << ' ';
	ret = 0;
	for (int i = 0; i < N; ++i) if (a[n][i] && ((mask >> i) & 1)) {
		if (n > 0) ret += matchCache(n - 1, mask ^ (1 << i));
		else ++ret;
		ret %= MOD;
	}
	// cout << ret << '\n';
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N; for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> a[i][j];
	memset(cache, -1, sizeof(cache));
	cout << matchCache(N - 1, (1 << N) - 1);
}