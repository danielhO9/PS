#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	LL n; cin >> n;
	LL a[n], b[n];
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) cin >> b[i];
	LL mina = a[0], minb = b[0];
	LL suma = 0, sumb = 0;
	for (int i = 0; i < n; ++i) {
		suma += a[i];
		sumb += b[i];
		mina = min(mina, a[i]);
		minb = min(minb, b[i]);
	}
	cout << min(suma + minb * n, sumb + mina * n) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}