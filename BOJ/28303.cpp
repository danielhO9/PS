#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, K;
ll a[500000];
ll val[500000];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> K;
	for (int i = 0; i < N; ++i) cin >> a[i];
	for (int i = 0; i < N; ++i) val[i] = a[i] + i * K;
	ll ans = LLONG_MIN;
	ll mx = val[0];
	for (int i = 1; i < N; ++i) {
		ans = max(ans, mx - i * K - a[i]);
		mx = max(mx, val[i]);
	}
	for (int i = 0; i < N; ++i) val[i] = -a[i] + i * K;
	mx = val[0];
	for (int i = 1; i < N; ++i) {
		ans = max(ans, mx + a[i] - i * K);
		mx = max(mx, val[i]);
	}
	cout << ans;
}