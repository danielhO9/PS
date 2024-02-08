#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL gcd(LL a, LL b) {
	if (a < b) swap(a, b);
	if (b == 0) return a;
	return gcd(a % b, b);
}

void solve() {
	LL n, k; cin >> n >> k;
	vector<LL> a(n);
	int type = -2;
	LL sum = 0;
	for (int i = 0; i < n; ++i) {
		cin >> a[i]; a[i] -= k;
		sum += a[i];
	}
	for (int i = 0; i < n; ++i) {
		if (a[i] > 0) {
			if (type != -2 && type != 1) {
				cout << "-1\n";
				return;
			}
			type = 1;
		}
		if (a[i] == 0) {
			if (type != -2 && type != 0) {
				cout << "-1\n";
				return;
			}
			type = 0;
		}
		if (a[i] < 0) {
			if (type != -2 && type != -1) {
				cout << "-1\n";
				return;
			}
			type = -1;
		}
	}
	if (type == 0) {
		cout << "0\n"; return;
	}
	LL g = abs(a[0]);
	for (int i = 0; i < n; ++i) g = gcd(g, abs(a[i]));
	if (type == -1) g *= -1;
	cout << sum / g - n << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}