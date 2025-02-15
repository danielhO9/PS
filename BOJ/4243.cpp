#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, a;
ll t[101];
ll sm[101];
ll ssm[101];
ll cache[101][101][2];
const ll MAX = 15000000ll * 100ll * 100ll + 100ll;

ll dis(ll i, ll j) {
	if (i == j) return 0;
	if (i < j) return ssm[j] - ssm[i] - sm[i] * (j - i);
	else return (i - j) * sm[i] - (ssm[i - 1] - ssm[j - 1]);
}

ll matchCache(int l, int r, int pos) {
	if (a < l || r < a) return MAX;
	ll& ret = cache[l][r][pos];
	if (ret != -1) return ret;
	ret = MAX;
	if (pos == 0) {
		for (int i = l + 1; i <= r; ++i) {
			ret = min(ret, matchCache(i, r, 0) + dis(i, l) + (sm[i] - sm[l]) * (N - (r - l + 1))); // l <- i
			ret = min(ret, matchCache(i, r, 1) + dis(i, l) + (sm[i] - sm[l]) * (N - (r - l + 1)) + (sm[r] - sm[i]) * (N - (r - i + 1)) ); // l <- r
		}
	} else {
		for (int i = l; i < r; ++i) {
			ret = min(ret, matchCache(l, i, 0) + dis(i, r) + (sm[r] - sm[i]) * (N - (r - l + 1)) + (sm[i] - sm[l]) * (N - (i - l + 1)) ); // l -> r
			ret = min(ret, matchCache(l, i, 1) + dis(i, r) + (sm[r] - sm[i]) * (N - (r - l + 1))); // i -> r
		}
	}
	// cout << l << ' ' << r << ' ' << pos << ' ' << ret << "\n";
	return ret;
}

void solve() {
	cin >> N >> a;
	for (int i = 2; i <= N; ++i) cin >> t[i];
	for (int i = 2; i <= N; ++i) sm[i] = sm[i - 1] + t[i];
	for (int i = 2; i <= N; ++i) ssm[i] = ssm[i - 1] + sm[i];
	memset(cache, -1, sizeof(cache));
	cache[a][a][0] = 0;
	cache[a][a][1] = 0;
	cout << min(matchCache(1, N, 0), matchCache(1, N, 1)) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}