#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL gcd(LL a, LL b) {
	if (a < b) swap(a, b);
	if (b == 0) return a;
	return gcd(b, a % b);
}

void solve() {
	LL a, b; cin >> a >> b;
	LL g = gcd(a, b);
	LL l = a * b / g;
	if (b == l) {
		cout << b * b / g << '\n';
		return;
	}
	cout << l << '\n';
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}