#include <bits/stdc++.h>
using namespace std;

void solve() {
	int a, b; cin >> a >> b;
	vector<pair<int, int>> V = {{a, b}, {a, -b}, {-a, b}, {-a, -b}, {b, a}, {b, -a}, {-b, a}, {-b, -a}};
	int xk, yk; cin >> xk >> yk;
	int xq, yq; cin >> xq >> yq;
	set<pair<int, int>> Sv, Sq;
	for (int i = 0; i < 8; ++i) {
		Sv.insert({xk + V[i].first, yk + V[i].second});
	}
	int ans = 0;
	for (int i = 0; i < 8; ++i) {
		Sq.insert({xq + V[i].first, yq + V[i].second});
	}
	for (auto i: Sv) {
		if (Sq.find(i) != Sq.end()) ++ans;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}