#include <bits/stdc++.h>
using namespace std;
int N, C[3][1000], cache[3][1000];

int matchCache(int t, int n) {
	if (n == 0) return C[t][0];
	int& ret = cache[t][n];
	if (ret != -1) return ret;
	ret = 987654321;
	for (int i = 0; i < 3; ++i) if (i != t) ret = min(ret, matchCache(i, n - 1) + C[t][n]);
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	memset(cache, -1, sizeof(cache));
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> C[0][i] >> C[1][i] >> C[2][i];
	cout << min({matchCache(0, N - 1), matchCache(1, N - 1), matchCache(2, N - 1)});
}