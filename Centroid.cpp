#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 500001; // modify
bool vis[N];
int sz[N];
vector<pair<int, ll>> adj[N];

int getSize(int v, int p) {
    int& ret = sz[v]; ret = 1;
    for (auto [u, _]: adj[v]) if (u != p && !vis[u]) ret += getSize(u, v);
    return ret;
}

void getCent(int v, int p, int nsz, vector<int>& ret) {
    int psz = nsz - 1;
    bool flag = true;
    for (auto [u, _]: adj[v]) if (u != p && !vis[u]) {
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

int dnc(int v) {
    int ret = 0.0;
	int c = centroid(v, -1)[0]; vis[c] = true;
	// compute

    for (auto [u, _]: adj[c]) if (!vis[u]) ret = max(dnc(u), ret);
    return ret;
}