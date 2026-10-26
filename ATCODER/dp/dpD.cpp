#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, W;
ll w[100], v[100];
ll cache[100001][100];

ll matchCache(ll l, ll n) {
	if (n == 0) {
		if (l >= w[n]) return v[n];
		else return 0;
	}
	ll& ret = cache[l][n];
	if (ret != -1) return ret;
	ret = matchCache(l, n - 1);
	if (l >= w[n]) ret = max(ret, matchCache(l - w[n], n - 1) + v[n]);
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	memset(cache, -1, sizeof(cache));
	cin >> N >> W;
	for (ll i = 0; i < N; ++i) cin >> w[i] >> v[i];
	cout << matchCache(W, N - 1);
}