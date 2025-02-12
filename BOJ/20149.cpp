#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double ld;

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
	ld dist() const { return sqrt((ld)dist2()); }
	ld angle() const { return atan2(y, x); } // angle to x−axis in interval [−pi, pi]
	Point unit() const { return *this / dist(); } // makes dist() = 1
	Point perp() const { return Point(-y, x); } // rotates +90 degrees
	Point normal() const { return perp().unit(); }
	// returns point rotated ’a’ radians ccw around the origin
	Point rotate(ld a) const { return Point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
};

template<class T>
struct Line {
	Point<T> s, e;
	explicit Line(Point<T> s = Point<T>(0, 0), Point<T> e = Point<T>(0, 0)) : s(s), e(e) {}
	bool operator< (Line l) const {
		auto sinPos = [&](Line l) { return l.s.y == l.e.y ? l.s.x <= l.e.x : l.s.y <= l.e.y; }; // angle in [0, pi)
		return sinPos(*this) != sinPos(l) ? sinPos(*this) > sinPos(l) : (e - s).cross(l.e - l.s) >= 0;
	}
	// only direction, not setment
	bool operator== (Line l) const {
		auto sinPos = [&](Line l) { return l.s.y == l.e.y ? l.s.x <= l.e.x : l.s.y <= l.e.y; }; // angle in [0, pi)
		return sinPos(*this) == sinPos(l) && (e - s).cross(l.e - l.s) == 0;
	}
	Line operator+ (Point<T> p) const { return {s + p, e + p}; }
	Line operator- (Point<T> p) const { return {s - p, e - p}; }
	bool onSegment(Point<ll> p) const { return abs(p.cross(s, e)) == 0 && (s - p).dot(e - p) <= 0; }
	bool onSegment(Point<ld> p) const { return abs(p.cross(s, e)) < EPS && (s - p).dot(e - p) <= EPS; }
	Line normTrans(T x) const { return *this + (e - s).normal() * x; }
	ld lineDist(Point<T> p) const { return (ld)(e - s).cross(p - s) / (e - s).dist(); }
	ld segDist(Point<T> p) const {
		if (s == e) return (p - s).dist();
		ld d = (e - s).dist2(), t = min(d, max((ld) 0.0, (ld) (p - s).dot(e - s)));
		return ((p - s) * d - (e - s) * t).dist() / d;
	}
	pair<int, Point<T>> lineInter(Line l) const {
		auto d = (e - s).cross(l.e - l.s);
		if (d == 0) return {-(s.cross(e, l.s) == 0), Point<T>(0, 0)};
		auto p = l.s.cross(e, l.e), q = l.s.cross(l.e, s);
		return {1, (s * p + e * q) / d};
	}
	pair<int, Point<T>> segInter(Line l) const {
		auto sgn = [&](T x) { return (x > 0) - (x < 0); };
		auto oa = l.s.cross(l.e, s), ob = l.s.cross(l.e, e),
		oc = s.cross(e, l.s), od = s.cross(e, l.e);
		// Checks if intersection is single non−endpoint point.
		if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
			return {1, (s * ob - e * oa) / (ob - oa)};
		set<Point<T>> spts;
		if (l.onSegment(s)) spts.insert(s);
		if (l.onSegment(e)) spts.insert(e);
		if (onSegment(l.s)) spts.insert(l.s);
		if (onSegment(l.e)) spts.insert(l.e);
		if (spts.size() == 1) return {1, *spts.begin()};
		if (spts.size() == 0) return {0, Point<T>(0, 0)};
		return {-1, Point<T>(0, 0)};
	}
};

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	Line<ld> lines[2];
	for (int i = 0; i < 2; ++i) cin >> lines[i].s.x >> lines[i].s.y >> lines[i].e.x >> lines[i].e.y;
	auto res = lines[0].segInter(lines[1]);
	cout << abs(res.first) << '\n';
	cout.precision(10);
	cout << fixed;
	if (res.first == 1) cout << res.second.x << ' ' << res.second.y << "\n";
}