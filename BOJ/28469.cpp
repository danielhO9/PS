#include <bits/stdc++.h>
using namespace std;

int N;
vector<pair<double, double>> v;

double f(double x) {
	double ret = v[0].second / (x - v[0].first) / (x - v[0].first);
	for (int i = 1; i < v.size(); ++i) {
		ret -= v[i].second / (x - v[i].first) / (x - v[i].first);
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	v.resize(N);
	for (int i = 0; i < N; ++i) cin >> v[i].first;
	for (int i = 0; i < N; ++i) cin >> v[i].second;
	sort(v.begin(), v.end());
	double l = v[0].first, r = v[1].first, mid;
	for (int i = 0; i < 50; ++i) {
		mid = (l + r) / 2.0;
		if (f(mid) < 0) r = mid;
		else l = mid;
	}
	cout.precision(7);
	cout << fixed;
	cout << l;
}