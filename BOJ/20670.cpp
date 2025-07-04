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

int N, M, K;
vector<Point<ll>> A, B;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M >> K;
    A.resize(N); B.resize(M);
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < M; ++i) cin >> B[i];
    int cnt = 0;
    for (int i = 0; i < K; ++i) {
        Point<ll> p; cin >> p;
        if (!inConvex(p, A) || inConvex(p, B)) {
            // cout << p << ' ' << inConvex(p, A) << ' ' << inConvex(p, B) << '\n';
            ++cnt;
        }
    }
    if (cnt) cout << cnt;
    else cout << "YES";
}