#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, M, Q;
ll pos[100001], cpos[100001];

void solve() {
	cin >> N >> M >> Q;
	for (ll i = 0; i < M; ++i) {
		ll P, d; cin >> P >> d;
		if (d) ++cpos[P];
		else ++pos[P];
	}
	for (ll i = 1; i <= N; ++i) {
		pos[i] += pos[i - 1];
		cpos[i] += cpos[i - 1];
	}
	while (Q--) {
		ll P, X; cin >> P >> X;
		ll ans = 0ll;
		ll tmp = (X - 1) / M;
		ans += tmp * N;
		X -= tmp * M;
		ll l = -1, r = N - 1;
		while (l + 1 < r) {
			ll mid = (l + r) / 2;
			ll val = 0;
			ll s = max(P - mid, 1ll);
			val += pos[P] - pos[s - 1];
			if (P - mid < 1) {
				s = P - mid + N;
				val += pos[N] - pos[s - 1];
			}
			ll rr = min(P + mid, N);
			val += cpos[rr] - cpos[P - 1];
			if (P + mid > N) {
				rr = P + mid - N;
				val += cpos[rr] - cpos[0];
			}
			if (val >= X) r = mid;
			else l = mid;
			// cout << mid << ' ' << val << '\n';
		}
		cout << r + ans << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}