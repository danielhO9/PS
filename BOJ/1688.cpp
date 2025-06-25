#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const double EPS = 1e-9;

template<typename T>
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
struct Line {
	Point<T> s, e;
	explicit Line(Point<T> s = Point<T>(0, 0), Point<T> e = Point<T>(0, 0)) : s(s), e(e) {}
	bool operator< (Line l) const {
		auto sinPos = [&](Line l) { return l.s.y == l.e.y ? l.s.x <= l.e.x : l.s.y <= l.e.y; }; // angle in [0, pi)
		return sinPos(*this) != sinPos(l) ? sinPos(*this) > sinPos(l) : (e - s).cross(l.e - l.s) >= 0;
	}
	// only direction, not segment
	bool operator== (Line l) const {
		auto sinPos = [&](Line l) { return l.s.y == l.e.y ? l.s.x <= l.e.x : l.s.y <= l.e.y; }; // angle in [0, pi)
		return sinPos(*this) == sinPos(l) && (e - s).cross(l.e - l.s) == 0;
	}
	Line operator+ (Point<T> p) const { return {s + p, e + p}; }
	Line operator- (Point<T> p) const { return {s - p, e - p}; }
	bool onSegment(Point<ll> p) const { return abs(p.cross(s, e)) == 0 && (s - p).dot(e - p) <= 0; }
	bool onSegment(Point<double> p) const { return abs(p.cross(s, e)) < EPS && (s - p).dot(e - p) <= EPS; }
	Line normTrans(T x) const { return *this + (e - s).normal() * x; }
	double lineDist(Point<T> p) const { return (double)(e - s).cross(p - s) / (e - s).dist(); }
	double segDist(Point<T> p) const {
		if (s == e) return (p - s).dist();
		double d = (e - s).dist2(), t = min(d, max(0.0, (double) (p - s).dot(e - s)));
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
    int N; cin >> N;
    vector<Point<ll>> pts(N);
    for (int i = 0; i < N; ++i) cin >> pts[i].x >> pts[i].y;
    vector<Line<ll>> lines;
    for (int i = 0; i < N; ++i) lines.push_back(Line<ll>(pts[i], pts[(i + 1) % N]));
    for (int i = 0; i < 3; ++i) {
        Point<ll> pt; cin >> pt.x >> pt.y;
        Line<ll> line {pt, Point<ll> {pt.x + 1000000000, pt.y + 1}};
        bool flag = false;
        for (auto j: lines) {
            if (j.onSegment(pt)) {
                cout << 1 << '\n';
                flag = true;
                break;
            }
        }
        if (flag) continue;
        int cnt = 0;
        for (auto j: lines) {
            auto tmp = j.segInter(line).first;
            cnt += tmp;
        }
        if (cnt % 2) cout << "1\n";
        else cout << 0 << '\n';

    }
}