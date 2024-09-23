#include <bits/stdc++.h>
using namespace std;

long double a, b, vmax, f;
int r;
long double x[10000], y[10000];
long double s[10000], d[10000];
long double ans;

bool check(long double v) {
	long double fuel = 0.0;
	long double time = 0.0;
	for (int i = 0; i < r; ++i) {
		long double vi = v;
		if (a * v + b * s[i] < 0) {
			vi = min(vmax, -b * s[i] / a);
		}
		long double c = max((long double)0.0, a * vi + b * s[i]);
		time += d[i] / vi;
		fuel += c * d[i];
	}
	if (fuel < f + 1e-15) {
		ans = min(ans, time);
		return true;
	} else return false;
}

void solve() {
	cin >> a >> b >> vmax >> f;
	cin >> r;
	ans = 25.0;
	for (int i = 0; i < r; ++i) {
		cin >> x[i] >> y[i];
	}
	for (int i = 0; i < r; ++i) {
		s[i] = y[i] / x[i];
		d[i] = sqrt(x[i] * x[i] + y[i] * y[i]) / 1000.0;
	}
	long double tmp = 0.0;
	for (int i = 0; i < r; ++i) {
		if (s[i] > 0.0) {
			tmp += b * s[i] * d[i];
		}
	}
	if (tmp > f + 1e-15) {
		cout << "IMPOSSIBLE\n";
		return;
	}
	long double l = 0.0, r = vmax;
	for (int i = 0; i < 100; ++i) {
		long double mid = (l + r) / 2;
		if (check(mid)) l = mid;
		else r = mid;
	}
	cout << fixed;
	cout.precision(7);
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}