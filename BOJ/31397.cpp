#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
pair<ll, ll> points[200001];
double l, S;
double lsum[200001];

double len(int i, int j) {
	double ret = (points[i].first - points[j].first) * (points[i].first - points[j].first);
	ret += (points[i].second - points[j].second) * (points[i].second - points[j].second);
	return sqrt(ret);
}

bool area(double s) {
	double e = l / 2.0 + s;
	int sidx = upper_bound(lsum, lsum + N + 1, s) - lsum;
	if (sidx == N + 1) {
		s -= l; s = abs(s); sidx = 1;
	}
	s -= lsum[sidx - 1];
	double r = s / len(sidx - 1, sidx);
	pair<double, double> spt = {points[sidx - 1].first * (1.0 - r) + points[sidx].first * r,
								points[sidx - 1].second * (1.0 - r) + points[sidx].second * r};

	int eidx = upper_bound(lsum, lsum + N + 1, e) - lsum;
	if (eidx == N + 1) {
		e -= l; e = abs(e); eidx = 1;
	}
	e -= lsum[eidx - 1];
	r = e / len(eidx - 1, eidx);
	pair<double, double> ept = {points[eidx - 1].first * (1.0 - r) + points[eidx].first * r,
								points[eidx - 1].second * (1.0 - r) + points[eidx].second * r};
	// cout << spt.first << ' ' << spt.second << "\n";
	// cout << ept.first << ' ' << ept.second << "\n";
	vector<pair<double, double>> pts;
	pts.push_back(spt);
	sidx %= N; eidx %= N;
	int idx = sidx;
	// cout << sidx << ' ' << eidx << '\n';
	while (true) {
		if (idx == eidx) break;
		pts.push_back(points[idx]);
		++idx;
		idx %= N;
	}
	pts.push_back(ept);
	pts.push_back(spt);
	double a = 0.0;
	for (int i = 0; i + 1 < pts.size(); ++i) {
		a += pts[i].first * pts[i + 1].second;
		a -= pts[i].second * pts[i + 1].first;
	}
	a = abs(a);
	a /= 2.0;
	// cout << a << ' ';
	return a > S / 2.0;
}

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> points[i].first >> points[i].second;
	points[N] = points[0];
	lsum[0] = 0.0;
	for (int i = 0; i < N; ++i) {
		int j = i + 1;
		lsum[j] = lsum[i] + len(i, j);
	}
	l = lsum[N];
	for (int i = 0; i < N; ++i) {
		S += points[i].first * points[i + 1].second;
		S -= points[i].second * points[i + 1].first;
	}
	S = abs(S);
	S /= 2.0;
	double le = 0.0, ri = l / 2.0;
	int lv = area(le), rv = area(ri);
	if (lv == rv) lv = 1 - lv;
	for (int i = 0; i < 100; ++i) {
		double mid = (le + ri) / 2.0;
		int v = area(mid);
		if (v == lv) {
			le = mid;
		} else {
			ri = mid;
		}
	}

	double s = (le + ri) / 2.0;

	double e = l / 2.0 + s;
	int sidx = upper_bound(lsum, lsum + N + 1, s) - lsum;
	if (sidx == N + 1) {
		s -= l; s = abs(s); sidx = 1;
	}
	s -= lsum[sidx - 1];
	double r = s / len(sidx - 1, sidx);
	cout << "YES\n";
	cout << sidx - 1 + 1 << ' ';
	cout << fixed;
	cout.precision(12);
	cout << r << '\n';

	int eidx = upper_bound(lsum, lsum + N + 1, e) - lsum;
	if (eidx == N + 1) {
		e -= l; e = abs(e); eidx = 1;
	}
	e -= lsum[eidx - 1];
	r = e / len(eidx - 1, eidx);
	cout << eidx - 1 + 1 << ' ';
	cout << fixed;
	cout.precision(12);
	cout << r << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}