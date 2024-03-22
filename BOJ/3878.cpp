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

bool isMeet(const pair<ll, ll>& a, const pair<ll, ll>& b1, const pair<ll, ll>& b2) {
	ll val = ccw(b1, a, b2);
	return val == 0 && min(b1, b2) <= a && a <= max(b1, b2);
}

vector<pair<ll, ll>> getConvexHull(vector<pair<ll, ll>> points) {
	sort(points.begin(), points.end());
	pair<ll, ll> unit = points.front();
	for (auto& i: points) {
		i.first -= unit.first;
		i.second -= unit.second;
	}
	sort(next(points.begin()), points.end(), [](const pair<ll, ll>& a, const pair<ll, ll>& b) {
		if (cross(a, b) == 0) {
			if (a.first == b.first) return a.second < b.second;
			return a.first < b.first;
		}
		return cross(a, b) > 0;
	});
	vector<pair<ll, ll>> convex;
	convex.push_back(points[0]); convex.push_back(points[1]);
	for (int i = 2; i < points.size(); ++i) {
		while (convex.size() >= 2) {
			pair<ll, ll> b = convex.back(); convex.pop_back();
			pair<ll, ll> a = convex.back();
			if (ccw(a, b, points[i]) > 0) {
				convex.push_back(b);
				break;
			}
		}
		convex.push_back(points[i]);
	}
	for (auto& i: convex) {
		i.first += unit.first;
		i.second += unit.second;
	}
	return convex;
}

void solve() {
	int n, m; cin >> n >> m;
	vector<pair<ll, ll>> points[2];
	for (int i = 0; i < n; ++i) {
		int x, y; cin >> x >> y;
		points[0].push_back({x, y});
	}
	for (int i = 0; i < m; ++i) {
		int x, y; cin >> x >> y;
		points[1].push_back({x, y});
	}

	vector<pair<ll, ll>> convexHull[2];
	if (n == 0 || m == 0) { cout << "YES\n"; return; }
	if (n == 1) convexHull[0].push_back(points[0][0]);
	else convexHull[0] = getConvexHull(points[0]);
	if (m == 1) convexHull[1].push_back(points[1][0]);
	else convexHull[1] = getConvexHull(points[1]);

	if (convexHull[1].size() >= 3) {
		for (int i = 0; i < n; ++i) {
			bool flag = true;
			for (int j = 0; j < convexHull[1].size(); ++j) {
				int nxt = (j + 1 == convexHull[1].size() ? 0 : j + 1);
				if (ccw(convexHull[1][j], convexHull[1][nxt], points[0][i]) < 0) {
					flag = false; break;
				}
			}
			if (flag) {
				cout << "NO\n"; return;
			}
		}
	}
	if (convexHull[0].size() >= 3) {
		for (int i = 0; i < m; ++i) {
			bool flag = true;
			for (int j = 0; j < convexHull[0].size(); ++j) {
				int nxt = (j + 1 == convexHull[0].size() ? 0 : j + 1);
				if (ccw(convexHull[0][j], convexHull[0][nxt], points[1][i]) < 0) {
					flag = false; break;
				}
			}
			if (flag) {
				cout << "NO\n"; return;
			}
		}
	}
	for (int i = 0; i < convexHull[0].size(); ++i) for (int j = 0; j < convexHull[1].size(); ++j) {
		int nxti = (i + 1 == convexHull[0].size() ? 0 : i + 1);
		int nxtj = (j + 1 == convexHull[1].size() ? 0 : j + 1);
		if (i == nxti && j == nxtj) {
			cout << "YES\n"; return;
		}
		if (i == nxti && isMeet(convexHull[0][i], convexHull[1][j], convexHull[1][nxtj])) {
			cout << "NO\n"; return;
		}
		if (j == nxtj && isMeet(convexHull[1][j], convexHull[0][i], convexHull[0][nxti])) {
			cout << "NO\n"; return;
		}
		if (isMeet(convexHull[0][i], convexHull[0][nxti], convexHull[1][j], convexHull[1][nxtj])) {
			cout << "NO\n"; return;
		}
	}
	cout << "YES\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}