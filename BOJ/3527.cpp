#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

const ld EPS = 1e-8;

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
	int sinPos() const { return s.y == e.y ? s.x <= e.x : s.y < e.y; } // angle in [0, pi)
	bool operator< (Line l) const { return sinPos() != l.sinPos() ? sinPos() > l.sinPos() : (e - s).cross(l.e - l.s) > 0; }
	Line operator+ (Point<T> p) const { return {s + p, e + p}; }
	Line operator- (Point<T> p) const { return {s - p, e - p}; }
	bool onSegment(Point<T> p) const { return abs(p.cross(s, e)) < EPS && (s - p).dot(e - p) < EPS; }
	Line normTrans(T x) const { return *this + (e - s).normal() * x; }
	pair<int, Point<ld>> lineInter(Line l) const {
		auto d = (e - s).cross(l.e - l.s);
		if (d == 0) return {-(s.cross(e, l.s) == 0), Point<ld>(0, 0)};
		auto p = l.s.cross(e, l.e), q = l.s.cross(l.e, s);
		Point<T> tmp = s * p + e * q;
		Point<ld> ntmp = Point<ld>((ld)tmp.x, (ld)tmp.y);
		// cout << (ntmp / (ld) d).x << ' ' << (ntmp / (ld) d).y << '\n';
		return {1, ntmp / (ld) d};
	}
};

// half plane intersection(convex)
template<class T>
vector<Point<ld>> hpi(vector<Line<T>> lines) {
	// intersection of a, b is not part of c's half plane
	auto bad = [&](Line<T>& a, Line<T>& b, Line<T>& c) {
		auto v = a.lineInter(b);
		if (v.first != 1) return false;
		Point<ld> ncs = Point<ld>((ld) c.s.x, (ld) c.s.y);
		Point<ld> nce = Point<ld>((ld) c.e.x, (ld) c.e.y);
		// cout << ncs.cross(nce, v.second) << '\n';
		return ncs.cross(nce, v.second) <= EPS;
	};
	sort(lines.begin(), lines.end());
	deque<Line<T>> dq;
	for (int i = 0; i < lines.size(); ++i) {
		while(dq.size() >= 2 && bad(dq[(int) dq.size() - 2], dq.back(), lines[i])) dq.pop_back();
		while(dq.size() >= 2 && bad(dq[0], dq[1], lines[i])) dq.pop_front();
		if (dq.size() < 2 || !bad(dq.back(), lines[i], dq[0])) dq.push_back(lines[i]);
	}
	vector<Point<ld>> ret;
	if (dq.size() >= 3) for (int i = 0; i < dq.size(); ++i) {
		int j = (i + 1) % dq.size();
		auto v = dq[i].lineInter(dq[j]);
		if (v.first == 1) ret.push_back(v.second);
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	vector<Point<ll>> pts(n);
	for (int i = 0; i < n; ++i) cin >> pts[i].x >> pts[i].y;
	reverse(pts.begin(), pts.end());
	int l = 0, r = n - 1, mid;
	while (l + 1 < r) {
		mid = (l + r) / 2;
		vector<Line<ll>> ls;
		for (int i = 0; i < n; ++i) {
			int j = (i + mid + 1) % n;
			ls.push_back({pts[i], pts[j]});
		}
		if (hpi(ls).size() <= 2) r = mid;
		else l = mid;
	}
	cout << r << '\n';
}