#include <bits/stdc++.h>
using namespace std;

int a[8], ans = 0;

double ccw(pair<double, double>& a, pair<double, double>& b) { return a.first * b.second - a.second * b.first; }

bool check(vector<int>& v) {
	vector<double> temp;
	for (auto i: v) temp.push_back(a[i]); temp.push_back(a[v[0]]); temp.push_back(a[v[1]]);
	for (int i = 1; i <= 9; ++i) {
		double x = temp[i - 1], y = temp[i], z = temp[i + 1];
		x *= sqrt(2.0) / 2.0; z *= sqrt(2.0) / 2.0;
		pair<double, double> v1, v2;
		v1 = {y - x, -x}, v2 = {z - y, -z};
		double res = ccw(v1, v2);
		// cout << temp[i - 1] << ' ' << temp[i] << ' ' << temp[i + 1] << res << '\n';
		if (res > 0) {
			return false;
		}
	}
	return true;
}

void generator(vector<int>& v, int& vis) {
	if (v.size() == 8) {
		if (check(v)) ++ans;
		return;
	}
	for (int i = 0; i < 8; ++i) if (!((vis >> i) & 1)) {
		v.push_back(i); vis ^= (1 << i);
		generator(v, vis);
		v.pop_back(); vis ^= (1 << i);
	}
}

void solve() {
	for (int i = 0; i < 8; ++i) cin >> a[i];
	vector<int> v = {}; int vis = 0;
	generator(v, vis);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}