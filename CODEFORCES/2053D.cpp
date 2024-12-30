#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, q;
const ll MOD = 998244353;
ll a[200001], b[200001];
ll idxa[200001], idxb[200001]; // v's idx

ll lpow(ll x, ll y) {
	if (y == 0) return 1ll;
	ll half = lpow(x, y / 2);
	half = (half * half) % MOD;
	if (y % 2) return (half * x) % MOD;
	else return half;
}

ll inv(ll x) {
	return lpow(x, MOD - 2);
}

void solve() {
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) cin >> b[i];

	vector<pair<ll, ll> > va, vb;
	for (int i = 1; i <= n; ++i) va.push_back(make_pair(a[i], i));
	for (int i = 1; i <= n; ++i) vb.push_back(make_pair(b[i], i));

	sort(va.begin(), va.end());
	sort(vb.begin(), vb.end());

	for (int i = 0; i < n; ++i) idxa[va[i].second] = i;
	for (int i = 0; i < n; ++i) idxb[vb[i].second] = i;
	ll ret = 1ll;
	for (int i = 0; i < n; ++i) {
		ret *= min(va[i].first, vb[i].first);
		ret %= MOD;
	}
	cout << ret << ' ';
	while (q--) {
		ll o, x; cin >> o >> x;
		if (o == 1) {
			ll prv_idx = idxa[x];
			ll nxt_idx = upper_bound(va.begin(), va.end(), make_pair(a[x], LLONG_MAX)) - va.begin();
			--nxt_idx;
			// cout << prv_idx << ' ' << nxt_idx << '\n';
			ret *= inv(min(va[prv_idx].first, vb[prv_idx].first)); ret %= MOD;
			if (prv_idx != nxt_idx) ret *= inv(min(va[nxt_idx].first, vb[nxt_idx].first)); ret %= MOD;

			idxa[x] = nxt_idx;
			idxa[va[nxt_idx].second] = prv_idx;
			swap(va[prv_idx], va[nxt_idx]);
			++va[nxt_idx].first;
			++a[x];

			ret *= min(va[prv_idx].first, vb[prv_idx].first); ret %= MOD;
			if (prv_idx != nxt_idx) ret *= min(va[nxt_idx].first, vb[nxt_idx].first); ret %= MOD;
		} else {
			ll prv_idx = idxb[x];
			ll nxt_idx = upper_bound(vb.begin(), vb.end(), make_pair(b[x], LLONG_MAX)) - vb.begin();
			--nxt_idx;
			ret *= inv(min(va[prv_idx].first, vb[prv_idx].first)); ret %= MOD;
			if (prv_idx != nxt_idx) ret *= inv(min(va[nxt_idx].first, vb[nxt_idx].first)); ret %= MOD;

			idxb[x] = nxt_idx;
			idxb[vb[nxt_idx].second] = prv_idx;
			swap(vb[prv_idx], vb[nxt_idx]);
			++vb[nxt_idx].first;
			++b[x];

			ret *= min(va[prv_idx].first, vb[prv_idx].first); ret %= MOD;
			if (prv_idx != nxt_idx) ret *= min(va[nxt_idx].first, vb[nxt_idx].first); ret %= MOD;
		}
		cout << ret << ' ';
		// for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
		// cout << '\n';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while (t--) solve();
}