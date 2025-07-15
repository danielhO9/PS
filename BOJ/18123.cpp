#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 31;
bool vis[N];
int sz[N];
set<int> adj[N];

int getSize(int v, int p) {
    int& ret = sz[v]; ret = 1;
    for (auto u: adj[v]) if (u != p && !vis[u]) ret += getSize(u, v);
    return ret;
}

void getCent(int v, int p, int nsz, vector<int>& ret) {
    int psz = nsz - 1;
    bool flag = true;
    for (auto u: adj[v]) if (u != p && !vis[u]) {
        if (sz[u] * 2 >= nsz) getCent(u, v, nsz, ret);
        if (sz[u] * 2 > nsz) flag = false;
        psz -= sz[u];
    }
    if (flag && psz * 2 <= nsz) ret.push_back(v);
}

vector<int> centroid(int v, int p) {
    getSize(v, p); int nsz = sz[v];
    vector<int> ret;
    getCent(v, p, nsz, ret);
    return ret;
}

const ll prime[2] = {17, 53};
const ll MOD = 998244353;

ll hashing(const vector<ll>& a) {
    ll val[2] = {1, 1};
    ll curp[2] = {1, 1};
    for (auto j: a) {
        for (int i = 0; i < 2; ++i) {
            curp[i] *= prime[i]; curp[i] %= MOD;
            val[i] += (j * curp[i]) % MOD;
            val[i] %= MOD;
        }
    }
    return val[0] * val[1];
}

ll dfs(int v, int p) {
    vector<ll> s;
    ll val[2] = {1, 1};
    ll curp[2] = {1, 1};
    for (auto u: adj[v]) if (u != p) s.push_back(dfs(u, v));
    sort(s.begin(), s.end());
    return hashing(s);
}

int n;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    unordered_set<ll> rt1, rt2;
    for (int i = 0; i < n; ++i) {
        int s; cin >> s;
        for (int j = 0; j <= s; ++j) {
            adj[j].clear();
            vis[j] = false;
        }
        for (int j = 0; j < s - 1; ++j) {
            int u, v; cin >> u >> v;
            adj[u].insert(v);
            adj[v].insert(u);
        }
        auto cs = centroid(0, -1);
        if (cs.size() == 2) {
            adj[cs[0]].insert(s);
            adj[cs[1]].insert(s);
            adj[s].insert(cs[0]);
            adj[s].insert(cs[1]);
            if (adj[cs[0]].find(cs[1]) != adj[cs[0]].end()) adj[cs[0]].erase(adj[cs[0]].find(cs[1]));
            if (adj[cs[1]].find(cs[0]) != adj[cs[1]].end()) adj[cs[1]].erase(adj[cs[1]].find(cs[0]));
            rt2.insert(dfs(s, -1));
        } else rt1.insert(dfs(cs[0], -1));
    }
    cout << rt1.size() + rt2.size();
}