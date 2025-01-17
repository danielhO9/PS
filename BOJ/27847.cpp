#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int G, N;

struct Cor {
	ll x, y, t;
};

bool avail(Cor& a, Cor& b) {
	return (a.t - b.t) * (a.t - b.t) >= (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void solve() {
	cin >> G >> N;
	vector<Cor> g(G), n(N);
	for (int i = 0; i < G; ++i) cin >> g[i].x >> g[i].y >> g[i].t;
	for (int i = 0; i < N; ++i) cin >> n[i].x >> n[i].y >> n[i].t;
	sort(g.begin(), g.end(), [](Cor& a, Cor& b) {
		return a.t < b.t;
	});
	int ans = 0;
	for (int i = 0; i < N; ++i) {
		int cnt = 0;
		auto itr = lower_bound(g.begin(), g.end(), n[i].t, [](Cor& a, ll t) {
			return a.t < t;
		});
		if (itr != g.end()) {
			if (avail(*itr, n[i])) ++cnt;
		} else ++cnt;
		if (itr != g.begin()) {
			--itr;
			if (avail(*itr, n[i])) ++cnt;
		} else ++cnt;
		if (cnt != 2) ++ans;
		// cout << flag << '\n';
	}
	cout << ans;


}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}