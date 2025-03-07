#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 

ll n, s, m;
ll t[100000];

ll f(ll tm) {
	if (tm == 0) return 0;
	ll ret = 0;
	for (ll i = 0; i < m; ++i) ret += ((tm - 1) / t[i]) + 1;
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> s;
	cin >> m;
	for (ll i = 0; i < m; ++i) cin >> t[i];
	ll l = 0, r = 100000001, mid;
	while (l + 1 < r) {
		mid = (l + r) / 2;
		if (f(mid) >= n - s) r = mid;
		else l = mid;
	}
	ll dif = n - s - f(r - 1);
	assert(dif >= 1);
	vector<ll> v;
	for (ll i = 0; i < m; ++i) if ((r - 1) % t[i] == 0) v.push_back(i);
	// cout << r << '\n';
	// for (auto i: v) cout << i << ' ';
	cout << v[dif - 1] + 1;
}

// 16 + 6 + 4