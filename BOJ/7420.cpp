#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double PI = 3.1415926535;

ll cross(const pair<ll, ll>& a, const pair<ll, ll>& b) { return a.first * b.second - a.second * b.first; }
ll ccw(const pair<ll, ll>& a, const pair<ll, ll>& b, const pair<ll, ll>& c) {
	pair<ll, ll> a_b = {b.first - a.first, b.second - a.second};
	pair<ll, ll> b_c = {c.first - b.first, c.second - b.second};
	return cross(a_b, b_c);
}

vector<pair<ll, ll>> getConvexHull(vector<pair<ll, ll>>& cities) {
	sort(cities.begin(), cities.end());
	pair<ll, ll> unit = cities.front();
	for (auto& i: cities) {
		i.first -= unit.first;
		i.second -= unit.second;
	}
	sort(next(cities.begin()), cities.end(), [](const pair<ll, ll>& a, const pair<ll, ll>& b) {
		if (cross(a, b) == 0) {
			if (a.first == b.first) return a.second < b.second;
			return a.first < b.first;
		}
		return cross(a, b) > 0;
	});
	vector<pair<ll, ll>> convex;
	convex.push_back(cities[0]); convex.push_back(cities[1]);
	for (int i = 2; i < cities.size(); ++i) {
		while (convex.size() >= 2) {
			pair<ll, ll> b = convex.back(); convex.pop_back();
			pair<ll, ll> a = convex.back();
			if (ccw(a, b, cities[i]) > 0) {
				convex.push_back(b);
				break;
			}
		}
		convex.push_back(cities[i]);
	}
	for (auto& i: convex) {
		i.first += unit.first;
		i.second += unit.second;
	}
	return convex;
}

double dis(vector<pair<ll, ll>>& arr, int i, int j) {
	return sqrt((arr[i].first - arr[j].first) * (arr[i].first - arr[j].first) + (arr[i].second - arr[j].second) * (arr[i].second - arr[j].second));
}

void solve() {
	int n, l; cin >> n >> l;
	vector<pair<ll, ll>> cities;
	for (int i = 0; i < n; ++i) {
		ll x, y; cin >> x >> y;
		cities.push_back({x, y});
	}
	vector<pair<ll, ll>> convexHull = getConvexHull(cities);
	double ans = 0;
	for (int i = 0; i < int(convexHull.size()) - 1; ++i) {
		ans += dis(convexHull, i, i + 1);
	}
	ans += dis(convexHull, 0, int(convexHull.size()) - 1);
	ans += 2 * PI * l;
	cout << ll(round(ans));
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}