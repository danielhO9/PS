#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) {
		ll n, m; cin >> n >> m;
		int ans = 0;
		while (n > 0) {
			n /= 2;
			++ans;
		}
		cout << ans + m << '\n';
	}
}