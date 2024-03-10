#include <bits/stdc++.h>
using namespace std;

void solve() {
	double X, Y, D, T; cin >> X >> Y >> D >> T;
	double dis = sqrt(X * X + Y * Y);
	if (D <= T) {
		cout << fixed;
		cout.precision(10);
		cout << dis;
		return;
	}
	double ans = 987654321.0;
	double temp = 0.0;
	while (dis > 0) {
		ans = min(ans, temp + min(dis, ceil(dis / (2.0 * D)) * 2.0 * T));
		dis -= D; temp += T;
	}
	dis = abs(dis);
	ans = min(ans, temp + min(dis, 2.0 * T));
	cout << fixed;
	cout.precision(10);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}