#include <bits/stdc++.h>
using namespace std;

int n, q, xor_path[250001];
vector<pair<int, int>> adj[250001];

/**
 * Description: Union-Find (Disjoint Set Union) with path compression and union by rank.
 *  Supports efficient merging and finding of connected components.
 * Time: O(\alpha(N)) per operation, where \alpha is the inverse Ackermann function.
 */
// 0-index
struct UF {
    vector<int> par, rk, dis;

    UF(int sz) {
        par.resize(sz);
        rk.resize(sz);
        dis.resize(sz);
        for (int i = 0; i < sz; ++i) par[i] = i;
    }
    pair<int, int> find(int x) {
        if (par[x] == x) return {x, 0};
        auto [pp, pw] = find(par[x]);
        par[x] = pp;
        dis[x] ^= pw;
        return make_pair(par[x], dis[x]);
    }
    bool merge(int x, int y, int w) {
        auto tmp = find(x);
        x = tmp.first;
        w ^= tmp.second;
        
        tmp = find(y);
        y = tmp.first;
        w ^= tmp.second;

        if (x == y) {
            if (w) return false;
            return true;
        }
        if (rk[x] > rk[y]) swap(x, y);
        par[x] = y;
        dis[x] = w;
        if (xor_path[x] != -1) {
            int val = xor_path[x] ^ dis[x];
            if (xor_path[y] != -1 && xor_path[y] != val) return false;
            xor_path[y] = val;
        }
        if (rk[x] == rk[y]) ++rk[y];
        return true;
    }
};
int ans[250000];

void dfs(int v, int p) {
    for (auto [u, i]: adj[v]) if (u != p) {
        ans[i] = xor_path[v] ^ xor_path[u];
        dfs(u, v);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;
    for (int i = 0; i < n - 1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(make_pair(v, i));
        adj[v].push_back(make_pair(u, i));
    }
    UF uf {n + 1};
    memset(xor_path, -1, sizeof(xor_path));
    xor_path[1] = 0;

    bool available = true;
    for (int i = 0; i < q; ++i) {
        int u, v, x; cin >> u >> v >> x;
        if (u == 1 || v == 1) {
            auto tmp = uf.find(u + v - 1);
            if (xor_path[tmp.first] != -1 && (xor_path[tmp.first] != (tmp.second ^ x))) available = false;
            xor_path[tmp.first] = tmp.second ^ x;
        } else {
            if (!uf.merge(u, v, x)) available = false;
        }
    }
    if (!available) {
        cout << "No";
        return 0;
    }

    set<int> s;
    int cur = 0;
    for (int i = 2; i <= n; ++i) if (adj[i].size() & 1) {
        auto tmp = uf.find(i);
        if (xor_path[tmp.first] != -1) {
            cur ^= xor_path[tmp.first] ^ tmp.second;
            continue;
        }
        cur ^= tmp.second;
        if (s.find(tmp.first) != s.end()) s.erase(s.find(tmp.first));
        else s.insert(tmp.first);
    }
    cout << "Yes\n";
    if (!s.empty()) {
        int v = *s.begin();
        xor_path[v] = cur;
    }
    for (int i = 2; i <= n; ++i) {
        auto tmp = uf.find(i);
        if (xor_path[tmp.first] != -1) xor_path[i] = xor_path[tmp.first] ^ tmp.second;
        else xor_path[i] = tmp.second;
    }

    dfs(1, 0);
    for (int i = 0; i < n - 1; ++i) cout << ans[i] << ' ';
}