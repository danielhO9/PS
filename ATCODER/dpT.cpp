#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

int N;
string s;
vector<int> adj[3000];
ll cache[3000];
ll sz[3000];
ll fac[3001];
ll ifac[3001];
int deg[3000];

ll pow(ll a, ll b) {
	if (b == 0) return 1ll;
	ll half = pow(a, b / 2);
	half = (half * half) % MOD;
	if (b % 2) return (half * a) % MOD;
	else return half;
}

void dfs(int v) {
	sz[v] = 1;
	for (auto u: adj[v]) {
		dfs(u);
		sz[v] += sz[u];
	}
}

ll matchCache(int n) {
	ll& ret = cache[n];
	if (ret != -1) return ret;
	if (adj[n].size() == 0) return ret = 1;
	if (adj[n].size() == 1) return ret = matchCache(adj[n][0]);
	ll sz1 = sz[adj[n][0]];
	ll sz2 = sz[adj[n][1]];
	ret = fac[sz1 + sz2];
	ret *= ifac[sz1]; ret %= MOD;
	ret *= ifac[sz2]; ret %= MOD;
	ret *= matchCache(adj[n][0]); ret %= MOD;
	ret *= matchCache(adj[n][1]); ret %= MOD;
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> s;
	memset(deg, 0, sizeof(deg));
	for (int i = 0; i < N - 1; ++i) {
		if (s[i] == '<') {
			adj[i].push_back(i + 1);
			++deg[i + 1];
			cout << i + 1 << '\n';
		}
		else {
			adj[i + 1].push_back(i);
			++deg[i];
			cout << i << '\n';
		}
	}
	fac[0] = 1, ifac[0] = 1;
	for (ll i = 1; i <= 3001; ++i) {
		fac[i] = fac[i - 1] * i; fac[i] %= MOD;
		ifac[i] = pow(fac[i], MOD - 2);
	}
	memset(cache, -1, sizeof(cache));
	for (int i = 0; i < N; ++i) cout << deg[i] << ' ';
	cout << '\n';

	for (int i = 0; i < N; ++i) if (deg[i] == 0) dfs(i);
	for (int i = 0; i < N; ++i) cout << sz[i] << ' ';
	cout << '\n';
	
	ll ans = 1;
	vector<ll> szs;
	for (int i = 0; i < N; ++i) if (deg[i] == 0) {
		szs.push_back(sz[i]);
		ans *= matchCache(i);
		ans %= MOD;
	}
	ans *= fac[N]; ans %= MOD;
	for (auto i: szs) {
		ans *= ifac[i];
		ans %= MOD;
	}
	cout << ans;
}