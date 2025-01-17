#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll cache[3000];

ll N, M, L;
ll U[3000], D[3000];
ll dis[3000][3000];
const ll MAX = 1e17;

ll f(ll i, ll j) {
	return dis[i][j] * (i + j + 1) * (M + N - i - j - 1);
}

void solve() {
	cin >> N >> M >> L;
	for (int i = 0; i < N; ++i) cin >> U[i];
	for (int i = 0; i < M; ++i) cin >> D[i];
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
		dis[i][j] = (U[i] - D[j]) * (U[i] - D[j]) + L * L;
	}
	for (int i = 0; i < M; ++i) cache[i] = MAX;
	cache[0] = 0;
	ll ncache[3000];
	for (int i = 0; i < N; ++i) {
		ll dv = MAX;
		for (int j = 0; j < M; ++j) {
			ll c1, c2, c3;
			if (j != 0) c1 = dv - f(i, j - 1) + dis[i][j - 1] * (M + N - 1) + f(i, j);
			else c1 = MAX;
			
			if (j != 0) c2 = f(i, j - 1) + f(i, j) + cache[j - 1];
			else c2 = MAX;
			
			c3 = cache[j] + dis[i][j] * (M + N - 1);

			ncache[j] = min({c1, c2, c3});
			dv = min(c1, c2);
		}
		swap(ncache, cache);
		// for (int j = 0; j < M; ++j) cout << cache[j] << ' ';
		// cout << '\n';
	}
	cout << cache[M - 1];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}