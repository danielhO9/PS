#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 0-index
struct UF {
	vector<int> par, rk;
    vector<bool> isGraph;

	UF(int _sz) {
		par.resize(_sz);
		rk.resize(_sz);
        isGraph.resize(_sz);
		for (int i = 0; i < _sz; ++i) par[i] = i;
	}
	int find(int x) {
		if (par[x] == x) return x;
		par[x] = find(par[x]);
		return par[x];
	}
	void union_rank(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) {
            isGraph[x] = true;
            return;
        }
		if (rk[x] > rk[y]) swap(x, y);
		par[x] = y;
		if (rk[x] == rk[y]) ++rk[y];
        if (isGraph[x]) isGraph[y] = true;
	}
};

int n, m;
ll s[250000], t[250000];
ll sm;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    vector<ll> v;
    for (int i = 0; i < n; ++i) {
        cin >> s[i] >> t[i];
        v.push_back(s[i]);
        v.push_back(t[i]);
        sm += s[i];
        sm += t[i];
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    m = v.size();
    UF uf {m};
    for (int i = 0; i < n; ++i) {
        int a = lower_bound(v.begin(), v.end(), s[i]) - v.begin();
        int b = lower_bound(v.begin(), v.end(), t[i]) - v.begin();
        uf.union_rank(a, b);
    }
    vector<vector<ll>> adj(m);
    ll ans = 0;
    for (int i = 0; i < m; ++i) adj[uf.find(i)].push_back(v[i]);
    for (int i = 0; i < m; ++i) if (uf.find(i) == i) {
        for (auto j: adj[i]) ans += j;
        if (uf.isGraph[i]) continue;
        ll mx = 0;
        for (auto j: adj[i]) mx = max(mx, j);
        ans -= mx;
    }
    cout << sm - ans;
}