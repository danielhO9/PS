#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 500001; // modify

bool vis[N];
int sz[N];
vector< pair<int, ll> > adj[N];
ll d[N], h[N];

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

int n, k;

void dfs(int v, int p, vector<double>& dis) {
    for (auto [u, w]: adj[v]) if (!vis[u] && u != p) {
        ll nh = h[v] + 1, nd = d[v] + w;
        if (dis.size() <= nh) dis.resize(nh + 1);
        dis[nh] = max(dis[nh], (double) nd);
        h[u] = nh, d[u] = nd;
        dfs(u, v, dis);
    }
}

// dis[i] / i > x
bool f(double x, vector<double>& dis, vector<double>& ndis) {
    vector< pair<double, int> > v[2];
    for (int i = 0; i < dis.size(); ++i) v[0].push_back(make_pair(dis[i] - i * x, i));
    for (int i = 0; i < ndis.size(); ++i) v[1].push_back(make_pair(ndis[i] - i * x, i));
    for (int i = 0; i < 2; ++i) for (int j = (int) v[i].size() - 2; j >= 0; --j) v[i][j] = max(v[i][j], v[i][j + 1]);
    for (int i = max(0, k - (int) v[1].size() + 1); i <= k; ++i) {
        if (i >= v[0].size()) break;
        int iidx = v[0][i].second, jidx = v[1][k - i].second;
        if ((dis[iidx] + ndis[jidx]) / (iidx + jidx) > x) return true;
    }
    return false;
}

double dnc(int v) {
    double ret = 0.0;
	int c = centroid(v, -1)[0]; vis[c] = true;
    // cout << c << '\n';
    vector<double> dis; dis.push_back(0);
    h[c] = 0, d[c] = 0;
    for (auto [u, w]: adj[c]) if (!vis[u]) {
        vector<double> ndis;
        ndis.push_back(0); ndis.push_back(w);
        h[u] = 1, d[u] = w; dfs(u, c, ndis);
        if (dis.size() < ndis.size()) swap(dis, ndis);

        double l = 0.0, r = 1e6 + 0.1, mid;
        for (int t = 0; t < 50; ++t) {
            mid = (l + r) / 2;
            if (f(mid, dis, ndis)) l = mid;
            else r = mid;
        }
        ret = max(ret, l);

        for (int i = 0; i < ndis.size(); ++i) dis[i] = max(dis[i], ndis[i]);
    }
    for (auto [u, _]: adj[c]) if (!vis[u]) ret = max(dnc(u), ret);
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n - 1; ++i) {
        int u, v; ll c; cin >> u >> v >> c;
        adj[u].push_back(make_pair(v, c));
        adj[v].push_back(make_pair(u, c));
    }
    cout << fixed;
    cout.precision(7);
    cout << dnc(1);
}