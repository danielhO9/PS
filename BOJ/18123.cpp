#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2000001; // modify
bool vis[N];
int sz[N];
vector<int> tmp[30];
vector<int> adj[N];

int getSize(int v, int p) {
    int& ret = sz[v]; ret = 1;
    for (auto u: tmp[v]) if (u != p && !vis[u]) ret += getSize(u, v);
    return ret;
}

void getCent(int v, int p, int nsz, vector<int>& ret) {
    int psz = nsz - 1;
    bool flag = true;
    for (auto u: tmp[v]) if (u != p && !vis[u]) {
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

ll dfs(int v, int p) {
    multiset<ll> s;
    ll val[2] = {1, 1};
    ll curp[2] = {1, 1};
    for (auto u: adj[v]) if (u != p) s.insert(dfs(u, v));
    for (auto cval: s) {
        for (int i = 0; i < 2; ++i) {
            curp[i] *= prime[i]; curp[i] %= MOD;
            val[i] += (cval * curp[i]) % MOD;
            val[i] %= MOD;
        }
    }
    return val[0] * val[1];
}

int n;
int num[30];
int cnt;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    cnt = 0;
    vector<int> rt1, rt2;
    for (int i = 0; i < n; ++i) {
        int s; cin >> s;
        for (int j = 0; j < s - 1; ++j) {
            int u, v; cin >> u >> v;
            if (num[u] == 0) num[u] = ++cnt;
            if (num[v] == 0) num[v] = ++cnt;
            tmp[u].push_back(v);
            tmp[v].push_back(u);
        }
        auto cs = centroid(0, -1);
        if (cs.size() == 2) {
            int c = ++cnt;
            adj[c].push_back(num[cs[0]]);
            adj[c].push_back(num[cs[1]]);
            adj[num[cs[0]]].push_back(c);
            adj[num[cs[1]]].push_back(c);
            rt2.push_back(c);
        } else rt1.push_back(num[cs[0]]);

        for (int j = 0; j < s; ++j) {
            for (auto k: tmp[j]) {
                if (cs.size() == 2 && j + k == cs[0] + cs[1] && abs(j - k) == abs(cs[0] - cs[1])) continue;
                adj[num[j]].push_back(num[k]);
            }
            tmp[j].clear();
        }
        for (int j = 0; j < s; ++j) num[j] = 0;
    }
    unordered_set<ll> s1, s2;
    for (auto i: rt1) s1.insert(dfs(i, -1));
    for (auto i: rt2) s2.insert(dfs(i, -1));
    cout << s1.size() + s2.size();
}