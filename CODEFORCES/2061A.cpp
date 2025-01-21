#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;
ll a[100];

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	int ocnt = 0, ecnt = 0;
	for (int i = 0; i < n; ++i) {
		if (a[i] % 2) ++ocnt;
		else ++ecnt;
	}
	if (ecnt > 0) cout << ocnt + 1 << '\n';
	else cout << ocnt - 1 << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}