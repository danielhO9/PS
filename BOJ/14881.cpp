#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
	if (a < b) swap(a, b);
	if (b == 0) return a;
	return gcd(b, a % b);
}

int a, b, c;

void solve() {
	cin >> a >> b >> c;
	int g = gcd(a, b);
	if (c > a && c > b) {
		cout << "NO" << '\n';
		return;
	}
	if (c % g == 0) cout << "YES\n";
	else cout << "NO\n";
	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}