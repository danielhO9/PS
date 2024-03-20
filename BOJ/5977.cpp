#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	ll N, K; cin >> N >> K;
	vector<ll> E(N + 1); for (int i = 1; i <= N; ++i) cin >> E[i];
	vector<ll> sum(N + 1, 0); for (int i = 1; i <= N; ++i) sum[i] = sum[i - 1] + E[i];
	deque<pair<int, ll>> Q;
	ll cache[N + 1]; cache[0] = 0; Q.push_back({0, 0});
	for (int i = 1; i <= N; ++i) {
		while (!Q.empty() && Q.front().first < i - K) Q.pop_front();
		ll val = cache[i - 1] - sum[i];
		while (!Q.empty() && Q.back().second <= val) Q.pop_back();
		Q.push_back({i, val});
		cache[i] = sum[i] + Q.front().second; cache[i] = max(cache[i], cache[i - 1]);
	}
	cout << cache[N];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}