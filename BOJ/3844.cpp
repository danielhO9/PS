#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;
ll n;
bool isPrime[10000001];
vector<ll> prime;

ll pow(ll a, ll b) {
	if (b == 0) return 1;
	ll h = pow(a, b / 2);
	h = (h * h) % MOD;
	if (b % 2) return (h * a) % MOD;
	else return h;
}

void init() {
	for (int i = 2; i <= 1e7; ++i) isPrime[i] = true;
	for (int i = 2; i <= 1e7; ++i) if (isPrime[i]) {
		prime.push_back(i);
		for (int j = i * 2; j <= 1e7; j += i) isPrime[j] = false;
	}
}

void solve() {
	ll ans = 1ll;
	for (auto i: prime) {
		if (i > n) break;
		ll cnt = 0;
		ll v = i, f = 1;
		while (true) {
			ll c = n / v;
			if (c == 0) break;
			cnt += c;
			v *= i; ++f;
		}
		if (cnt <= 1) break;
		ans *= pow(i, (cnt / 2) * 2);
		ans %= MOD;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	while (true) {
		cin >> n;
		if (n == 0) break;
		solve();
	}
}