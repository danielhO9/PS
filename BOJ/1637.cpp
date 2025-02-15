#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
ll A[20000], C[20000], B[20000];

ll f(ll x) {
	ll ret = 0;
	for (ll i = 0; i < N; ++i) if (A[i] <= C[i] && A[i] <= x) {
		ll mx = min(C[i], x);
		ret += (mx - A[i]) / B[i] + 1;
	}
	// cout << x << ' ' << ret << '\n';
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (ll i = 0; i < N; ++i) cin >> A[i] >> C[i] >> B[i];
	ll l = 0, r = INT32_MAX, mid;
	if (f(r) % 2 == 0) {
		cout << "NOTHING";
		return;
	}
	while (l + 1 < r) {
		mid = (l + r) / 2;
		if (f(mid) % 2) r = mid;
		else l = mid;
	}
	
	cout << r << ' ' << f(r) - f(r - 1);
}