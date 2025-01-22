#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
ll a[400];
ll cache[400][400];

ll matchCache(ll l, ll r) {
	if (l == r) return 0;
	ll& ret = cache[l][r];
	if (ret != -1) return ret;
	ret = LLONG_MAX;
	ll sum = 0;
	for (int i = l; i <= r; ++i) sum += a[i];
	for (int d = l; d < r; ++d) {
		ret = min(ret, sum + matchCache(l, d) + matchCache(d + 1, r));
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	memset(cache, -1, sizeof(cache));
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> a[i];
	cout << matchCache(0, N - 1);
}