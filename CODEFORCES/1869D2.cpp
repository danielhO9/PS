#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
unordered_map<ll, pair<ll, ll>> M;

void init() {
	for (ll i = 0; i <= 30; ++i) for (ll j = 0; j <= 30; ++j) if (i != j) {
		M[(1 << i) - (1 << j)] = make_pair(i, j);
	}
}

void solve() {
	ll n; cin >> n;
	vector<ll> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
	ll sum = 0;
	for (int i = 0; i < n; ++i) sum += a[i];
	if (sum % n != 0) {
		cout << "NO\n"; return;
	}
	ll ave = sum / n;
	vector<ll> bit(31, 0), getPow(31, 0), givePow(31, 0);
	for (int i = 0; i < n; ++i) {
		ll num = ave - a[i];
		if (num == 0) continue;
		if (__builtin_popcount(abs(num)) == 1) {
			ll log = log2(abs(num));
			if (num > 0) ++getPow[log];
			else ++givePow[log];
			continue;
		}
		if (M.find(num) == M.end()) {
			cout << "NO\n"; return;
		}
		++bit[M[num].first]; --bit[M[num].second];
	}
	for (int i = 30; i >= 1; --i) {
		bit[i] += getPow[i] - givePow[i];
		if (bit[i] == 0) continue;
		if (bit[i] > 0) {
			givePow[i - 1] -= bit[i];
			bit[i - 1] += bit[i];
			if (givePow[i - 1] < 0) {
				cout << "NO\n"; return;
			}
		} else {
			getPow[i - 1] -= abs(bit[i]);
			bit[i - 1] -= abs(bit[i]);
			if (getPow[i - 1] < 0) {
				cout << "NO\n"; return;
			}
		}
	}
	bit[0] += getPow[0] - givePow[0];
	if (bit[0] == 0) {
		cout << "YES\n"; return;
	} else {
		cout << "NO\n"; return;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	int t; cin >> t; while (t--) solve();
}