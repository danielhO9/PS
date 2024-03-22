#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll cross(const pair<ll, ll>& a, const pair<ll, ll>& b) { return a.first * b.second - a.second * b.first; }
ll ccw(const pair<ll, ll>& a, const pair<ll, ll>& b, const pair<ll, ll>& c) {
	pair<ll, ll> a_b = {b.first - a.first, b.second - a.second};
	pair<ll, ll> b_c = {c.first - b.first, c.second - b.second};
	return cross(a_b, b_c);
}

bool isMeet(const pair<ll, ll>& a1, const pair<ll, ll>& a2, const pair<ll, ll>& b1, const pair<ll, ll>& b2) {
	ll ab1 = ccw(a1, a2, b1); if (ab1 != 0) ab1 /= abs(ab1);
	ll ab2 = ccw(a1, a2, b2); if (ab2 != 0) ab2 /= abs(ab2);
	ll ba1 = ccw(b1, b2, a1); if (ba1 != 0) ba1 /= abs(ba1);
	ll ba2 = ccw(b1, b2, a2); if (ba2 != 0) ba2 /= abs(ba2);
	if (ab1 * ab2 == 0 && ba1 * ba2 == 0) return min(b1, b2) <= max(a1, a2) && min(a1, a2) <= max(b1, b2);
	return ab1 * ab2 <= 0 && ba1 * ba2 <= 0;
}

void solve() {
	ll x1, y1, x2, y2, x3, y3, x4, y4;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
	cout << isMeet({x1, y1}, {x2, y2}, {x3, y3}, {x4, y4});
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}