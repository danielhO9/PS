#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, k;
vector<pair<int, ll>> adj[50001];
int tar[50001];
ll cache[50001][2];

void dfs(int v, int p) {
    for (auto [u, _]: adj[v]) if (u != p) dfs(u, v), tar[v] += tar[u];
}

ll matchCache(int v, int p, int t) {
    ll& ret = cache[v][t];
    if (ret != -1) return ret;
    vector<pair<ll, ll>> arr;
    for (auto [u, d]: adj[v]) if (u != p && tar[u]) {
        arr.push_back(make_pair(matchCache(u, v, 0) + d, matchCache(u, v, 1) + 2 * d));
    }
    ll sm = 0;
    for (auto i: arr) sm += i.second;
    if (t == 1) return ret = sm;
    ll mx = 0;
    for (auto i: arr) mx = max(mx, i.second - i.first);
    return ret = sm - mx;
}



int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n - 1; ++i) {
        int u, v; ll d; cin >> u >> v >> d;
        adj[u].push_back(make_pair(v, d));
        adj[v].push_back(make_pair(u, d));
    }
    int j; cin >> j;
    for (int i = 0; i < j; ++i) {
        int m; cin >> m; tar[m] = 1;
    }
    dfs(k, -1);
    memset(cache, -1, sizeof(cache));
    cout << matchCache(k, -1, 0);

}