#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

const ld EPS = 1e-9;

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

template<class T>
struct Circle {
	Point<T> c; T r;
	bool inCircle(Point<T> p) const { return (p - c).dist() < r * (1 + EPS); }
};

// circumcircle center
template<class T>
Circle<T> ccCenter(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
	Point<T> nb = c - a, nc = b - a;
	Point<T> na = a;
	Point<T> center = na + (nb * nc.dist2() - nc * nb.dist2()).perp() / nb.cross(nc) / 2;
	T r = (b - a).dist() * (c - b).dist() * (a - c).dist() / (double) abs((b - a).cross(c - a)) / 2.0;
	return {center, r};
}

// minimum enclosing center
template<class T>
Circle<T> mec(vector<Point<T>> pts) {
	shuffle(pts.begin(), pts.end(), mt19937(time(0)));
	Circle<T> c = {pts[0], 0};
	for (int i = 0; i < pts.size(); ++i) if (!c.inCircle(pts[i])) {
		c = {pts[i], 0};
		for (int j = 0; j < i; ++j) if (!c.inCircle(pts[j])) {
			c.c = (pts[i] + pts[j]) / 2;
			c.r = (c.c - pts[i]).dist();
			for (int k = 0; k < j; ++k) if (!c.inCircle(pts[k])) {
				c = ccCenter(pts[i], pts[j], pts[k]);
			}
		}
	}
	return c;
}