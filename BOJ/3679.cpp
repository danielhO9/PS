#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

struct Point {
	LL x, y;
	int index;
};

bool comp1 (const Point& a, const Point& b) {
	if (a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

bool comp2 (const Point& a, const Point& b) {
	if (a.x * b.y == a.y * b.x) {
		if (a.x == b.x) return a.y < b.y;
		return a.x < b.x;
	}
	return a.x * b.y > a.y * b.x;
}

LL cross(Point a, Point b) { return a.x * b.y - b.x * a.y; }

LL ccw(Point& a, Point& b, Point& c) {
	return cross({b.x - a.x, b.y - a.y}, {c.x - b.x, c.y - b.y});
}

void solve() {
	int N;
	vector<Point> v;
	cin >> N;
	LL x, y;
	for (int i = 0; i < N; ++i) {
		cin >> x >> y;
		v.push_back({x, y, i});
	}
	sort(v.begin(), v.end(), comp1);
	for (int i = 1; i < v.size(); ++i) {
		v[i].x -= v[0].x;
		v[i].y -= v[0].y;
	}
	v[0].x = 0; v[0].y = 0;
	sort(next(v.begin()), v.end(), comp2);
	Point s = v.front(); Point e = v.back();
	vector<int> ans;
	for (auto i = v.size() - 1; i >= 0; --i) {
		if (ccw(s, v[i], e) == 0) {
			ans.push_back(v[i].index);
		} else break;
	}
	for (int i = 0; i < (int) v.size() - (int) ans.size(); ++i) cout << v[i].index << ' ';
	for (auto i: ans) cout << i << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int c; cin >> c;
	while (c--) solve();
}