#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int calc(int n) {
	if (n == 1) return 1;
	if (n == 2) return 2;
	if (n == 4) return 2;
	return calc((n + 1) / 2 - 1) + 1;
}

void solve() {
	int n; cin >> n;
	cout << calc(n) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}