#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

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
	double angle() const { return atan2(y, x); } // angle to x-axis in interval [-pi, pi]
	Point unit() const { return *this / dist(); } // makes dist() = 1
	Point perp() const { return Point(-y, x); } // rotates +90 degrees
	Point normal() const { return perp().unit(); }
	// returns point rotated a radians ccw around the origin
	Point rotate(double a) const { return Point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
};

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

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    vector<Point<ll>> pts(N);
    for (int i = 0; i < N; ++i) cin >> pts[i].x >> pts[i].y;
    auto hull = convexHull(pts);
    ll mn = LLONG_MAX, mx = LLONG_MIN;
    for (auto i: hull) {
        mn = min(mn, i.x);
        mx = max(mx, i.x);
    }
    int len = hull.size();
    for (int i = 0; i < len; ++i) hull.push_back(hull[i]);
    vector<Point<ll>> low;
    bool flag = false;
    for (int i = 0; i < hull.size(); ++i) {
        if (hull[i].x == mn) flag = true;
        if (flag) low.push_back(hull[i]);
        if (flag && hull[i].x == mx) break;
    }
    int Q; cin >> Q;
    while (Q--) {
        ll d; cin >> d;
        int l = 0, r = low.size();
        while (l + 1 < r) {
            int m = (l + r) >> 1;
            if (low[m].x < d) l = m;
            else r = m;
        }
        ll s = (low[l + 1].y - low[l].y) * (d - low[l].x) + (low[l + 1].x - low[l].x) * low[l].y;
        ll t = low[l + 1].x - low[l].x;
        ll g = gcd(s, t);
        cout << s / g << ' ' << t / g << '\n';
    }
}