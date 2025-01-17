#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, s, p;

void solve() {
	cin >> n >> s >> p;
	vector<pair<ll, ll>> v(n + 1);
	ll len = 0;
	for (int i = 0; i < n + 1; ++i) cin >> v[i].first >> v[i].second;
	for (int i = 0; i < n; ++i) {
		len += abs(v[i].first - v[i + 1].first) + abs(v[i].second - v[i + 1].second);
	}
	len *= s;
	cout << (len + p - 1) / p << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	for (int i = 1; i <= t; ++i) {
		cout << "Data Set " << i << ":\n";
		solve();
		cout << '\n';
	}
}