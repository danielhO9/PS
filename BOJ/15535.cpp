#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
	ll x, y;
};

ll cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }

ll ccw(const Point& a, const Point& b, const Point& c) {
	Point a_b = {b.x - a.x, b.y - a.y};
	Point b_c = {c.x - b.x, c.y - b.y};
	return cross(a_b, b_c);
}

int N;
Point pts[100000];
ll mn[100000];
ll mx[100000];
vector<ll> xcor;
unordered_map<ll, ll> m;
ll ans[100001];

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> pts[i].x >> pts[i].y;
	set<int> s;
	for (int i = 0; i < N; ++i) s.insert(pts[i].x);
	for (auto i: s) {
		m[i] = xcor.size();
		xcor.push_back(i);
		mn[m[i]] = LLONG_MAX;
		mx[m[i]] = LLONG_MIN;
	}
	for (int i = 0; i < N; ++i) {
		mn[m[pts[i].x]] = min(mn[m[pts[i].x]], pts[i].y);
		mx[m[pts[i].x]] = max(mx[m[pts[i].x]], pts[i].y);
	}
	int sz = xcor.size();
	ans[0] = 0ll;
	vector<Point> lo, hi;
	ll now = 0;
	for (int j = 0; j < 2; ++j) {
		now = 0;
		for (int i = 0; i < sz; ++i) {
			while (hi.size() >= 2) {
				auto b = hi.back(); hi.pop_back();
				auto a = hi.back();
				if (ccw(a, b, {xcor[i], mx[i]}) < 0) {
					hi.push_back(b);
					break;
				}
				now -= (b.y + a.y) * (b.x - a.x);
			}
			auto b = Point {xcor[i], mx[i]};
			if (hi.size() > 0) {
				auto a = hi.back();
				now += (b.y + a.y) * (b.x - a.x);
			}
			hi.push_back(b);
			// cout << i + 1 << ' ' << now << "\n";
			while (lo.size() >= 2) {
				auto b = lo.back(); lo.pop_back();
				auto a = lo.back();
				if (ccw(a, b, {xcor[i], mn[i]}) > 0) {
					lo.push_back(b);
					break;
				}
				now += (b.y + a.y) * (b.x - a.x);
			}
			b = Point {xcor[i], mn[i]};
			if (lo.size() > 0) {
				auto a = lo.back();

				now -= (b.y + a.y) * (b.x - a.x);
			}
			lo.push_back(b);
			ans[i + 1] += now;
			// cout << i + 1 << ' ' << now << "\n";
			// for (auto i: lo) cout << i.x << ' ' << i.y << '\n';
			// cout << '\n';
			// for (auto i: hi) cout << i.x << ' ' << i.y << '\n';
			// cout << '\n';

		}
		reverse(xcor.begin(), xcor.end());
		for (auto& i: xcor) i = -i;
		reverse(mn, mn + sz);
		reverse(mx, mx + sz);
		reverse(ans, ans + sz + 1);
		lo.clear();
		hi.clear();
	}
	ll ret = LLONG_MAX;
	for (int i = 0; i <= sz; ++i) ret = min(ret, ans[i]);
	cout << (ret + 1) / 2;

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}