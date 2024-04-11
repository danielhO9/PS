#include <bits/stdc++.h>
using namespace std;

struct Point {
	double x, y;
};

Point mid(Point a, Point b) { return {(a.x + b.x) / 2, (a.y + b.y) / 2}; }

Point circumcenter(Point a, Point b, Point c) {
	double denominator = 2 * (a.x - b.x) * (c.y - b.y) - 2 * (c.x - b.x) * (a.y - b.y);
	double numerator21 = b.x * b.x - a.x * a.x + b.y * b.y - a.y * a.y;
	double numerator23 = b.x * b.x - c.x * c.x + b.y * b.y - c.y * c.y;
	double retx = (-numerator21 * (c.y - b.y) + numerator23 * (a.y - b.y)) / denominator;
	double rety = (numerator21 * (c.x - b.x) - numerator23 * (a.x - b.x)) / denominator;
	return {retx, rety};
}

double dist(Point a, Point b) { return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }

void solve() {
	int N; cin >> N;
	Point island[N];
	for (int i = 0; i < N; ++i) cin >> island[i].x >> island[i].y;
	random_device rd;
	shuffle(island, island + N, rd);
	Point center = {0.0, 0.0}; double radius = 0.0;
	for (int i = 0; i < N; ++i) if (dist(center, island[i]) > radius) {
		center = island[i]; radius = 0.0;
		for (int j = 0; j < i; ++j) if (dist(center, island[j]) > radius) {
			center = mid(island[i], island[j]); radius = dist(center, island[j]);
			for (int k = 0; k < j; ++k) if (dist(center, island[k]) > radius) {
				center = circumcenter(island[i], island[j], island[k]); radius = dist(center, island[k]);
			}
		}
	}
	cout << fixed;
	cout.precision(3);
	cout << center.x << ' ' << center.y << '\n';
	cout << radius;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}