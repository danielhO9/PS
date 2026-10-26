#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, d;

void solve() {
	cin >> n >> d;
	cout << 1 << ' ';
	if (d % 3 == 0 || n >= 3) cout << 3 << ' ';
	if (d == 5) cout << 5 << ' ';
	if (n >= 3 || (n == 2 && d == 7)) cout << 7 << ' ';
	if (n >= 6 || (n >= 3 && d % 3 == 0) || d % 9 == 0) cout << 9 << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}