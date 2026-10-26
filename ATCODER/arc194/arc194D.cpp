#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll p[2] = {17, 53};
const ll MOD = 998244353;

int N;
string S;
ll fac[5005], ifac[5005];
vector<int> adj[5005];
ll h[5005], val[5005];
ll leaf;

ll pow(ll a, ll b) {
	if (b == 0) return 1ll;
	ll half = pow(a, b / 2);
	half = (half * half) % MOD;
	if (b % 2) return (half * a) % MOD;
	return half;
}

void init() {
	fac[0] = 1, ifac[0] = 1;
	for (ll i = 1; i < 5005; ++i) fac[i] = (fac[i - 1] * i) % MOD;
	for (ll i = 1; i < 5005; ++i) ifac[i] = pow(fac[i], MOD - 2);
}

void dfs(int v) {
	val[v] = 1;
	h[v] = 0;
	if (adj[v].size() == 0) {
		h[v] = leaf;
		return;
	}
	map<ll, ll> m;
	for (auto u: adj[v]) {
		dfs(u);
		++m[h[u]];
		val[v] *= val[u]; val[v] %= MOD;
	}
	ll pcur[2] = {p[0], p[1]};
	ll cnt = 0;
	ll nh[2] = {0, 0};
	for (auto [i, j]: m) {
		for (int k = 0; k < j; ++k) {
			for (int l = 0; l < 2; ++l) {
				pcur[l] *= p[l]; pcur[l] %= MOD;
				nh[l] += (i * pcur[l]) % MOD;
				nh[l] %= MOD;
			}
		}
		cnt += j;
		val[v] *= ifac[j]; val[v] %= MOD;
	}
	h[v] = nh[0] * nh[1];
	val[v] *= fac[cnt]; val[v] %= MOD;
}

void solve() {
	cin >> N >> S;
	leaf = 269; leaf %= MOD;
	N += 2;
	S = '(' + S + ')';
	stack<int> s;
	for (int i = 0; i < N; ++i) {
		if (S[i] == '(') {
			if (!s.empty()) adj[s.top()].push_back(i);
			s.push(i);
		} else s.pop();
	}
	dfs(0);
	cout << val[0];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	solve();
}