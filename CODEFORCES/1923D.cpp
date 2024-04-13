#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	ll n; cin >> n;
	vector<ll> a(n + 2, 0); for (int i = 1; i <= n; ++i) cin >> a[i];
	vector<ll> difl(n + 2, 0), difr(n + 2, n + 1), suml(n + 2, 0), sumr(n + 2, 0);
	for (int i = 1; i <= n + 1; ++i) {
		if (a[i] != a[i - 1]) difl[i] = i;
		else difl[i] = difl[i - 1];
		sumr[i] = sumr[i - 1] + a[i];
	}
	for (int i = n; i >= 0; --i) {
		if (a[i] != a[i + 1]) difr[i] = i;
		else difr[i] = difr[i + 1];
		suml[i] = suml[i + 1] + a[i];
	}
	// for (int i = 1; i <= n; ++i) cout << sumr[i] << ' ';
	// cout << '\n';
	vector<int> ansr(n + 2, 987654321);
	for (int i = 1; i < n; ++i) {
		ll ind = lower_bound(sumr.begin(), sumr.end(), sumr[i] + a[i] + 1) - sumr.begin();
		// cout << sumr[i] + a[i] + 1 << ' ' << ind << ' ' << difr[i] << '\n';
		if (ind == n + 2) continue;
		if (ind - i == 1) ansr[i] = 1;
		else {
			if (difr[i + 1] == n) continue;
			ansr[i] = max(ind, difr[i + 1]+1) - i;
		}
	}
	vector<int> ansl(n + 2, 987654321);
	for (int i = 2; i <= n; ++i) {
		ll ind = lower_bound(suml.rbegin(), suml.rend(), suml[i] + a[i] + 1) - suml.rbegin();
		if (ind == n + 2) continue;
		else {
			if (i - (n + 1 - ind) == 1) ansl[i] = 1;
			else {
				if (difl[i - 1] == 1) continue;
				ansl[i] = i - min(n + 1 - ind, difl[i - 1]-1);
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		int temp = min(ansl[i], ansr[i]);
		if (temp == 987654321) temp = -1;
		cout << temp << ' ';
	}
	cout << '\n';
	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}