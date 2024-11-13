#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
	ll x, y;
	Point operator-(Point p) const { return {x - p.x, y - p.y}; }
	Point operator*(ll d) const { return {x * d, y * d}; }
	bool operator==(Point p) const { return tie(x,y) == tie(p.x,p.y); }
	bool operator!=(Point p) const { return tie(x,y) != tie(p.x,p.y); }
	bool operator<(Point p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator<=(Point p) const { return tie(x,y) <= tie(p.x,p.y); }
	ll dot(Point p) const {return x*p.x + y*p.y; }
	ll cross(Point p) const { return x*p.y - y*p.x; }
};

ll cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }

ll ccw(const Point& a, const Point& b, const Point& c) {
	Point a_b = {b.x - a.x, b.y - a.y};
	Point b_c = {c.x - b.x, c.y - b.y};
	return cross(a_b, b_c);
}

vector<Point> getConvexHull(vector<Point> points) {
	if (points.size() <= 2) return points;
	sort(points.begin(), points.end());
	Point unit = points.front();
	for (auto& i: points) {
		i.x -= unit.x;
		i.y -= unit.y;
	}
	
	sort(next(points.begin()), points.end(), [](const Point& a, const Point& b) {
		if (cross(a, b) == 0) {
			if (a.x == b.x) return a.y < b.y;
			return a.x < b.x;
		}
		return cross(a, b) > 0;
	});
	vector<Point> convex;
	convex.push_back(points[0]); convex.push_back(points[1]);
	for (int i = 2; i < points.size(); ++i) {
		while (convex.size() >= 2) {
			Point b = convex.back(); convex.pop_back();
			Point a = convex.back();
			if (ccw(a, b, points[i]) >= 0) {
				convex.push_back(b);
				break;
			}
		}
		convex.push_back(points[i]);
	}
	
	auto e = convex.back();

	if (cross(convex[1], e) != 0) {
		for (int i = 0; i < points.size(); ++i) {
			if (cross(points[i], e) == 0 && points[i] != convex.front() && points[i] != e) convex.push_back(points[i]);
		}
	}

	for (auto& i: convex) {
		i.x += unit.x;
		i.y += unit.y;
	}
	return convex;
}

ll polygonArea2(vector<Point> v) {
	ll a = v.back().cross(v[0]);
	for (int i = 0; i < v.size() - 1; i++)
		a += v[i].cross(v[i+1]);
	return a;
}

int n, m;

void solve() {
	cin >> n >> m;
	vector<Point> points[3];
	int ccnt[3] = {0, 0, 0};
	for (int i = 0; i < n; ++i) {
		string tmp; cin >> tmp;
		for (int j = 0; j < m; ++j) {
			if (tmp[j] == 'R') points[0].push_back({i, j}), ++ccnt[0];
			else if (tmp[j] == 'G') points[1].push_back({i, j}), ++ccnt[1];
			else points[2].push_back({i, j}), ++ccnt[2];
		}
	}
	for (int i = 0; i < 3; ++i) points[i] = getConvexHull(points[i]);

	// for (int i = 0; i < 3; ++i) cout << points[i].size() << ' ';
	// cout << '\n';

	vector<set<int>> avail[3];
	// 0, 1, 2 / 0, 2, 1 / 1, 2, 0
	int cnt = 0;
	for (int i = 0; i < 3; ++i) for (int j = i + 1; j < 3; ++j) {
		int k = 3 - i - j;
		avail[k].resize(points[i].size() * points[j].size());
		for (int a = 0; a < points[i].size(); ++a) for (int b = 0; b < points[j].size(); ++b) {
			int idx = a * points[j].size() + b;
			ll maxd = 0.0;
			for (int c = 0; c < points[k].size(); ++c) {
				ll dis = abs(polygonArea2({points[i][a], points[j][b], points[k][c]}));
				if (dis == maxd) avail[k][idx].insert(c);
				else if (dis > maxd) {
					avail[k][idx].clear();
					avail[k][idx].insert(c);
					maxd = dis;
				}
			}
			if (k == 0) {
				for (auto c: avail[k][idx]) {
					int nidx = c * points[i].size() + a;
					if (avail[2][nidx].find(b) == avail[2][nidx].end()) continue;
					nidx = c * points[j].size() + b;
					if (avail[1][nidx].find(a) == avail[1][nidx].end()) continue;
					++cnt;
				}
			}
		}
	}
	cout << ccnt[0] * ccnt[1] * ccnt[2] - cnt << '\n';
	// vector<Point> pts;
	// pts.push_back({0, 0});
	// pts.push_back({1, 1});
	// pts.push_back({2, 2});
	// pts = getConvexHull(pts);
	// cout << pts.size() << ' ';
	// for (auto i: pts) {
	// 	cout << i.x << ' ' << i.y << '\n';
	// }
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}