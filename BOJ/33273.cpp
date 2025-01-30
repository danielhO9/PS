#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, M;
ll x[500], c[500];
unordered_map<int, ll> mx[500];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	for (ll i = 0; i < M; ++i) cin >> x[i] >> c[i];
	vector<pair<ll, ll>> v;
	for (int i = 0; i < M; ++i) v.push_back({-x[i], i});
	sort(v.begin(), v.end());

	for (int i = 0; i < M; ++i) {
		int cur = v[i].second;
		mx[i][min(c[cur], N)] = min(c[cur], N) * x[cur];
		for (int j = 0; j < i; ++j) if (x[v[j].second] % x[cur] == 0) {
			for (auto& [pcnt, pval]: mx[j]) {
				ll dif = min(N - pcnt, c[cur]);
				mx[i][dif + pcnt] = max(mx[i][dif + pcnt], pval + x[cur] * dif);
			}
		}
	}
	ll ans = -1;
	for (int i = 0; i < M; ++i) if (mx[i].find(N) != mx[i].end()) ans = max(ans, mx[i][N]);
	cout << ans;
}