#include <bits/stdc++.h>
using namespace std;

int ccw(pair<int, int>& a, pair<int, int>& b) { return a.first * b.second - a.second * b.first; }

void solve() {
	pair<int, int> p[3];
	for (int i = 0; i < 3; ++i) cin >> p[i].first >> p[i].second;
	pair<int, int> t1 = {p[1].first - p[0].first, p[1].second - p[0].second};
	pair<int, int> t2 = {p[2].first - p[1].first, p[2].second - p[1].second};
	int ret = ccw(t1, t2);
	if (ret > 0) {
		cout << 1;
		return;
	}
	else if (ret == 0) {
		cout << 0;
		return;
	}
	else {
		cout << -1; return;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}