#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL n, P, l, t;

LL solution() {
	cin >> n >> P >> l >> t;
	LL task = (n - 1) / 7 + 1;
	LL ans = 0;
	if (task % 2 == 0) {
		ans += min((P + l + 2 * t - 1) / (l + 2 * t), task / 2);
		P -= ans * (l + 2 * t);
	} else {
		ans += min((P + l + 2 * t - 1) / (l + 2 * t), task / 2);
		P -= ans * (l + 2 * t);
		if (P > 0) ++ans;
		P -= (l + t);
	}
	if (P <= 0) return n - ans;
	ans += (P + l - 1) / l;
	return n - ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int tc; cin >> tc;
	while (tc--) cout << solution() << '\n';
}