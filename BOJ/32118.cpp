#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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

int N, Q, midx;

template <typename T>
bool inConvex(const Point<T>& p, const deque<Point<T>>& pts) {
    assert(pts.size() >= 3);
    if (p.x == 0 && p.y == 0) return true;
    int l, r;
    if (pts[0].cross(p) < 0 && pts[N - 1].cross(p) >= 0) l = N - 1, r = N;
    else if (pts[midx - 1].cross(p) >= 0 && pts[midx].cross(p) < 0) l = midx - 1, r = midx;
    else {
        if (p.y >= 0) l = 0, r = midx - 1;
        else l = midx, r = N - 1;
    }
    int mid;
    while (l + 1 < r) {
        mid = (l + r) / 2;
        if (pts[mid].cross(p) >= 0) l = mid;
        else r = mid;
    }
    assert(pts[l].cross(p) >= 0 && pts[r].cross(p) < 0);
    if (pts[l].cross(p) == 0) {
        while (pts[l].cross(p) == 0) {
            if (pts[l].dist2() >= p.dist2()) return true;
            --l; if (l < 0) break;
        }
        return false;
    }
    return pts[l].cross(pts[r], p) >= 0;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> Q;
    deque<Point<ll>> pts(N);
    for (int i = 0; i < N; ++i) cin >> pts[i];
    while (pts.front().y <= 0) {
        pts.push_back(pts.front());
        pts.pop_front();
    }
    while (pts.back().y >= 0) {
        pts.push_front(pts.back());
        pts.pop_back();
    }
    pts.push_back(pts[0]);
    for (int i = 0; i < N; ++i) if (pts[i].y < 0) {
        midx = i;
        break;
    }
    bool inPolygon;
    Point<ll> prv;
    for (int i = 0; i < Q; ++i) {
        Point<ll> p; cin >> p;
        if (i == 0) {
            inPolygon = inConvex(p, pts);
            cout << inPolygon << '\n';
            prv = p;
            continue;
        }
        if (inPolygon) p = p + p - prv;
        else {
            Point<double> dif {(double) prv.x - p.x, (double) prv.y - p.y};
            dif.x /= 2.0; dif.y /= 2.0;
            dif.x += p.x; dif.y += p.y;
            p.x = dif.x; p.y = dif.y;
        }
        prv = p;
        inPolygon = inConvex(p, pts);
        cout << inPolygon << '\n';
    }
}