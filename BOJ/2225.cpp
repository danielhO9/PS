#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9;

ll cache[201][201];

ll matchCache(int n, int k) {
	if (k == 1) return 1;
	if (k == 0) {
		if (n == 0) return 1;
		return 0;
	}
	ll& ret = cache[n][k];
	if (ret != -1) return ret;
	ret = 0;
	for (int i = 0; i <= n; ++i) {
		ret += matchCache(n - i, k - 1); ret %= MOD;
	}
	return ret;
}

void solve() {
	int N, M; cin >> N >> M;
	memset(cache, -1, sizeof(cache));
	cout << matchCache(N, M);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}