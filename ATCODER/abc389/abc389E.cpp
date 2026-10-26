#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, M;
ll P[200000];

ll calc(ll x) {
	vector<ll> lk(N);
	ll m = 0;
	for (int i = 0; i < N; ++i) {
		ll p = x / P[i];
		ll k = (p + 1) / 2;
		lk[i] = k;
		if (k > 1e9) return M + 1;
		if (k * k > M / P[i]) return M + 1;
		m += k * k * P[i];
		if (m > M) return M + 1;
	}
	return M - 1;
}

void solve() {
	cin >> N >> M;
	for (int i = 0; i < N; ++i) cin >> P[i];
	ll l = 0, r = 2e18, mid;
	while (l + 1 < r) {
		mid = (l + r) / 2;
		if (calc(mid) <= M) l = mid;
		else r = mid;
	}
	ll x = l;
	vector<ll> lk(N);
	ll m = 0;
	for (int i = 0; i < N; ++i) {
		ll p = x / P[i];
		ll k = (p + 1) / 2;
		lk[i] = k;
		m += k * k * P[i];
	}
	priority_queue<pair<ll, ll>> pq;
	for (int i = 0; i < N; ++i) {
		ll val = (2 * lk[i] + 1) * P[i];
		pq.push({-val, i});
	}
	while (true) {
		auto cur = pq.top(); pq.pop();
		cur.first *= -1;
		if (cur.first + m > M) break;
		m += cur.first;
		++lk[cur.second];
		ll val = (2 * lk[cur.second] + 1) * P[cur.second];
		pq.push({-val, cur.second});
	}
	ll ans = 0;
	for (int i = 0; i < N; ++i) ans += lk[i];
	cout << ans;

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}