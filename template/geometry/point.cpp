#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const double EPS = 1e-9;

template<typename T>
struct Point {
	T x, y;
	explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
	bool operator< (const Point& p) const { return tie(x, y) < tie(p.x, p.y); }
	bool operator== (const Point& p) const { return tie(x, y) == tie(p.x, p.y); }
	bool operator!= (const Point& p) const { return !(*this == p); }
	Point operator+ (const Point& p) const { return Point(x + p.x, y + p.y); }
	Point operator- (const Point& p) const { return Point(x - p.x, y - p.y); }
	Point operator* (T d) const { return Point(x * d, y * d); }
	Point operator/(T d) const { return Point(x / d, y / d); }
	friend istream& operator>> (istream& in, Point<T>& p) { in >> p.x >> p.y; return in; }
	friend ostream& operator<< (ostream& out, Point<T>& p) { out << p.x << ' ' << p.y; return out; }
	T dot(const Point& p) const { return x * p.x + y * p.y; }
	T cross(const Point& p) const { return x * p.y - y * p.x; }
	T cross(const Point& a, const Point& b) const { return (a - *this).cross(b - *this); }
	T dist2() const { return x * x + y * y; }
	double dist() const { return sqrt((double)dist2()); }
	double angle() const { return atan2(y, x); } // angle to x−axis in interval [−pi, pi]
	Point unit() const { return *this / dist(); } // makes dist() = 1
	Point perp() const { return Point(-y, x); } // rotates +90 degrees
	Point normal() const { return perp().unit(); }
	// returns point rotated ’a’ radians ccw around the origin
	Point rotate(double a) const { return Point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
};

template<typename T>
struct Line {
	Point<T> s, e;
	explicit Line(Point<T> s = Point<T>(0, 0), Point<T> e = Point<T>(1, 0)) : s(s), e(e) { assert(s != e); }
	bool sinPos() const { return s.y == e.y ? s.x <= e.x : s.y <= e.y; } // angle in [0, pi)
	bool operator< (const Line<T>& l) const {
		return sinPos() != l.sinPos() ? sinPos() > l.sinPos() : (e - s).cross(l.e - l.s) >= 0;
	}
	// only direction, not segment
	bool operator== (const Line<T>& l) const { sinPos() == l.sinPos() && (e - s).cross(l.e - l.s) == 0; }
	Line operator+ (const Point<T>& p) const { return Line(s + p, e + p); }
	Line operator- (const Point<T>& p) const { return Line(s - p, e - p); }
	bool onSegment(const Point<ll>& p) const { return abs(p.cross(s, e)) == 0 && (s - p).dot(e - p) <= 0; }
	bool onSegment(const Point<double>& p) const { return abs(p.cross(s, e)) < EPS && (s - p).dot(e - p) < EPS; }
	double lineDist(const Point<T>& p) const { return (double)(e - s).cross(p - s) / (e - s).dist(); }
	double segDist(const Point<T>& p) const {
		double d = (e - s).dist2(), t = min(d, max(0.0, (double) (p - s).dot(e - s)));
		return ((p - s) * d - (e - s) * t).dist() / d;
	}
	pair<int, Point<T>> lineInter(const Line& l) const {
		auto d = (e - s).cross(l.e - l.s);
		if (d == 0) return {-(s.cross(e, l.s) == 0), Point<T>(0, 0)};
		auto p = l.s.cross(e, l.e), q = l.s.cross(l.e, s);
		return {1, (s * p + e * q) / d};
	}
	pair<int, Point<T>> segInter(const Line& l) const {
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

template<typename T>
T polygonArea2(const vector<Point<T>>& pts) {
	assert(!pts.empty());
	T ret = pts.back().cross(pts[0]);
	for (int i = 0; i + 1 < pts.size(); ++i) ret += pts[i].cross(pts[i + 1]);
	return abs(ret);
}

// time complexity: logN
template <typename T>
bool inConvex(const Point<T>& p, const vector<Point<T>>& pts) {
    assert(pts.size() >= 3);
    if (pts[0].cross(pts[1], p) < 0 || pts[0].cross(pts.back(), p) > 0) return false;
    int l = 0, r = pts.size(), mid; --r;
    while (l + 1 < r) {
        mid = (l + r) / 2;
        if (pts[0].cross(p, pts[mid]) >= 0) r = mid;
        else l = mid;
    }
    return pts[r - 1].cross(pts[r], p) > 0;
}

// time complexity: N
template <typename T>
bool inConcave(const Point<T>& pt, const vector<Point<T>>& pts) {
	vector<Line<ll>> lines;
	const int n = pts.size();
    for (int i = 0; i < n; ++i) lines.push_back(Line<ll>(pts[i], pts[(i + 1) % n]));
	Line<ll> line {pt, Point<ll> {pt.x + 1000000000ll, pt.y + 1}}; // non parallel
	for (auto j: lines) if (j.onSegment(pt)) return true;
	int cnt = 0;
	for (auto j: lines) {
		auto tmp = j.segInter(line).first;
		cnt += tmp;
	}
	if (cnt % 2) return true;
	else return false;
}

template<typename P>
vector<P> convexHull(vector<P> pts) {
	if (pts.size() <= 1) return pts;
	sort(pts.begin(), pts.end());
	P unit = pts[0];
	for (auto& i: pts) i = i - unit;
	sort(next(pts.begin()), pts.end(), [](const P& a, const P& b) {
		if (a.cross(b) == 0) {
			if (a.x == b.x) return a.y < b.y;
			return a.x < b.x;
		}
		return a.cross(b) > 0;
	});
	vector<P> h;
	h.push_back(pts[0]); h.push_back(pts[1]);
	for (int i = 2; i < pts.size(); ++i) {
		while (h.size() >= 2) {
			P b = h.back(); h.pop_back();
			P a = h.back();
			if (a.cross(b, pts[i]) > 0) {
				h.push_back(b);
				break;
			}
		}
		h.push_back(pts[i]);
	}
	for (auto& i: h) i = i + unit;
	return h;
}

// rotating calipers(convex)
template<typename T>
pair<Point<T>, Point<T>> hullDiameter(vector<Point<T>>& pts) {
	int n = pts.size();
	if (n == 0) return {Point<T>(0, 0), Point<T>(0, 0)};
	if (n == 1) return {pts[0], pts[0]};
	pair<T, pair<Point<T>, Point<T>>> res({0, {pts[0], pts[0]}});
	int j = 1;
	for (int i = 0; i < j; ++i) {
		while (true) {
			res = max(res, {(pts[i] - pts[j]).dist2(), {pts[i], pts[j]}});
			if ((pts[(j + 1) % n] - pts[j]).cross(pts[i + 1] - pts[i]) >= 0) break;
			j = (j + 1) % n;
		}
	}
	return res.second;
}

// half plane intersection(convex)
template<typename T>
vector<Point<T>> hpi(vector<Line<T>> lines) {
	// intersection of a, b is not part of c's half plane
	auto bad = [&](Line<T>& a, Line<T>& b, Line<T>& c) {
		auto v = a.lineInter(b);
		if (v.first != 1) return false;
		return c.s.cross(c.e, v.second) <= EPS;
	};
	sort(lines.begin(), lines.end());
	deque<Line<T>> dq;
	for (int i = 0; i < lines.size(); ++i) {
		while(dq.size() >= 2 && bad(dq[(int) dq.size() - 2], dq.back(), lines[i])) dq.pop_back();
		while(dq.size() >= 2 && bad(dq[0], dq[1], lines[i])) dq.pop_front();
		if (dq.size() < 2 || !bad(dq.back(), lines[i], dq[0])) dq.push_back(lines[i]);
	}
	vector<Point<T>> ret;
	if (dq.size() >= 3) for (int i = 0; i < dq.size(); ++i) {
		int j = (i + 1) % dq.size();
		auto v = dq[i].lineInter(dq[j]);
		if (v.first == 1) ret.push_back(v.second);
	}
	return ret;
}