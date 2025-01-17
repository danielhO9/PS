#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int K, N;
vector<pair<ll, ll>> v;

bool f(double x) {
	priority_queue<pair<double, int>> pq;
	for (int i = 0; i < N; ++i) {
		pq.push({-v[i].second * x + v[i].first, i});
	}
	ll P = 0, Q = 0;
	for (int i = 0; i < K; ++i) {
		int cur = pq.top().second; pq.pop();
		P += v[cur].first;
		Q += v[cur].second;
	}
	return (double) P / Q >= x + 1e-8;
}

void solve() {
	cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		ll P, Q; cin >> P >> Q;
		v.push_back({P, Q});
	}
	double l = 0.0, r = 1.01, mid;
	for (int i = 0; i < 50; ++i) {
		mid = (l + r) / 2.0;
		if (f(mid)) l = mid;
		else r = mid;
	}
	cout << fixed;
	cout.precision(7);
	cout << l;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}