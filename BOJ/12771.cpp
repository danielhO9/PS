#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Poll {
	ll x, y;
};

ll ccw(const Poll& a, const Poll& b) {
	Poll tmp = {b.x - a.x, b.y - a.y};
	return a.x * tmp.y - a.y * tmp.x;
}

struct Oil {
	Poll p;
	ll val;
	bool operator < (const Oil& a) const {
		if (ccw(p, a.p) == 0) return val > a.val;
		return ccw(p, a.p) > 0;
	}
};

ll n;
vector<Oil> dep;
vector<Oil> ndep;

void solve() {
	cin >> n;
	for (ll i = 0; i < n; ++i) {
		ll x0, x1, y; cin >> x0 >> x1 >> y;
		if (x1 < x0) swap(x0, x1);
		dep.push_back({{x1, y}, x1 - x0});
		dep.push_back({{x0, y}, x0 - x1});
	}


	ll ans = -1;
	ll bx, by;
	for (ll i = 0; i < 2 * n; ++i) {
		ndep.clear();
		ll tans = dep[i].val;
		ans = max(tans, ans);
		bx = dep[i].p.x;
		by = dep[i].p.y;
		for (ll j = 0; j < 2 * n; ++j) if (j / 2 != i / 2) {
			ll nx = dep[j].p.x - bx;
			ll ny = dep[j].p.y - by;
			ll nval = dep[j].val;
			if (ny < 0) {
				nx *= -1;
				ny *= -1;
				nval *= -1;
			}
			if (ny != 0) ndep.push_back({{nx, ny}, nval});
		}
		sort(ndep.begin(), ndep.end());
		// for (auto j: ndep) {
		// 	cout << j.p.x << ' ' << j.p.y << ' ' << j.val << '\n';
		// }
		// cout << '\n';
		for (ll j = 0; j < ndep.size(); ++j) {
			tans += ndep[j].val;
			ans = max(ans, tans);
		}
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}