#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL calc(LL d, vector<LL>& cor) {
	LL ans = 0;
	for (LL i = 0; i < cor.size(); ++i) ans += abs(cor[i] - d * i);
	return ans;
}

void solve() {
	LL N; cin >> N;
	vector<LL> cor(N); for (int i = 0; i < N; ++i) cin >> cor[i];
	LL l = 0, r = cor[N - 1], mid1, mid2;
	while (r - l >= 3) {
		mid1 = (l * 2 + r) / 3;
		mid2 = (l + r * 2) / 3;
		if (calc(mid1, cor) <= calc(mid2, cor)) r = mid2;
		else l = mid1;
	}
	LL ans = LLONG_MAX;
	for (LL i = l; i <= r; ++i) ans = min(ans, calc(i, cor));
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}