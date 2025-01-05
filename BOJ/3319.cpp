#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Line {
	ll m, k;
};

ll N;
ll S[100001], V[100001];
vector<pair<ll, ll>> adj[100001];
ll dis[100001];
ll dp[100001];
vector<Line> cht(100000);
ll sz = 0;

double intersect(Line& a, Line& b) {
	return (double) (a.k - b.k) / (b.m - a.m);
}

// dp[i] = min(-dis[j] * V[i] + dp[j]) + dis[i] * V[i] + S[i]
void dfs(int v, int p) {
	// cout << v << '\n';
	int psz = sz;
	Line pline;
	int pidx;
	if (v == 1) {
		dp[v] = 0;
		pline = cht[sz];
		pidx = sz;
		cht[sz] = {-dis[v], dp[v]};
		++sz;
	} else {
		int l = 0, r = sz, mid;
		while (l + 1 < r) {
			int mid = (l + r) / 2;
			double xcor;
			if (mid == 0) xcor = -987654321.0;
			else xcor = intersect(cht[mid], cht[mid - 1]);
			
			if (xcor <= (double) V[v]) l = mid;
			else r = mid;
		}
		dp[v] = cht[l].m * V[v] + cht[l].k + dis[v] * V[v] + S[v];
		
		Line cur = {-dis[v], dp[v]};
		l = 0, r = sz;
		while (l + 1 < r) {
			int mid = (l + r) / 2;
			double xcor;
			if (mid == 0) xcor = -987654321;
			else xcor = intersect(cht[mid], cht[mid - 1]);
			
			if (xcor <= intersect(cht[mid], cur)) l = mid;
			else r = mid;
		}

		++l;
		pline = cht[l];
		pidx = l;
		cht[l] = cur;
		sz = l + 1;
		
	}
	// cout << v << '\n';
	// for (int i = 0; i < sz; ++i) {
	// 	cout << cht[i].m << ' ' << cht[i].k << '\n';
	// }
	// cout << '\n';
	for (auto [u, d]: adj[v]) if (u != p) {
		dis[u] = dis[v] + d;
		dfs(u, v);
	}
	sz = psz;
	cht[pidx] = pline;
}

void solve() {
	cin >> N;
	for (int i = 0; i < N - 1; ++i) {
		ll u, v, d; cin >> u >> v >> d;
		adj[u].push_back({v, d});
		adj[v].push_back({u, d});
	}
	for (int i = 2; i <= N; ++i) cin >> S[i] >> V[i];
	dfs(1, 0);
	for (int i = 2; i <= N; ++i) cout << dp[i] << ' ';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}