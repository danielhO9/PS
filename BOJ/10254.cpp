#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<ll, ll> vec(pair<ll, ll> a, pair<ll, ll> b) { return {b.first - a.first, b.second - a.second}; }
ll cross(const pair<ll, ll>& a, const pair<ll, ll>& b) { return a.first * b.second - a.second * b.first; }
ll ccw(const pair<ll, ll>& a, const pair<ll, ll>& b, const pair<ll, ll>& c) {
	pair<ll, ll> a_b = vec(a, b), b_c = vec(b, c);
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

void solve() {
	int n; cin >> n;
	vector<pair<ll, ll>> cities;
	for (int i = 0; i < n; ++i) {
		ll x, y; cin >> x >> y;
		cities.push_back({x, y});
	}
	vector<pair<ll, ll>> convex = getConvexHull(cities);
	int a = 0, b = 1;
	pair<int, int> ans; ll dis = 0;
	while (true) {
		if (dis < (convex[a].first - convex[b].first) * (convex[a].first - convex[b].first) + (convex[a].second - convex[b].second) * (convex[a].second - convex[b].second)) {
			dis = (convex[a].first - convex[b].first) * (convex[a].first - convex[b].first) + (convex[a].second - convex[b].second) * (convex[a].second - convex[b].second);
			ans.first = a, ans.second = b;
		}
		if (cross(vec(convex[a], convex[a + 1]), vec(convex[b], convex[b + 1])) > 0) {
			++b; b %= convex.size();
		} else {
			++a; a %= convex.size();
			if (a == 0) break;
		}
	}
	cout << convex[ans.first].first << ' ' << convex[ans.first].second << ' ' << convex[ans.second].first << ' ' << convex[ans.second].second << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}