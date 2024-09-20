#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;
vector<pair<ll, ll>> pt;
ll mx, my;

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		ll x, y; cin >> x >> y;
		pt.push_back({x, y});
	}
	sort(pt.begin(), pt.end());
	mx = pt[n / 2].first;
	my = pt[n / 2].second;
	if (n % 2) {
		cout << mx + (ll) 1e17 << ' ' << my + 1 << "\n";
		cout << mx - (ll) 1e17 << ' ' << my - 1 << "\n";
	} else {
		cout << mx + (ll) 1e17 << ' ' << my + (1 - 1) / 2 << "\n";
		cout << mx - (ll) 1e17 << ' ' << my - (1 + 1) / 2 << "\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}