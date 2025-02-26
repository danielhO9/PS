#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, Q;
ll X[200000];
ll sm[200000];


int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> Q;
	for (int i = 0; i < N; ++i) cin >> X[i];
	for (int i = 0; i < N; ++i) {
		if (i) sm[i] = sm[i - 1] + X[i];
		else sm[i] = X[i];
	}
	while (Q--) {
		ll L, R; cin >> L >> R;
		auto l = lower_bound(X, X + N, L) - X;
		auto r = lower_bound(X, X + N, R) - X;
		if (r == N || X[r] > R) --r;
		if (r < 0 || l > r) {
			cout << 0 << '\n';
			continue;
		}
		ll mid = (l + r) / 2;
		ll mx = sm[r] - sm[l] - X[l] * (r - l);
		ll nmx = X[r] * (r - l) - (r == 0 ? 0 : sm[r - 1]) + (l == 0 ? 0 : sm[l - 1]);
		mx = max(mx, nmx);
		ll mn = sm[r] - sm[mid] - X[mid] * (r - mid) - (mid == 0 ? 0 : sm[mid - 1]) + (l == 0 ? 0 : sm[l - 1]) + X[mid] * (mid - l);
		// cout << mx << ' ' << mn << '\n';
		cout << mx - mn << '\n';
	}

}