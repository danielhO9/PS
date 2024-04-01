#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<ll, pair<ll, ll>> exEucild(ll a, ll b) {
	bool inv = a < b;
	if (inv) swap(a, b);
    if (b == 0) return {a, {1, 0}};
    pair<ll, pair<ll, ll>> ret = exEucild(b, a % b);
    ll g, x, y;
    g = ret.first;
    x = ret.second.first, y = ret.second.second;
    if (inv) return {g, {x - (a / b) * y, y}};
	else return {g, {y, x - (a / b) * y}};
}

void solve() {
	ll K, C; cin >> K >> C;
	auto gcd = exEucild(K, C);
	if (gcd.second.second <= 0) {
		ll temp = abs(gcd.second.second) / K + 1;
		gcd.second.second += temp * K;
		gcd.second.first -= temp * C;
	}
	if (gcd.second.first == 0) {
		gcd.second.second += K;
	}
	if (gcd.first != 1 || gcd.second.second > 1e9) {
		cout << "IMPOSSIBLE\n";
		return;
	}
	cout << gcd.second.second << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}