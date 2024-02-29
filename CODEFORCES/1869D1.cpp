#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
unordered_map<ll, pair<ll, ll>> M;

void init() {
	for (ll i = 0; i <= 30; ++i) for (ll j = 0; j <= 30; ++j) if (i != j) {
		M[(1 << i) - (1 << j)] = make_pair(i, j);
		// cout << (1 << i) - (1 << j) << ' ' << i << ' ' << j <<'\n';
	}
}

void solve() {
	ll n; cin >> n;
	vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
	ll sum = 0;
	for (int i = 0; i < n; ++i) sum += a[i];
	if (sum % n != 0) {
		cout << "NO\n"; return;
	}
	ll ave = sum / n;
	vector<ll> get(31, 0), give(31, 0);
	for (ll i = 0; i < n; ++i) {
		ll num = ave - a[i];
		if (num == 0) continue;
		if (M.find(num) == M.end()) {
			cout << "NO\n"; return;
		}
		++get[M[num].first];
		++give[M[num].second];
	}
	for (int i = 0; i <= 30; ++i) if (get[i] != give[i]) {
		cout << "NO\n"; return;
	}
	cout << "YES\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	int t; cin >> t;
	while (t--) solve();
}