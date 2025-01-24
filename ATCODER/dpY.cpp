#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

ll pow(ll a, ll b) {
	if (b == 0) return 1;
	ll h = pow(a, b / 2);
	h = (h * h) % MOD;
	if (b % 2) return (h * a) % MOD;
	else return h;
}

ll H, W, N;
vector<pair<ll, ll>> walls;
ll fac[200001];
ll ifac[200001];
ll dis[3000][3000];
ll cache[3000];

ll comb(ll n, ll r) {
	ll ret = fac[n];
	ret *= ifac[n - r]; ret %= MOD;
	ret *= ifac[r]; ret %= MOD;
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> H >> W >> N;
	for (int i = 0; i < N; ++i) {
		ll r, c; cin >> r >> c; --r; --c;
		walls.push_back({r, c});
	}
	sort(walls.begin(), walls.end(), [](const pair<ll, ll>& a, const pair<ll, ll>& b) {
		if (a.first + a.second == b.first + b.second) return a.first < b.first;
		return a.first + a.second < b.first + b.second;
	});
	fac[0] = 1, ifac[0] = 1;
	for (ll i = 1; i <= 2e5; ++i) {
		fac[i] = fac[i - 1] * i; fac[i] %= MOD;
		ifac[i] = pow(fac[i], MOD - 2);
	}
	for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
		ll dify = walls[j].first - walls[i].first;
		ll difx = walls[j].second- walls[i].second;
		if (dify >= 0 && difx >= 0) dis[i][j] = comb(dify + difx, difx);
	}
	ll ans = comb(H + W - 2, H - 1);
	for (int i = 0; i < N; ++i) {
		
		cache[i] = comb(walls[i].first + walls[i].second, walls[i].second);
		for (int j = 0; j < i; ++j) {
			cache[i] -= (cache[j] * dis[j][i]) % MOD;
			cache[i] += MOD;
			cache[i] %= MOD;
		}
		ans -= (cache[i] * comb(H - 1 - walls[i].first + W - 1 - walls[i].second, H - 1 - walls[i].first)) % MOD;
		ans += MOD;
		ans %= MOD;
	}
	cout << ans;


}