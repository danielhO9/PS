#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll cross(const pair<ll, ll>& a, const pair<ll, ll>& b) { return a.first * b.second - a.second * b.first; }
ll ccw(const pair<ll, ll>& a, const pair<ll, ll>& b, const pair<ll, ll>& c) {
	pair<ll, ll> a_b = {b.first - a.first, b.second - a.second};
	pair<ll, ll> b_c = {c.first - b.first, c.second - b.second};
	return cross(a_b, b_c);
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
	int n;
	vector<pair<ll, ll>> points;
	vector<pair<ll, ll>> convexHull = getConvexHull(points);
}