#include <bits/stdc++.h>
using namespace std;

int cache[30][30];

int comb(int a, int b) {
	if (b == 0 || b == a) return 1;
	int& ret = cache[a][b];
	if (ret != -1) return ret;
	ret = comb(a - 1, b - 1) + comb(a - 1, b);
	return ret;
}

void solve() {
	int N, M; cin >> N >> M;
	cout << comb(M, N) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	memset(cache, -1, sizeof(cache));
	int t; cin >> t;
	while (t--) solve();
}