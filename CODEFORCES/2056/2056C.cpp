#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;

void solve() {
	cin >> n;
	cout << 1 << ' ';
	for (int i = 1; i <= n - 3; ++i) cout << i << ' ';
	cout << 1 << ' ' << 2 << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}