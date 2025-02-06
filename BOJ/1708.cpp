#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

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

template<class T>
struct Line {
	Point<T> s, e;
	bool sinPos() const { return s.y == e.y ? s.x <= e.x : s.y <= e.y; } // angle in [0, pi)
	bool operator< (Line l) const { return sinPos() != l.sinPos() ? sinPos() > l.sinPos() : (e - s).cross(l.e - l.s) >= 0; }
	Line operator+ (Point<T> p) const { return {s + p, e + p}; }
	Line operator- (Point<T> p) const { return {s - p, e - p}; }
	bool onSegment(Point<T> p) const { return abs(p.cross(s, e)) < EPS && (s - p).dot(e - p) < EPS; }
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

template<class T>
struct Circle {
	Point<T> c; T r;
};

template<class T>
T polygonArea2(vector<Point<T>>& v) {
	T a = v.back().cross(v[0]);
	for (int i = 0; i < v.size() - 1; ++i)
	a += v[i].cross(v[i + 1]);
	return abs(a);
}

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
	Point<T> o = pts[0];
	T r = 0;
	for (int i = 0; i < pts.size(); ++i) if ((o - pts[i]).dist() > r * (1.0 + EPS)) {
		o = pts[i], r = 0;
		for (int j = 0; j < i; ++j) if ((o - pts[j]).dist() > r * (1.0 + EPS)) {
			o = (pts[i] + pts[j]) / 2;
			r = (o - pts[i]).dist();
			for (int k = 0; k < j; ++k) if ((o - pts[k]).dist() > r * (1.0 + EPS)) {
				o = ccCenter(pts[i], pts[j], pts[k]);
				r = (o - pts[i]).dist();
			}
		}
	}
	return {o, r};
}

template<class P>
vector<P> convexHull(vector<P> pts) {
	if (pts.size() <= 1) return pts;
	sort(pts.begin(), pts.end());
	P unit = pts[0];
	for (auto& i: pts) i = i - unit;
	sort(next(pts.begin()), pts.end(), [](const P& a, P& b) {
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

// rotating calipers
template<class P>
pair<P, P> hullDiameter(vector<P> pts) {
	int n = pts.size();
	if (n == 0) return {P(0, 0), P(0, 0)};
	if (n == 1) return {pts[0], pts[0]};
	pair<ll, pair<P, P>> res({0, {pts[0], pts[0]}});
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

// half plane intersection
template<class T>
vector<Point<T>> hpi(vector<Line<T>> lines) {
	// intersection of a, b is not part of c's half plane
	auto bad = [&](Line<T>& a, Line<T>& b, Line<T>& c) {
		auto v = a.lineInter(b);
		if (v.first != 1) return false;
		return c.s.cross(c.e, v.second) < EPS;
	};
	sort(lines.begin(), lines.end());
	deque<Line<T>> dq;
	for (int i = 0; i < lines.size(); ++i) {
		while(dq.size() >= 2 && bad(dq[(int) dq.size() - 2], dq.back(), lines[i])) dq.pop_back();
		while(dq.size() >= 2 && bad(dq[0], dq[1], lines[i])) dq.pop_front();
		if (dq.size() < 2 || !bad(dq.back(), lines[i], dq[0])) dq.push_back(lines[i]);
	}
	vector<Point<T>> ret;
	if(dq.size() >= 3) for (int i=0; i < dq.size(); ++i) {
		int j = (i + 1) % dq.size();
		auto v = dq[i].lineInter(dq[j]);
		if (v.first == 1) ret.push_back(v.second);
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int N; cin >> N;
	vector<Point<ll>> pts(N);
	for (int i = 0; i < N; ++i) cin >> pts[i].x >> pts[i].y;
	cout << convexHull(pts).size();
}