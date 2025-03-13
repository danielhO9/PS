#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 10001; // modify

bool vis[N];
int sz[N];
vector<int> adj[N];

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


int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    auto ans = centroid(1, 0);
    sort(ans.begin(), ans.end());
    for (auto i: ans) cout << i << ' ';
    
}