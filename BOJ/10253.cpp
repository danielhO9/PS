#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
	if (a < b) swap(a, b);
	if (b == 0) return a;
	return gcd(b, a % b);
}

void solve() {
	ll a, b; cin >> a >> b;
	while (a != 1) {
		ll x = (b + a - 1) / a;
		ll g = gcd(x, b);
		ll l = g * x * b;
		a *= (l / b);
		a -= (l / x);
		b = l;
		g = gcd(a, b);
		a /= g;
		b /= g;
	}
	cout << b << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}