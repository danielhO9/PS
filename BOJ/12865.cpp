#include <bits/stdc++.h>
using namespace std;

int N, K;
int W[100], V[100];
int cache[100][100001];

int matchCache(int n, int w) {
	int& ret = cache[n][w];
	if (ret != -1) return ret;
	if (n == 0) {
		if (w >= W[n]) ret = V[n];
		else ret = 0;
		return ret;
	}
	if (w >= W[n]) ret = max(ret, matchCache(n - 1, w - W[n]) + V[n]);
	ret = max(ret, matchCache(n - 1, w));
	return ret;
}

void solve() {
	cin >> N >> K;
	for (int i = 0; i < N; ++i) cin >> W[i] >> V[i];
	memset(cache, -1, sizeof(cache));
	cout << matchCache(N - 1, K);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}