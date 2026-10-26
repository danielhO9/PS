#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m;

void solve() {
	cin >> n >> m;
	cout << 1 + max(n, m) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}