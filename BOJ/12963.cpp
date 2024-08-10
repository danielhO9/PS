#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1000000007;

int N, M;
int par[2000];
int rk[2000];
vector<int> rev;

int find(int v) {
	if (v == par[v]) return v;
	return find(par[v]);
}

void Union(int u, int v) {
	v = find(v), u = find(u);
	if (v == u) return;
	if (rk[u] > rk[v]) swap(u, v);
	par[u] = v;
	if (rk[u] == rk[v]) {
		++rk[v];
		rev = {u, v, 1};
	} else {
		rev = {u, v, 0};
	}
}

ll pow(ll a, ll b) {
	if (b == 0) return 1ll;
	ll half = pow(a, b / 2);
	half = half * half; half %= MOD;
	if (b % 2) return (half * a) % MOD;
	else return half;
}

ll ans = 0ll;

void solve() {
	cin >> N >> M;
	for (int i = 0; i < N; ++i) par[i] = i;
	vector<pair<int, int>> edge;
	for (int i = 0; i < M; ++i) {
		int u, v; cin >> u >> v;
		edge.push_back({u, v});
	}
	for (int i = M - 1; i >= 0; --i) {
		Union(edge[i].first, edge[i].second);
		if (find(0) == find(N - 1)) {
			ans += pow(3ll, (ll) i);
			ans %= MOD;
			par[rev[0]] = rev[0];
			rk[rev[1]] -= rev[2];
		}
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}