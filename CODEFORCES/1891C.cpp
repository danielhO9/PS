#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int n; cin >> n;
	LL sum = 0;
	LL a[n]; for (int i = 0; i < n; ++i) {
		cin >> a[i];
		sum += a[i];
	}
	sort(a, a + n);
	int s = 0, e = n - 1;
	LL dec = 0;
	while (true) {
		if (s == e && a[s] == 0) break;
		LL x = 0;
		while (true) {
			// cout << s << ' ' << e << '\n';
			if (s == e) {
				x += a[s] / 2;
				a[s] = 0;
				break;
			} else {
				if (a[s] <= a[e]) {
					x += a[s];
					a[e] -= a[s];
					a[s] = 0;
					++s;
					if (a[e] == 0) {
						if (s < e) --e;
						break;
					}
				} else {
					x += a[e];
					a[s] -= a[e];
					a[e] = 0;
					--e; break;
				}
			}
		}
		dec += max(0LL, x - 1);
		// cout << "들어감 " << dec << '\n';
	}
	cout << sum - dec << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}

/*
1
4
1 3 1 1
*/