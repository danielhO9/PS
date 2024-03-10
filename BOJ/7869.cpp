#include <bits/stdc++.h>
using namespace std;

const double PI = 3.141592653589793238;

void solve() {
	double x1, y1, r1, x2, y2, r2;
	cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
	double d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	if (d >= r1 + r2) {
		cout << fixed; cout.precision(3);
		cout << 0.000; return;
	}
	if (d <= max(r1, r2) - min(r1, r2)) {
		cout << fixed; cout.precision(3);
		cout << PI * min(r1, r2) * min(r1, r2); return;
	}
	double coslhalf = (r1 * r1 + d * d - r2 * r2) / (2.0 * r1 * d);
	double cosrhalf = (r2 * r2 + d * d - r1 * r1) / (2.0 * r2 * d);
	double l = acos(coslhalf), r = acos(cosrhalf);
	double theta1 = l * 2.0, theta2 = r * 2.0;
	double s1 = 0.5 * r1 * r1 * theta1;
	s1 -= 0.5 * r1 * r1 * sin(theta1);
	double s2 = 0.5 * r2 * r2 * theta2;
	s2 -= 0.5 * r2 * r2 * sin(theta2);
	cout << fixed; cout.precision(3);
	cout << s1 + s2;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}