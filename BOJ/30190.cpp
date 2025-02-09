#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

int N, K;
int pos[1000001];
ll val[1000001];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> K;
	for (int i = 1; i <= N; ++i) cin >> pos[i];
	val[0] = 0;
	val[1] = 1;
	for (ll i = 2; i <= N; ++i) {
		val[i] = val[i - 1] * 2 + 1;
		val[i] %= MOD;
	}
	ll ans = 0;
	for (int i = N; i >= 1; --i) {
		if (pos[i] == K) continue;
		ans += val[i - 1] + 1;
		ans %= MOD;
		K = 6 - K - pos[i];
	}
	cout << ans;

}