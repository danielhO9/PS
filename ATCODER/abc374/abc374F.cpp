#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

ll K, N, X;
ll T[100];
ll sumT[100];
vector<pll> cache[100];

ll query(ll a, ll b) {
	ll ret = sumT[b];
	if (a == 0) return ret;
	ret -= sumT[a - 1];
	return ret;
}

void solve() {
	cin >> N >> K >> X;
	for (int i = 0; i < N; ++i) cin >> T[i];

	sumT[0] = T[0];
	for (int i = 1; i < N; ++i) {
		sumT[i] = sumT[i - 1] + T[i];
	}

	cache[0].push_back({T[0], 0ll});
	for (ll i = 1; i < N; ++i) {
		vector<pll> arr;
		if (i + 1 <= K) {
			ll time = T[i];
			ll cost = 0ll;
			cost += time * (i + 1) - query(0, i);
			arr.push_back({time, cost});
		}
		for (ll j = max(i - K, 0ll); j < i; ++j) {
			for (auto& k: cache[j]) {
				ll time = max(k.first + X, T[i]);
				ll cost = k.second;
				cost += time * (i - j) - query(j + 1, i);
				arr.push_back({time, cost});
			}
		}
		sort(arr.begin(), arr.end());
		for (auto j: arr) {
			if (cache[i].empty() || cache[i].back().second > j.second) cache[i].push_back(j);
		}
	}

	ll ans = LLONG_MAX;
	for (auto i: cache[N - 1]) {
		ans = min(ans, i.second);
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}