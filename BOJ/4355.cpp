#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll getPhi(ll na) {
	ll a = na;
	if (na == 1) return 0;
	vector<bool> isPrime(100000, 1);
	ll phi = 1ll;
	vector<pair<ll, ll>> v;
	for (int i = 2; i < 1e5; ++i) {
		if (a == 1ll) break;
		if (!isPrime[i]) continue;
		for (int j = i * 2; j < 1e5; j += i) isPrime[j] = 0;
		ll cnt = 0;
		while (a % i == 0) {
			a /= i;
			++cnt;
		}
		if (cnt != 0) v.push_back({i, cnt});
	}
	if (v.empty() || (v.size() == 1 && v[0].second == 1 && a == 1ll)) {
		phi = na - 1;
		return phi;
	}
	for (auto [i, j]: v) {
		ll tmp = pow(i, j);
		phi *= (tmp - (tmp / i));
	}
	if (a != 1) phi *= a - 1;
	return phi;
}

void solve() {
	while (true) {
		ll n; cin >> n;
		if (n == 0) break;
		cout << getPhi(n) << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}