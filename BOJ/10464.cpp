#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL ans(LL x) {
	if (x % 4 == 3) return 0;
	LL temp = x;
	while (temp % 4 != 0) --temp;
	LL ans = 0;
	for (LL i = temp; i <= x; ++i) ans ^= i;
	return ans;
}

void solve() {
	LL S, F; cin >> S >> F;
	LL ret = ans(S - 1) ^ ans(F);
	cout << ret << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
}