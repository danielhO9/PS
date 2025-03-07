#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

template<class T>
struct Point {
	T x, y;
	explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
	bool operator< (Point p) const { return tie(x, y) < tie(p.x, p.y); }
	bool operator== (Point p) const { return tie(x, y) == tie(p.x, p.y); }
	Point operator+ (Point p) const { return Point(x + p.x, y + p.y); }
	Point operator- (Point p) const { return Point(x - p.x, y - p.y); }
	Point operator* (T d) const { return Point(x * d, y * d); }
	Point operator/(T d) const { return Point(x / d, y / d); }
	T dot(Point p) const { return x * p.x + y * p.y; }
	T cross(Point p) const { return x * p.y - y * p.x; }
	T cross(Point a, Point b) const { return (a - *this).cross(b - *this); }
	T dist2() const { return x * x + y * y; }
	double dist() const { return sqrt((double)dist2()); }
	double angle() const { return atan2(y, x); } // angle to x−axis in interval [−pi, pi]
	Point unit() const { return *this / dist(); } // makes dist() = 1
	Point perp() const { return Point(-y, x); } // rotates +90 degrees
	Point normal() const { return perp().unit(); }
	// returns point rotated ’a’ radians ccw around the origin
	Point rotate(double a) const { return Point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
};

int n;
double d;
Point<double> pts[2000];
bool pos[2000][2000];

int cache[2000];

void solve() {
	cin >> n >> d;
	for (int i = 0; i < n; ++i) cin >> pts[i].x >> pts[i].y;

	for (int i = 0; i < n; ++i) {
		Point<double> a = pts[i];
		bool flag = true;
		Point<double> s;
		Point<double> e;
		for (int j = i + 1; j < n; ++j) {
			Point<double> b = pts[j];
			Point<double> p = b - a;

			if (flag) pos[i][j] = true;
			else if (s.cross(p) > -EPS && p.cross(e) > -EPS) pos[i][j] = true;

			if (p.dist() < d + EPS) continue;
			Point<double> ss = p.rotate(-asin(d / p.dist()));
			Point<double> ee = p.rotate(asin(d / p.dist()));
			
			if (flag) {
				s = ss, e = ee;
				flag = false;
				continue;
			}
			assert(ss.cross(ee) > -EPS);
			assert(s.cross(e) > -EPS);
			bool inter = false;
			if (s.cross(ss) > -EPS && ss.cross(e) > -EPS) s = ss, inter = true;
			if (s.cross(ee) > -EPS && ee.cross(e) > -EPS) e = ee, inter = true;
			if (!inter) if (ss.cross(s) < -EPS || s.cross(ee) < -EPS) break;
		}

	}

	for (int i = n - 1; i >= 0; --i) {
		Point<double> a = pts[i];
		bool flag = true;
		Point<double> s;
		Point<double> e;
		for (int j = i - 1; j >= 0; --j) {
			Point<double> b = pts[j];
			Point<double> p = b - a;

			if (flag) pos[i][j] = true;
			else if (s.cross(p) > -EPS && p.cross(e) > -EPS) pos[i][j] = true;

			if (p.dist() < d + EPS) continue;
			Point<double> ss = p.rotate(-asin(d / p.dist()));
			Point<double> ee = p.rotate(asin(d / p.dist()));
			
			if (flag) {
				s = ss, e = ee;
				flag = false;
				continue;
			}
			assert(ss.cross(ee) > -EPS);
			assert(s.cross(e) > -EPS);
			
			bool inter = false;
			if (s.cross(ss) > -EPS && ss.cross(e) > -EPS) s = ss, inter = true;
			if (s.cross(ee) > -EPS && ee.cross(e) > -EPS) e = ee, inter = true;
			if (!inter) if (ss.cross(s) < -EPS || s.cross(ee) < -EPS) break;
		}

	}
	// for (int i = 0; i < n; ++i) {
	// 	for (int j = 0; j < n; ++j) cout << pos[i][j] << ' ';
	// 	cout << '\n';
	// }
	for (int i = 0; i < n; ++i) cache[i] = n + 1;
	cache[n - 1] = 1;
	for (int i = n - 2; i >= 0; --i) {
		for (int j = i + 1; j < n; ++j) if (pos[i][j] && pos[j][i]) {
			cache[i] = min(cache[i], cache[j] + 1);
		}
	}
	cout << cache[0];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}