#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

ll cross(const pair<ll, ll>& a, const pair<ll, ll>& b) { return a.first * b.second - a.second * b.first; }
ll ccw(const pair<ll, ll>& a, const pair<ll, ll>& b, const pair<ll, ll>& c) {
	pair<ll, ll> a_b = {b.first - a.first, b.second - a.second};
	pair<ll, ll> b_c = {c.first - b.first, c.second - b.second};
	return cross(a_b, b_c);
}

bool isMeet(const pair<ll, ll>& a1, const pair<ll, ll>& a2, const pair<ll, ll>& b1, const pair<ll, ll>& b2) {
	ll ab1 = ccw(a1, a2, b1); if (ab1 != 0) ab1 /= abs(ab1);
	ll ab2 = ccw(a1, a2, b2); if (ab2 != 0) ab2 /= abs(ab2);
	ll ba1 = ccw(b1, b2, a1); if (ba1 != 0) ba1 /= abs(ba1);
	ll ba2 = ccw(b1, b2, a2); if (ba2 != 0) ba2 /= abs(ba2);
	if (ab1 * ab2 == 0 && ba1 * ba2 == 0) return min(b1, b2) <= max(a1, a2) && min(a1, a2) <= max(b1, b2);
	return ab1 * ab2 <= 0 && ba1 * ba2 <= 0;
}

ll w[2500];
pair<pll, pll> point[2500];
int dim[2500];
vector<int> adj[2500];

void solve() {
	int N; cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> point[i].first.first >> point[i].first.second >> point[i].second.first >> point[i].second.second;
		cin >> w[i];
	}
	for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
		if (isMeet(point[i].first, point[i].second, point[j].first, point[j].second)) {
			adj[i].push_back(j);
			adj[j].push_back(i);
			++dim[i];
			++dim[j];
		}
	}
	ll ans = 0ll;
	priority_queue<pair<ll, int>> Q;
	for (int i = 0; i < N; ++i) Q.push({-w[i], i});
	while (!Q.empty()) {
		ll wi = -Q.top().first; int idx = Q.top().second; Q.pop();
		ans += (dim[idx] + 1) * wi;
		for (auto i: adj[idx]) --dim[i];
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}