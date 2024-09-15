#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Query {
	int s, e, idx;
};

void solve() {
	int n; cin >> n;
	int sqrtn = sqrt(n);
	ll a[n + 1];
	for (int i = 1; i <= n; ++i) cin >> a[i];

	int Q; cin >> Q;
	vector<Query> query(Q);
	for (int i = 0; i < Q; ++i) {
		cin >> query[i].s >> query[i].e;
		query[i].idx = i;
	}

	sort(query.begin(), query.end(), [sqrtn](const Query& a, const Query& b) {
		if (a.s / sqrtn == b.s / sqrtn) return a.e < b.e;
		return a.s / sqrtn < b.s / sqrtn;
	});

	int s = query[0].s, e = query[0].e;
	unordered_map<ll, ll> M; ll now = 0;
	ll ans[Q];

	for (int i = s; i <= e; ++i) {
		ll tmp = a[i];
		if (tmp == 1 || tmp > n) continue;
		++M[tmp];
		while (M[tmp] == tmp) {
			++now;
			M[tmp] = 0;
			++M[tmp * tmp];
			tmp = tmp * tmp;
		}
	}

	for (int i = 0; i < Q; ++i) {
		while (s < query[i].s) {
			ll tmp = a[s];
			if (tmp == 1 || tmp > n) {
				++s;
				continue;
			}
			while (M[tmp] == 0) {
				--now;
				M[tmp] = tmp - 1;
				tmp = tmp * tmp;
			}
			--M[tmp];
			++s;
		}
		while (s > query[i].s) {
			--s;
			ll tmp = a[s];
			if (tmp == 1 || tmp > n) continue;
			++M[tmp];
			while (M[tmp] == tmp) {
				++now;
				M[tmp] = 0;
				++M[tmp * tmp];
				tmp = tmp * tmp;
			}
		}
		while (e < query[i].e) {
			++e;
			ll tmp = a[e];
			if (tmp == 1 || tmp > n) continue;
			++M[tmp];
			while (M[tmp] == tmp) {
				++now;
				M[tmp] = 0;
				++M[tmp * tmp];
				tmp = tmp * tmp;
			}
		}
		while (e > query[i].e) {
			ll tmp = a[e];
			if (tmp == 1 || tmp > n) {
				--e;
				continue;
			}
			while (M[tmp] == 0) {
				--now;
				M[tmp] = tmp - 1;
				tmp = tmp * tmp;
			}
			--M[tmp];
			--e;
		}
		ans[query[i].idx] = now;
	}
	for (int i = 0; i < Q; ++i) cout << ans[i] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	for (int i = 1; i <= t; ++i) {
		cout << "Case #" << i << '\n';
		solve();
	}
}