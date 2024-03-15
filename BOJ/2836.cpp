#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	ll N, M; cin >> N >> M;
	vector<pair<ll, ll>> V;
	for (int i = 0; i < N; ++i) {
		ll s, e; cin >> s >> e;
		if (s > e) {
			V.push_back({s, -1});
			V.push_back({e, 1});
		}
	}
	sort(V.begin(), V.end());
	ll s, sum = 0, ans = 0;
	for (auto [i, j]: V) {
		sum += j;
		if (j == 1 && sum == 1) {
			s = i;
		}
		if (j == -1 && sum == 0) {
			ans += (i - s) * 2;
		}
	}
	ans += M;
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}