#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, m, q;
vector<pair<int, ll> > adj[401];

void solve() {
	cin >> n >> m >> q;
	for (int i = 0; i < m; ++i) {
		int a, b; ll c;
		cin >> a >> b >> c;
		adj[a].push_back(make_pair(b, c));
		adj[b].push_back(make_pair(a, c));
	}
	


}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}