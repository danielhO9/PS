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
	bool onSegment(Point<T> p) const { return abs(p.cross(s, e)) == 0 && (s - p).dot(e - p) <= 0; }
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
T polygonArea2(vector<Point<T>>& pts) {
	assert(!pts.empty());
	T ret = pts.back().cross(pts[0]);
	for (int i = 0; i + 1 < pts.size(); ++i) ret += pts[i].cross(pts[i + 1]);
	return abs(ret);
}

struct Nline {
	int i, j;
	Line<ll> l;
};

int n;
Point<ll> pts[2000];
int ord[2000];

void solve() {
	for (int i = 0; i < n; ++i) cin >> pts[i].x >> pts[i].y;
	for (int i = 0; i < n; ++i) ord[i] = i;
	sort(pts, pts + n, [](const Point<ll>& a, const Point<ll>& b) {
		if (a.y == b.y) return a.x < b.x;
		return a.y < b.y;
	});
	vector<Nline> lines;
	for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) lines.push_back({i, j, Line<ll>(pts[i], pts[j])});
	sort(lines.begin(), lines.end(), [](const Nline& a, const Nline& b) {
		if (a.l == b.l) return tie(a.i, a.j) < tie(b.i, b.j);
		return a.l < b.l;
	});
	ll mn = LLONG_MAX, mx = LLONG_MIN;
	int j = 0;
	for (int i = 0; i < lines.size(); i = j) {
		while (j < lines.size() && (lines[i].l.e - lines[i].l.s).cross(lines[j].l.e - lines[j].l.s) == 0) ++j;
		for (int k = i; k < j; ++k) {
			int u = lines[k].i, v = lines[k].j;
			swap(ord[u], ord[v]);
			swap(pts[ord[u]], pts[ord[v]]);
			if (ord[u] > ord[v]) swap(u, v);
			if (ord[u] - 1 >= 0) {
				vector<Point<ll>> tmp = {pts[ord[u]], pts[ord[v]], pts[ord[u] - 1]};
				mn = min(mn, polygonArea2(tmp));
				tmp = {pts[ord[u]], pts[ord[v]], pts[0]};
				mx = max(mx, polygonArea2(tmp));
			}
			if (ord[v] + 1 < n) {
				vector<Point<ll>> tmp = {pts[ord[u]], pts[ord[v]], pts[ord[v] + 1]};
				mn = min(mn, polygonArea2(tmp));
				tmp = {pts[ord[u]], pts[ord[v]], pts[n - 1]};
				mx = max(mx, polygonArea2(tmp));
			}
		}
	}
	cout << mn / 2 << '.' << mn % 2 * 5 << ' ';
	cout << mx / 2 << '.' << mx % 2 * 5 << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	while (true) {
		cin >> n;
		if (n == 0) break;
		solve();
	}
}