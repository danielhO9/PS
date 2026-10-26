#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;
double k, l;
double a[200000];

void solve() {
	cin >> n >> k >> l;
	for (int i = 0; i < n; ++i) cin >> a[i];
	double pos = 0.0;
	double tm = 0;
	tm = a[0];
	a[0] = 0.0;
	pos = k;
	if (pos >= l - 0.01) {
		int ans = tm * 2;
		for (int i = ans - 1; i <= ans + 1; ++i) if (abs(ans - tm * 2) < 0.01) {
			cout << ans << '\n';
			break;
		}
		return;
	}
	for (int i = 1; i < n; ++i) {
		if (pos >= l - 0.01) {
			int ans = tm * 2;
			for (int i = ans - 1; i <= ans + 1; ++i) if (abs(ans - tm * 2) < 0.01) {
				cout << ans << '\n';
				break;
			}
			return;
		}
		double mx = a[i] + tm;
		double mn = a[i] - tm;
		if (mn - 0.01 <= pos && pos <= mx + 0.01) {
			a[i] = pos;
			pos += k;
			continue;
		}else if (pos < mn - 0.01) {
			double rem = mn - pos;
			double ttm = rem / 2.0;
			tm += ttm;
			pos += ttm + k;
			a[i] = pos - k;
		} else {
			pos = mx + k;
			a[i] = mx;
		}
		if (pos >= l - 0.01) {
			int ans = tm * 2;
			for (int i = ans - 1; i <= ans + 1; ++i) if (abs(ans - tm * 2) < 0.01) {
				cout << ans << '\n';
				break;
			}
			return;
		}
	}
	if (pos >= l - 0.01) {
		int ans = tm * 2;
		for (int i = ans - 1; i <= ans + 1; ++i) if (abs(ans - tm * 2) < 0.01) {
			cout << ans << '\n';
			break;
		}
		return;
	}

	tm += l - pos;
	int ans = tm * 2;
	for (int i = ans - 1; i <= ans + 1; ++i) if (abs(ans - tm * 2) < 0.01) {
		cout << ans << '\n';
		break;
	}
	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}