#include <bits/stdc++.h>
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

Point<double> A, B, C, D;

double f(double t) {
    Point<double> s = A + (B - A) * t;
    Point<double> e = C + (D - C) * t;
    return (e - s).dist();
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> A >> B >> C >> D;
    double l = 0, r = 1;
    for (int i = 0; i < 50; ++i) {
        double m1 = (l * 2.0 + r) / 3.0;
        double m2 = (l + r * 2.0) / 3.0;
        if (f(m1) < f(m2)) r = m2;
        else l = m1;
    }
    cout.precision(7);
    cout <<fixed;
    cout << f(l);
}