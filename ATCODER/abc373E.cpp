#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, M, K;
ll A[200000];
vector<ll> s;
ll ssum[200000];

ll getVal(ll x) {
	ll tmp = lower_bound(s.begin(), s.end(), x) - s.begin();
	if (tmp == 0) return 0ll;
	return x * tmp - ssum[tmp - 1];
}

void solve() {
	cin >> N >> M >> K;
	for (ll i = 0; i < N; ++i) cin >> A[i];
	for (ll i = 0; i < N; ++i) K -= A[i];
	// cout << K << '\n';
	if (N == M) {
		for (ll i = 0; i < N; ++i) cout << 0 << ' ';
		return;
	}
	vector<ll> tmp;
	for (ll i = 0; i < N; ++i) tmp.push_back(A[i]);
	sort(tmp.begin(), tmp.end());
	for (ll i = N - 1 - M; i < N; ++i) s.push_back(tmp[i]);
	ssum[0] = s[0];
	for (ll i = 1; i < M + 1; ++i) ssum[i] = ssum[i - 1] + s[i];

	for (ll i = 0; i < N; ++i) {
		ll val;
		if (s[0] <= A[i]) val = A[i];
		else val = s[0];
		ll r = K;
		ll sval = getVal(K + A[i] + 1);
		sval -= max(0ll, (K + A[i] + 1) - val);
		if (sval == 0) {
			cout << -1 << ' ';
			continue;
		}
		ll l = -1;
		while (l + 1 < r) {
			ll mid = (l + r) / 2;
			sval = getVal(mid + A[i] + 1);
			sval -= max(0ll, (mid + A[i] + 1) - val);
			if (sval <= K - mid) l = mid;
			else r = mid;
		}
		cout << r << ' ';

	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}