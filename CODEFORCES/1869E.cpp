#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll MOD = 998244353;
ll powTemp[100001][121];
ll 

void init() {
	for (ll i = 1; i <= 1e5; ++i) for (ll j = 0; j <= 120; ++j) {
		if (j == 0) powTemp[i][j] = 1;
		else powTemp[i][j] = (powTemp[i][j - 1] * i) % MOD;
	}

}

void solve() {
	ll n, m; cin >> n >> m;

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	int t; cin >> t;
	while (t--) solve();
}