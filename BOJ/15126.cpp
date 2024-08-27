#include <bits/stdc++.h>
using namespace std;

long double EPS = 1e-8;

struct Point {
	long double x, y;
};

struct Circle {
	Point c; long double r;
};

struct Line {
	long double a, b, c;
};

int n;
Circle circle[50];
long double ans = 0.0;

bool inCircle(long double x, long double y, Circle cir) {
	return (cir.c.x - x) * (cir.c.x - x) + (cir.c.y - y) * (cir.c.y - y) < cir.r * cir.r + EPS;
}

bool possible(long double x, long double y) {
	for (int i = 0; i < n; ++i) {
		if (!inCircle(x, y, circle[i])) return false;
	}
	return true;
}

vector<Point> intersect(Circle c, Line l) {
	// cout << l.a << ' ' << l.b << ' ' << l.c << '\n';
	Line tl = {l.a, l.b, l.a * c.c.x + l.b * c.c.y + l.c};
	if (tl.c*tl.c > c.r*c.r*(tl.a*tl.a+tl.b*tl.b)+EPS) return {};
	if (abs (tl.c*tl.c - c.r*c.r*(tl.a*tl.a+tl.b*tl.b)) < EPS) return {};
	Point h = {-tl.a * tl.c / (tl.a * tl.a + tl.b * tl.b), -tl.b * tl.c / (tl.a * tl.a + tl.b * tl.b)};
	h.x += c.c.x; h.y += c.c.y;
	long double d = tl.c * tl.c / (tl.a * tl.a + tl.b * tl.b);
	d = c.r * c.r - d;
	long double mult = sqrt (d / (tl.a * tl.a+tl.b * tl.b));
	Point ret1 = {h.x + mult * l.b, h.y - mult * l.a};
	Point ret2 = {h.x - mult * l.b, h.y + mult * l.a};
	return {ret1, ret2};
}

vector<Point> intersect(Circle c1, Circle c2) {
	if (c1.r == c2.r && c1.c.x == c2.c.x && c1.c.y == c2.c.y) return {};
	long double a1 = c1.c.x, b1 = c1.c.y, r1 = c1.r, a2 = c2.c.x, b2 = c2.c.y, r2 = c2.r;
	Line l = {-2 * a1 + 2 * a2, - 2 * b1 + 2 * b2, b1 * b1 - b2 * b2 - r1 * r1 + r2 * r2 + a1 * a1 - a2 * a2};
	return intersect(c1, l);
}

void solve() {
	cin >> n;
	cout << fixed;
	cout.precision(3);
	for (int i = 0; i < n; ++i) cin >> circle[i].c.x >> circle[i].c.y >> circle[i].r;
	for (int i = 0; i < n; ++i) {
		long double x = circle[i].c.x, y = circle[i].c.y;
		long double theta = atan(y / x);
		if (abs(x - 0.0) < EPS) x += EPS;
		if (abs(y - 0.0) < EPS) y += EPS;
		long double tx = circle[i].r * x / sqrt(x * x + y * y);
		long double ty = circle[i].r * y / sqrt(x * x + y * y);
		if (possible(x + tx, y + ty)) ans = max(ans, sqrt((x + tx) * (x + tx) + (y + ty) * (y + ty)));
		if (possible(x - tx, y - ty)) ans = max(ans, sqrt((x - tx) * (x - tx) + (y - ty) * (y - ty)));
		for (int j = i + 1; j < n; ++j) {
			for (auto k: intersect(circle[i], circle[j])) {
				if (possible(k.x, k.y)) ans = max(ans, sqrt(k.x * k.x + k.y * k.y));
				// cout << k.x << ' ' << k.y << '\n';
			}
		}
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}