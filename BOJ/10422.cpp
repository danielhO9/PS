#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;

ll cache[5001];
/*
((()))
()()
*/

ll matchCache(int l) {
	if (l % 2 == 1) return 0ll;
	if (l == 2 || l == 0) return 1ll;
	ll& ret = cache[l];
	if (ret != -1) return ret;
	ret = matchCache(l - 2);
	for (int i = 2; i <= l - 2; i += 2) {
		ret += matchCache(i - 2) * matchCache(l - i);
		ret %= MOD;
	}
	return ret;
}

void solve() {
	int L; cin >> L;
	cout << matchCache(L) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	memset(cache, -1, sizeof(cache));
	int t; cin >> t;
	while (t--) solve();
}