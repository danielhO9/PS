#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Query {
	ll s, e, idx;
};

ll cnt[50001];
ll n;
ll now = 0;
ll ans[50000];

void add(ll x) {
	ll tmp = x;
	while (2 <= tmp && tmp <= n) {
		++cnt[tmp];
		if (cnt[tmp] % tmp) break;
		++now;
		tmp = tmp * tmp;
	}
}

void del(ll x) {
	ll tmp = x;
	while (2 <= tmp && tmp <= n) {
		// cout << tmp << ' ' << cnt[tmp] << '\n';
		if (cnt[tmp] % tmp) {
			--cnt[tmp];
			break;
		}
		--now;
		--cnt[tmp];
		tmp = tmp * tmp;
	}
}

void solve() {
	cin >> n;
	for (ll i = 1; i <= n; ++i) cnt[i] = 0;
	now = 0;
	ll sqrtn = sqrt(n);
	ll a[n + 1];
	for (ll i = 1; i <= n; ++i) cin >> a[i];

	ll Q; cin >> Q;
	vector<Query> query(Q);
	for (ll i = 0; i < Q; ++i) {
		cin >> query[i].s >> query[i].e;
		query[i].idx = i;
	}

	sort(query.begin(), query.end(), [sqrtn](const Query& a, const Query& b) {
		if (a.s / sqrtn == b.s / sqrtn) return a.e < b.e;
		return a.s / sqrtn < b.s / sqrtn;
	});

	ll s = query[0].s, e = query[0].e;

	for (ll i = s; i <= e; ++i) {
		if (2 <= a[i] && a[i] <= n) ++cnt[a[i]];
	}
	
	for (ll i = 2; i <= n; ++i) {
		now += cnt[i] / i;
		if (i * i <= n) {
			cnt[i * i] += cnt[i] / i;
		}
	}

	for (ll i = 0; i < Q; ++i) {
		while (s < query[i].s) {
			del(a[s]);
			++s;
		}
		while (s > query[i].s) {
			--s;
			add(a[s]);
		}
		while (e < query[i].e) {
			++e;
			add(a[e]);
		}
		while (e > query[i].e) {
			del(a[e]);
			--e;
		}
		ans[query[i].idx] = now;
	}
	for (ll i = 0; i < Q; ++i) cout << ans[i] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	ll t; cin >> t;
	for (ll i = 1; i <= t; ++i) {
		cout << "Case #" << i << '\n';
		solve();
	}
}