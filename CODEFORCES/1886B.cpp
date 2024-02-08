#include <bits/stdc++.h>
using namespace std;

void solve() {
	int px, py, ax, ay, bx, by;
	cin >> px >> py >> ax >> ay >> bx >> by;
	int pa = (px - ax) * (px - ax) + (py - ay) * (py - ay);
	int pb = (px - bx) * (px - bx) + (py - by) * (py - by);
	int oa = ax * ax + ay * ay;
	int ob = bx * bx + by * by;
	int ab = (ax - bx) * (ax - bx) + (ay - by) * (ay - by);
	double ans = INT32_MAX;
	ans = min(ans, sqrt(max(pa, oa)));
	ans = min(ans, sqrt(max(pb, ob)));
	ans = min(ans, max(sqrt(max(oa, pb)), sqrt((double) ab / 4)));
	ans = min(ans, max(sqrt(max(ob, pa)), sqrt((double) ab / 4)));
	cout << fixed;
    cout.precision(7);
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}