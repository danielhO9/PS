#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

struct Point {
	LL x, y;
	int index;
};

bool comp1 (const Point& a, const Point& b) {
	if (a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

LL cross(Point a, Point b) { return a.x * b.y - b.x * a.y; }

bool comp2 (const Point& a, const Point& b) {
	if (cross(a, b) == 0) {
		if (a.x == b.x) return a.y < b.y;
		return a.x < b.x;
	}
	return cross(a, b) > 0;
}

LL ccw(Point& a, Point& b, Point& c) {
	return cross({b.x - a.x, b.y - a.y}, {c.x - b.x, c.y - b.y});
}

double distance(Point& m, Point& n, Point& x) {
	if (m.x == n.x) return (double) abs(m.x - x.x);
	double a = (n.y - m.y) / (double) (n.x - m.x);
	double b = m.y - a * m.x;
	return abs(a * x.x - x.y + b) / sqrt(a * a + 1.0);
}

void solve(int cnt, int N) {
	vector<Point> v;
	LL x, y;
	for (int i = 0; i < N; ++i) {
		cin >> x >> y;
		v.push_back({x, y, i});
	}
	sort(v.begin(), v.end(), comp1);
	for (int i = 1; i < v.size(); ++i) {
		v[i].x -= v[0].x;
		v[i].y -= v[0].y;
	}
	v[0].x = 0; v[0].y = 0;
	sort(next(v.begin()), v.end(), comp2);
	stack<int> S; S.push(0); S.push(1);
	int s, m;
	for (int i = 2; i < v.size(); ++i) {
		while (S.size() >= 2) {
			m = S.top(); S.pop();
			s = S.top();
			if (ccw(v[s], v[m], v[i]) > 0) {
				S.push(m);
				break;
			}
		}
		S.push(i);
	}
	vector<int> hull;
	while (!S.empty()) {
		hull.push_back(S.top());
		S.pop();
	}
	double ans = 987654321.0;
	for (int i = 0; i < hull.size(); ++i) {
		double temp = 0.0;
		for (int j = 0; j < hull.size(); ++j) {
			temp = max(temp, distance(v[hull[i]], v[hull[i + 1 == hull.size() ? 0 : i + 1]], v[hull[j]]));
		}
		ans = min(ans, temp);
	}
	cout << "Case " << cnt << ": ";
	ans *= 100.0;
	ans = ceil(ans);
	ans /= 100.0;
	cout << fixed;
	cout.precision(2);
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int cnt = 0;
	while (true) {
		int t; cin >> t;
		if (t == 0) break;
		else solve(++cnt, t);
	}
}