#include <bits/stdc++.h>
using namespace std;

int cache[100000];
int h[100000];
int N, K;

int matchCache(int x) {
	if (x == 0) return 0;
	int& ret = cache[x];
	if (ret != -1) return ret;
	ret = INT32_MAX;
	for (int i = 1; i <= K; ++i) if (x >= i) {
		ret = min(ret, matchCache(x - i) + abs(h[x] - h[x - i]));
	}
	return ret;
}

void solve() {
	memset(cache, -1, sizeof(cache));
	cin >> N >> K;
	for (int i = 0; i < N; ++i) cin >> h[i];
	cout << matchCache(N - 1);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}