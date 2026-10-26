#include <bits/stdc++.h>
using namespace std;

int cache[100000];
int h[100000];
int N;

int matchCache(int x) {
	if (x == 0) return 0;
	if (x == 1) return abs(h[1] - h[0]);
	int& ret = cache[x];
	if (ret != -1) return ret;
	ret = min(matchCache(x - 1) + abs(h[x] - h[x - 1]), matchCache(x - 2) + abs(h[x] - h[x - 2]));
	return ret;
}

void solve() {
	memset(cache, -1, sizeof(cache));
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> h[i];
	cout << matchCache(N - 1);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}