#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

struct Point {
	LL x, y;
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

int N;
vector<Point> v;

LL cross(Point a, Point b) { return a.x * b.y - b.x * a.y; }

LL ccw(Point& a, Point& b, Point& c) {
	return cross({b.x - a.x, b.y - a.y}, {c.x - b.x, c.y - b.y});
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	LL x, y;
	for (int i = 0; i < N; ++i) {
		cin >> x >> y;
		v.push_back({x, y});
	}
	sort(v.begin(), v.end(), comp1);
	for (int i = 1; i < v.size(); ++i) {
		v[i].x -= v[0].x;
		v[i].y -= v[0].y;
	}
	v[0].x = 0; v[0].y = 0;
	sort(next(v.begin()), v.end(), comp2);
	stack<int> S; S.push(0); S.push(1);
	int a, b, c;
	for (int i = 2; i < v.size(); ++i) {
		while (S.size() >= 2) {
			b = S.top(); S.pop();
			a = S.top();
			if (ccw(v[a], v[b], v[i]) > 0) {
				S.push(b);
				break;
			}
		}
		S.push(i);
	}
	while (!S.empty()) {
		cout << S.top() << ' ';
		S.pop();
	}
	cout << S.size();
}