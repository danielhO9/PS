#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int N, K; cin >> N >> K;
	int M[N], V[N]; for (int i = 0; i < N; ++i) cin >> M[i] >> V[i];
	int C[K]; for (int i = 0; i < K; ++i) cin >> C[i];
	sort(C, C + K);
	vector<pair<int, int>> v;
	for (int i = 0; i < N; ++i) v.push_back({M[i], V[i]});
	sort(v.begin(), v.end());
	int idx = 0;
	ll ans = 0;
	priority_queue<ll> q;
	for (int i = 0; i < K; ++i) {
		while (idx < v.size() && v[idx].first <= C[i]) {
			q.push(v[idx].second);
			++idx;
		}
		if (!q.empty()) {
			ans += q.top();
			q.pop();
		}
		
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}