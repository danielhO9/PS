#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, X;
ll A[100], P[100], B[100], Q[100];

ll gcd(ll a, ll b) {
	if (a > b) swap(a, b);
	if (a == 0) return b;
	return gcd(b % a, a);
}

bool possible(ll x) {
	ll tmp = 0ll;
	for (int i = 0; i < N; ++i) {
		ll lcd = A[i] * B[i] / gcd(A[i], B[i]);

		ll t = x / lcd;
		t = max(t - 1, 0ll);
		ll rem = x - t * lcd;
		tmp += min((lcd / B[i]) * Q[i] * t, (lcd / A[i]) * P[i] * t);

		ll cnt = LLONG_MAX;
		for (ll b = 0; b <= (rem + B[i] - 1) / B[i]; ++b) {
			
			ll a = (max(0ll, rem - B[i] * b) + A[i] - 1) / A[i];
			cnt = min(cnt, a * P[i] + b * Q[i]);
		}
		tmp += cnt;
	}
	// cout << x << ' ' << (tmp <= X) << '\n';
	return tmp <= X;
}

void solve() {
	cin >> N >> X;
	for (int i = 0; i < N; ++i) cin >> A[i] >> P[i] >> B[i] >> Q[i];
	ll l = 0, r = 1e9 + 1;
	while (l + 1 < r) {
		ll mid = (l + r) / 2;
		if (possible(mid)) l = mid;
		else r = mid;
	}
	cout << l;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}