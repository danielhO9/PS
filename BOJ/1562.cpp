#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9;

ll cache[100][1 << 10][10];
ll N;

ll matchCache(int n, int mask, int last) {
	ll& ret = cache[n][mask][last];
	if (ret != -1) return ret;
	if (n == 0) {
		if (__builtin_popcount(mask) == 1) {
			for (int i = 0; i < 10; ++i) if ((mask >> i) & 1) {
				if (last == i && i != 0) ret = 1;
				else ret = 0;
				break;
			}
		} else ret = 0;
		return ret;
	}
	ret = 0;
	if (!((mask >> last) & 1)) return ret;
	int nmask = (mask ^ (1 << last));
	if (last - 1 >= 0) {
		ret += matchCache(n - 1, nmask, last - 1);
		ret += matchCache(n - 1, mask, last - 1);
		ret %= MOD;
	}
	if (last + 1 < 10) {
		ret += matchCache(n - 1, nmask, last + 1);
		ret += matchCache(n - 1, mask, last + 1);
		ret %= MOD;
	}
	return ret;

}

void solve() {
	cin >> N;
	memset(cache, -1, sizeof(cache));
	ll ans = 0ll;
	for (int i = 0; i < 10; ++i) ans += matchCache(N - 1, (1 << 10) - 1, i), ans %= MOD;
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}