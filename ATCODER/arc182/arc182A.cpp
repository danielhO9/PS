#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 998244353;
ll N, Q;
ll P[5001], V[5001];
ll way[5001];

ll pow(ll a, ll b) {
	if (b == 0) return 1ll;
	ll half = pow(a, b / 2);
	half = half * half;
	half %= MOD;
	if (b % 2) return (half * a) % MOD;
	else return half;
}

void solve() {
	cin >> N >> Q;
	for (int i = 1; i <= Q; ++i) cin >> P[i] >> V[i];
	memset(way, -1, sizeof(way));
	for (int i = 2; i <= Q; ++i) {
		for (int j = 1; j < i; ++j) {
			if (V[j] > V[i]) {

				if (P[j] == P[i]) {
					cout << 0;
					return;
				}
				if (P[j] < P[i]) {
					if (way[j] == 1 || way[i] == 0) {
						cout << 0;
						return;
					}
					way[j] = 0; way[i] = 1;
				} else {
					if (way[j] == 0 || way[i] == 1) {
						cout << 0;
						return;
					}
					way[j] = 1; way[i] = 0;
				}

			}
		}
	}
	int cnt = 0;
	// cout << cnt << ' ';
	for (int i = 1; i <= Q; ++i) if (way[i] == -1) ++cnt;
	cout << pow(2ll, (ll)cnt);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}