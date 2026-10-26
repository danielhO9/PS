#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n, k; cin >> n >> k;
	cout << (n - 1 + k - 2) / (k - 1) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}